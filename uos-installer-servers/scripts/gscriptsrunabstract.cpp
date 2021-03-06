#include "gscriptsrunabstract.h"

#include <QTextCodec>
#include <QThread>
#include <QDebug>

static QTextCodec* codec_system = QTextCodec::codecForName("System");
#define PRINT_INFO(x) (codec_system ? codec_system->toUnicode(x) : x)

GScriptsRunAbstract::GScriptsRunAbstract(QObject *parent) :
    QObject(parent)
{
    if (!codec_system) {
        codec_system = QTextCodec::codecForName("UTF-8");
    }
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
            qInfo() << PRINT_INFO(an);
        process->deleteLater();
    });
    connect(process, &QProcess::started, this, []{
        qInfo() << "start install";
    });
    connect(process, &QProcess::readyReadStandardOutput, this, [process]{
        qInfo() << PRINT_INFO(process->readAllStandardOutput());
    });
    connect(process, &QProcess::readyReadStandardError, this, [process]{
        qWarning() << PRINT_INFO(process->readAllStandardError());
    });
    process->start(m_command, m_args);

    process->waitForStarted(3000);
    bool ret = process->waitForFinished(timeout);
    emit finished(m_command, QString("{return:%1}").arg(ret?"true":"false").toLocal8Bit());
    return 0;
}

void GScriptsRunAbstract::run()
{
    m_quit = true;
}

