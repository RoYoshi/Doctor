#include "doctorbackend.h"

#include <QFile>
#include <QFileInfo>
#include <QStorageInfo>
#include <QSysInfo>
#include <QStringList>

namespace {
QString readText(const QString &path)
{
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return {};
    return QString::fromUtf8(file.readAll());
}

QString osReleaseValue(const QString &key)
{
    QString text = readText(QStringLiteral("/usr/lib/os-release"));
    if (text.isEmpty())
        text = readText(QStringLiteral("/etc/os-release"));

    for (const QString &line : text.split('\n')) {
        if (!line.startsWith(key + QLatin1Char('=')))
            continue;
        QString value = line.mid(key.size() + 1).trimmed();
        if (value.size() >= 2 && value.startsWith('"') && value.endsWith('"'))
            value = value.mid(1, value.size() - 2);
        return value;
    }
    return {};
}

QString gib(qint64 bytes)
{
    return QString::number(bytes / (1024.0 * 1024.0 * 1024.0), 'f', 1)
        + QStringLiteral(" GiB");
}

qint64 memInfoKiB(const QString &key)
{
    const QString text = readText(QStringLiteral("/proc/meminfo"));
    for (const QString &line : text.split('\n')) {
        if (line.startsWith(key + QLatin1Char(':'))) {
            const QString value = line.mid(key.size() + 1).trimmed().section(' ', 0, 0);
            bool ok = false;
            const qint64 result = value.toLongLong(&ok);
            return ok ? result : -1;
        }
    }
    return -1;
}

QString cpuModel()
{
    const QString text = readText(QStringLiteral("/proc/cpuinfo"));
    for (const QString &line : text.split('\n')) {
        if (line.startsWith(QStringLiteral("model name")))
            return line.section(':', 1).trimmed();
    }
    return QSysInfo::currentCpuArchitecture();
}

QString gpuVendor()
{
    // Optional first graphics device. This is a vendor hint, not a driver test.
    for (int card = 0; card < 8; ++card) {
        const QString vendor = readText(QStringLiteral("/sys/class/drm/card%1/device/vendor").arg(card)).trimmed();
        if (vendor == QLatin1String("0x10de")) return QStringLiteral("NVIDIA detected");
        if (vendor == QLatin1String("0x1002")) return QStringLiteral("AMD detected");
        if (vendor == QLatin1String("0x8086")) return QStringLiteral("Intel detected");
    }
    return QStringLiteral("Not detected");
}
}

DoctorBackend::DoctorBackend(QObject *parent)
    : QObject(parent)
{
    m_process.setProcessChannelMode(QProcess::MergedChannels);
    m_timeout.setSingleShot(true);
    m_timeout.setInterval(15000);

    connect(&m_process, &QProcess::readyReadStandardOutput, this, [this]() {
        emit consoleOutput(QString::fromUtf8(m_process.readAllStandardOutput()));
    });
    connect(&m_process, &QProcess::stateChanged, this, [this]() {
        emit busyChanged();
    });
    connect(&m_process, &QProcess::finished, this,
            [this](int exitCode, QProcess::ExitStatus) {
        m_timeout.stop();
        emit commandFinished(exitCode);
    });
    connect(&m_process, &QProcess::errorOccurred, this,
            [this](QProcess::ProcessError) {
        m_timeout.stop();
        emit commandError(m_process.errorString());
    });
    connect(&m_timeout, &QTimer::timeout, this, [this]() {
        emit commandError(QStringLiteral("Diagnostic timed out after 15 seconds."));
        m_process.kill();
    });
    refreshSystemInfo();
}

void DoctorBackend::refreshSystemInfo()
{
    m_osName = osReleaseValue(QStringLiteral("PRETTY_NAME"));
    if (m_osName.isEmpty())
        m_osName = QSysInfo::prettyProductName();

    m_feXicoVersion = osReleaseValue(QStringLiteral("FE_XICO_VERSION"));
    if (m_feXicoVersion.isEmpty())
        m_feXicoVersion = QStringLiteral("Not reported by this system");

    m_kernelText = QSysInfo::kernelVersion();
    m_cpuText = cpuModel();

    const qint64 totalKiB = memInfoKiB(QStringLiteral("MemTotal"));
    const qint64 availableKiB = memInfoKiB(QStringLiteral("MemAvailable"));
    m_memoryText = (totalKiB > 0 && availableKiB >= 0)
        ? QStringLiteral("%1 / %2 used").arg(gib((totalKiB - availableKiB) * 1024),
                                             gib(totalKiB * 1024))
        : QStringLiteral("Unavailable");

    QStorageInfo root(QStringLiteral("/"));
    m_diskText = (root.isValid() && root.isReady() && root.bytesTotal() > 0)
        ? QStringLiteral("%1 / %2 available").arg(gib(root.bytesAvailable()),
                                                  gib(root.bytesTotal()))
        : QStringLiteral("Unavailable");

    const QString uptime = readText(QStringLiteral("/proc/uptime")).section(' ', 0, 0);
    bool ok = false;
    const qint64 seconds = static_cast<qint64>(uptime.toDouble(&ok));
    m_uptimeText = ok
        ? QStringLiteral("%1d %2h %3m").arg(seconds / 86400)
              .arg((seconds / 3600) % 24).arg((seconds / 60) % 60)
        : QStringLiteral("Unavailable");

    m_gpuText = gpuVendor();
    emit snapshotChanged();
}

void DoctorBackend::runAction(const QString &actionId)
{
    if (busy()) {
        emit commandError(QStringLiteral("Another diagnostic is still running."));
        return;
    }

    QString program;
    QStringList arguments;
    if (actionId == QLatin1String("failed-services")) {
        program = QStringLiteral("systemctl");
        arguments = {QStringLiteral("--failed"), QStringLiteral("--no-pager")};
    } else if (actionId == QLatin1String("deployment")) {
        program = QStringLiteral("bootc");
        arguments = {QStringLiteral("status"), QStringLiteral("--json")};
    } else if (actionId == QLatin1String("flatpaks")) {
        program = QStringLiteral("flatpak");
        arguments = {QStringLiteral("list"), QStringLiteral("--system"),
                     QStringLiteral("--app"), QStringLiteral("--columns=application,name,origin")};
    } else {
        emit commandError(QStringLiteral("Unknown or unsupported diagnostic action."));
        return;
    }

    emit commandStarted(program + QLatin1Char(' ') + arguments.join(QLatin1Char(' ')));
    m_process.start(program, arguments);
    m_timeout.start();
}

void DoctorBackend::stopCommand()
{
    if (busy())
        m_process.kill();
}
