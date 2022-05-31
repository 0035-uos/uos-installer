#include <QCoreApplication>

#include "scripts/gscriptsrunabstract.h"
#include "protocol/gprotomanager.h"
#include "gmanager.h"
#include "log/DLog"
#include "utils/utils.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // Initialize log service.
    DLogManager::setLogFormat("%{time}{yyyy-MM-dd, HH:mm:ss.zzz} [%{type:-7}] "
                              "[%{function:-35} %{line}] %{message}\n");
    DLogManager::setlogFilePath(Tools::installer_server_log_file);
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
