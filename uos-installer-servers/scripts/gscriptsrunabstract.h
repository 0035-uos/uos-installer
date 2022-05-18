#ifndef GSCRIPTSRUNABSTRACT_H
#define GSCRIPTSRUNABSTRACT_H

#include <QObject>
#include <QProcess>

#include <future>
#include <thread>

class GScriptsRunAbstract : public QObject
{
    Q_OBJECT
public:
    explicit GScriptsRunAbstract(QObject *parent = nullptr);

    void waitFinished();
signals:
    void finished();

public slots:
    void startRun(const QString& cmd, const QStringList &args);

private slots:
    void runCommand();
private:
    int asyncThread(int timeout);
    void runScripts();
    void run();
private:
    std::future<int> m_future;
    QProcess m_process;
    bool m_quit{false};

    QString m_command;
    QStringList m_args;
};

#endif // GSCRIPTSRUNABSTRACT_H
