#include "gscriptsrunabstract.h"

#include <QThread>
#include <QDebug>


GScriptsRunAbstract::GScriptsRunAbstract(QObject *parent) :
    QObject(parent)
{
}

void GScriptsRunAbstract::startRun(const QString &cmd, const QStringList &args)
{
    m_command = cmd;
    m_args = args;
    m_future = std::async(std::launch::async, std::bind(&GScriptsRunAbstract::asyncThread, this, 10000));
}

void GScriptsRunAbstract::runCommand()
{
}

int GScriptsRunAbstract::asyncThread(int timeout)
{
    qInfo() << m_command << m_args << timeout;
    m_quit = false;
    QProcess *process = new QProcess;
    connect(process, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
          [process](int, QProcess::ExitStatus){
        QByteArray an = process->readAllStandardOutput();
        if (!an.isEmpty())
            qInfo() << an;
        process->deleteLater();
    });
    process->start(m_command, m_args);

    process->waitForStarted(3000);
    process->waitForFinished(timeout);
    return 0;
}

void GScriptsRunAbstract::run()
{

    m_quit = true;
}
