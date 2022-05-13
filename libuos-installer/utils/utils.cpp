#include "utils.h"

#include <QFile>
#include <QByteArray>
#include <QDebug>

namespace Tools {



QString scanValidFileName(const QString &path, const QString &basename)
{
    QString fp = path;
    if (!(path.endsWith("/"))) {
        fp.append("/");
    }
    int k = 2;
    QString fn = fp + basename + QString("_1");
    while (QFile::exists(fn)) {
        fn = QString("%1%2_%3").arg(fp).arg(basename).arg(k++);
    }
    return fn;
}

Installation installation()
{
    Installation mode = WTI_Default;
    QFile file("/proc/cmdline");
    if (file.exists() && file.open(QFile::ReadOnly)) {
        QByteArray cmdline = file.readAll();
        file.close();
        if (cmdline.contains("nfsroot")) {
            mode = WTI_PXE;
        } else if (cmdline.contains("install-mode=local")) {
            mode = WTI_Local;
        } else if (cmdline.contains("install-mode=serialport")) {
            mode = WTI_SerialPort;
        } else if (cmdline.contains("install-mode=socket")) {
            mode = WTI_Socket;
        }
    }

    return mode;
}






}
