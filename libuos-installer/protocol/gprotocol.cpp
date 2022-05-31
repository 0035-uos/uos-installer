#include "gprotocol.h"

#include "../utils/commands.h"
#include "gpartedinfo.h"
#include "gsysinfo.h"


#include <QFile>
#include <QByteArray>


GProtocol::GProtocol(QObject *parent) : QObject(parent)
{

}

int GProtocol::getDataFromFrame(const QByteArray &begin, const QByteArray &end, QByteArray &frame, QByteArray &data)
{
    int i1 = frame.indexOf(begin);
    if (i1 > 0) {
        frame.remove(0, i1);
    } else if (i1 < 0) {
        return 1;
    }
    frame.remove(0, begin.length());
    i1 = frame.indexOf(end);
    if (i1 < 0) {
        return 2;
    } else if (i1 == 0) {
        return 3;
    }
    data = frame.mid(0, i1);
    frame.remove(0, i1 + type_end.length());
    return 0;
}

int GProtocol::getFrameFromFile(const QString &filename, QByteArray &frame)
{
    QFile file(filename);
    if (!file.open(QFile::ReadOnly)) {
        return 1;
    }
    QByteArray tmp = file.readAll();
    file.close();
    frame = generateFrame(type_file, tmp);
    return 0;
}

int GProtocol::getFrameFromCmd(const QByteArray &cmd, QByteArray &frame)
{
    Q_UNUSED(cmd);
    Q_UNUSED(frame);
    return 0;
}

QByteArray GProtocol::generateFrame(const QByteArray &cmd, const QByteArray &data)
{
    QByteArray frame;
    frame.append(proto_begin);
    frame.append(type_begin);
    frame.append(cmd);
    frame.append(type_end);
    frame.append(content_begin);
    frame.append(data);
    frame.append(content_end);
    frame.append(proto_end);
    return frame;
}

QByteArray GProtocol::getDevicesFrame()
{
    return generateFrame(cmd_get_devices, "devices");
}

QByteArray GProtocol::getPartedFrame(GJson* json)
{
    return generateFrame(cmd_set_parted, json->data());
}

QByteArray GProtocol::getSysInfoFrame(GJson *json)
{
    return generateFrame(cmd_set_sys_info, json->data());
}

QByteArray GProtocol::startInstallFrame()
{
    return generateFrame(cmd_start_install, "startInstall");
}

QByteArray GProtocol::getNotifyFrame(const QByteArray &data)
{
    return  generateFrame(cmd_notify_response, data);
}

QByteArray GProtocol::exitServerFrame()
{
    return  generateFrame(cmd_exit_server, "exit");
}
