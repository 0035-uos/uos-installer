#include "gscriptsrunabstract.h"

#include <QThread>
#include <QDebug>


GScriptsRunAbstract::GScriptsRunAbstract(QObject *parent) :
    QObject(parent)
{
}

void GScriptsRunAbstract::waitFinished()
{
    m_future.get();
}

void GScriptsRunAbstract::startRun(const QString &cmd, const QStringList &args)
{
    m_command = cmd;
    m_args = args;
    m_future = std::async(std::launch::async, std::bind(&GScriptsRunAbstract::asyncThread, this, 7200000));
}

void GScriptsRunAbstract::runCommand()
{
}

int GScriptsRunAbstract::asyncThread(int timeout)
{
    qInfo() << m_command << m_args << timeout;
    m_quit = false;
    QProcess *process = new QProcess;
    process->setEnvironment(QProcess::systemEnvironment());
    connect(process, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
          [process](int, QProcess::ExitStatus){
        QByteArray an = process->readAllStandardOutput();
        if (!an.isEmpty())
            qInfo() << an;
        process->deleteLater();
    });
    connect(process, &QProcess::started, this, []{
        qInfo() << "start install";
    });
    connect(process, &QProcess::readyReadStandardOutput, this, [process]{
        qWarning() << process->readAllStandardOutput();
    });
    connect(process, &QProcess::readyReadStandardError, this, [process]{
        qWarning() << process->readAllStandardError();
    });
    process->start(m_command, m_args);

    process->waitForStarted(3000);
    process->waitForFinished(timeout);
    qInfo() << "finished";
    emit finished();
    return 0;
}

void GScriptsRunAbstract::run()
{

    m_quit = true;
}
