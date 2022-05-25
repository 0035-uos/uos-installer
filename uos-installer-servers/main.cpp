#include <QCoreApplication>

#include "scripts/gscriptsrunabstract.h"
#include "protocol/gprotomanager.h"
#include "gmanager.h"
#include "log/DLog"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // Initialize log service.
    const char kLogFileName[] = "uos-installer-server.log";
    QString log_file;
#ifdef QT_DEBUG
        log_file = QString("/tmp/%1").arg(kLogFileName);
#else
        log_file = QString("/var/log/%1").arg(kLogFileName);
#endif
    DLogManager::setLogFormat("%{time}{yyyy-MM-dd, HH:mm:ss.zzz} [%{type:-7}] "
                              "[%{function:-35} %{line}] %{message}\n");
    DLogManager::setlogFilePath(log_file);
    DLogManager::registerConsoleAppender();
    DLogManager::registerFileAppender();

    QDir dir("/uos-installer");
    if (!(dir.exists())) {
        QDir("/").mkdir("/uos-installer");
    }
    if (!(dir.exists())) {
        qWarning() << "/installer create failed";
        return 0;
    }

    a.setObjectName("uos-installer");
    GManager manager;
    manager.init();
    manager.sigStartCommunication();


    return a.exec();
}
