#include <QCoreApplication>

#include "protocol/gprotocol.h"
#include "communication/communicationinterface.h"
#include "glocalmanager.h"
#include "gpartedinfo.h"
#include "gsysinfo.h"
#include "gpartedinfo.h"
#include "gparteditem.h"
#include "gsysinfo.h"

#include <QDebug>
#include <QDir>
#include <QFileInfo>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    a.setObjectName("uos-installer");

#if 0
    /// eg  示例程序，后期删除
    /// 生成分区参数文件示例
    GPartedInfo parted;
    {
        GPartedItem item;
        item.setFilesystem("ext4");
        item.setlabel("Roota");
        item.setMountPoint("/");
        item.setUsage("roota");
        parted.appendItem(&item);
    }
    {
        GPartedItem item;
        item.setFilesystem("ext4");
        item.setlabel("Rootb");
        item.setMountPoint("/boot");
        item.setUsage("rootb");
        parted.appendItem(&item);
    }
    // ...
    parted.commitData();// 提交数据
    /// 导出到文件
    parted.exportfile("./parted.json");
    /// 编写流程时不必导出文件直接调用数据即可
    // socket->writeData(parted.data());

    GSysInfo sys;
    {
        GJsonItem item;
        item.appendValue("username", "deepin");
        item.appendValue("passwd", "deepin12!");

        sys.appendItem("user", &item);
    }
    sys.commitData();
    sys.exportfile("./sysinfo.json");
    /// 同分区参数
#endif

//    QDir dir("/installer");
//    if (!(dir.exists())) {
//        QDir("/").mkdir("/installer");
//    }
//    if (!(dir.exists())) {
//        qWarning() << "/installer create failed";
//        return 0;
//    }


    CommunicationInterface *socket = GLocalManager::Instance()->communication();
    socket->start();
    GLocalManager::Instance()->startInstall();
    return a.exec();
}
