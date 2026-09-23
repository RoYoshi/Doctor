#include "doctorbackend.h"

DoctorBackend::DoctorBackend(QObject *parent)
    : QObject(parent)
{
    connect(
        &m_process,
        &QProcess::readyReadStandardOutput,
        this,
        [this]() {
            emit consoleOutput(
                QString::fromUtf8(m_process.readAllStandardOutput())
            );
        }
    );

    connect(
        &m_process,
        &QProcess::readyReadStandardError,
        this,
        [this]() {
            emit consoleOutput(
                QString::fromUtf8(m_process.readAllStandardError())
            );
        }
    );

    connect(
        &m_process,
        &QProcess::finished,
        this,
        [this](int exitCode, QProcess::ExitStatus) {
            emit commandFinished(exitCode);
        }
    );

    connect(
        &m_process,
        &QProcess::errorOccurred,
        this,
        [this](QProcess::ProcessError) {
            emit commandError(m_process.errorString());
        }
    );
}

void DoctorBackend::runCommand(
    const QString &program,
    const QStringList &arguments
)
{
    if (m_process.state() != QProcess::NotRunning)
        return;

    const QString command =
        program + " " + arguments.join(' ');

    emit commandStarted(command);

    m_process.start(program, arguments);
}

void DoctorBackend::stopCommand()
{
    if (m_process.state() != QProcess::NotRunning)
        m_process.terminate();
}