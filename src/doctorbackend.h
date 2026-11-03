#pragma once

#include <QObject>
#include <QProcess>
#include <QString>
#include <QTimer>

// Read-only desktop diagnostics. Privileged actions are intentionally not part
// of this early Doctor build; FE-Xico Updater owns bootc modifications.
class DoctorBackend : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString osName READ osName NOTIFY snapshotChanged)
    Q_PROPERTY(QString feXicoVersion READ feXicoVersion NOTIFY snapshotChanged)
    Q_PROPERTY(QString kernelText READ kernelText NOTIFY snapshotChanged)
    Q_PROPERTY(QString cpuText READ cpuText NOTIFY snapshotChanged)
    Q_PROPERTY(QString memoryText READ memoryText NOTIFY snapshotChanged)
    Q_PROPERTY(QString diskText READ diskText NOTIFY snapshotChanged)
    Q_PROPERTY(QString uptimeText READ uptimeText NOTIFY snapshotChanged)
    Q_PROPERTY(QString gpuText READ gpuText NOTIFY snapshotChanged)
    Q_PROPERTY(bool busy READ busy NOTIFY busyChanged)

public:
    explicit DoctorBackend(QObject *parent = nullptr);

    QString osName() const { return m_osName; }
    QString feXicoVersion() const { return m_feXicoVersion; }
    QString kernelText() const { return m_kernelText; }
    QString cpuText() const { return m_cpuText; }
    QString memoryText() const { return m_memoryText; }
    QString diskText() const { return m_diskText; }
    QString uptimeText() const { return m_uptimeText; }
    QString gpuText() const { return m_gpuText; }
    bool busy() const { return m_process.state() != QProcess::NotRunning; }

    Q_INVOKABLE void refreshSystemInfo();
    Q_INVOKABLE void runAction(const QString &actionId);
    Q_INVOKABLE void stopCommand();

signals:
    void snapshotChanged();
    void busyChanged();
    void consoleOutput(const QString &text);
    void commandStarted(const QString &command);
    void commandFinished(int exitCode);
    void commandError(const QString &error);

private:
    QProcess m_process;
    QTimer m_timeout;
    QString m_osName;
    QString m_feXicoVersion;
    QString m_kernelText;
    QString m_cpuText;
    QString m_memoryText;
    QString m_diskText;
    QString m_uptimeText;
    QString m_gpuText;
};
