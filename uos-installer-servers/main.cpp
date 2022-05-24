#include <QCoreApplication>

#include "scripts/gscriptsrunabstract.h"
#include "protocol/gprotomanager.h"
#include "gmanager.h"
#include "log/DLog"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

#if 0
#ifndef QT_DEBUG
    QString log_file(QString("%1/.cache/deepin/deepin-pxe-tools.log").arg(getenv("HOME")));
#else
    QString log_file("/tmp/uos-installer-server.log");
#endif
    DLogManager::setLogFormat("%{time}{yyyy-MM-dd, HH:mm:ss.zzz} [%{type:-7}] "
                              "[%{function:-35} %{line}] %{message}\n");
    DLogManager::setlogFilePath(log_file);
    DLogManager::registerConsoleAppender();
    DLogManager::registerFileAppender();
#endif

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
