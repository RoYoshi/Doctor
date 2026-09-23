#pragma once

#include <QObject>
#include <QProcess>

class DoctorBackend : public QObject
{
    Q_OBJECT

public:
    explicit DoctorBackend(QObject *parent = nullptr);

    Q_INVOKABLE void runCommand(
        const QString &program,
        const QStringList &arguments
    );

    Q_INVOKABLE void stopCommand();

signals:
    void consoleOutput(const QString &text);
    void commandStarted(const QString &command);
    void commandFinished(int exitCode);
    void commandError(const QString &error);

private:
    QProcess m_process;
};