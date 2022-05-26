#include "utils.h"

#include <QFile>
#include <QByteArray>
#include <QMap>
#include <QProcess>
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
    static const Installation mode = []() {
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
    }();
    return mode;
}

QString getCurrentPlatform()
{
    static const QMap<QString, QString> arch_map{ { "x86_64",  "x86" },
                                           { "i386", "x86" },
                                           { "i686", "x86" },
                                           { "amd64", "x86" },
                                           { "x86", "x86" },
                                           { "sw_64", "sw" },
                                           { "mips64", "loongson" },
                                           { "loongarch64", "loongarch64" },
                                           { "aarch64", "arm" } };
    static const QString platform = []() {
        QString res;
        QProcess p;
        p.start("uname -m");
        p.waitForFinished();
        res = p.readAllStandardOutput().trimmed();
        return res;
    }();
    return arch_map[platform];

}

bool is_sw()
{
    return (getCurrentPlatform() == "sw");
}

bool is_loongson()
{
    return (getCurrentPlatform() == "loongson");
}

bool is_loongarch64()
{
    return (getCurrentPlatform() == "loongarch64");
}

QString ReadFile(const QString &path)
{
    QFile file(path);
    if (file.exists()) {
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qWarning() << "ReadFile() failed to open" << path;
            return "";
        }
        const QString &str = QString::fromUtf8(file.readAll());
        file.close();
        return str;
    } else {
        qWarning() << "ReadFileContent() file not found: " << path;
        return "";
    }
}







}
