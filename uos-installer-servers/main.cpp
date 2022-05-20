#include <QCoreApplication>

#include "scripts/gscriptsrunabstract.h"
#include "protocol/gprotomanager.h"
#include "gmanager.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    a.setObjectName("uos-installer");
    GManager manager;
    manager.init();
    manager.sigStartCommunication();



    return a.exec();
}
