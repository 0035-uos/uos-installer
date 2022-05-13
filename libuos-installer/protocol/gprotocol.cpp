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
    frame.append(proto_begin);
    frame.append(type_begin);
    frame.append(type_file);
    frame.append(type_end);
    frame.append(content_begin);
    frame.append(file.readAll());
    frame.append(content_end);
    frame.append(proto_end);
    file.close();
    return 0;
}

int GProtocol::getFrameFromCmd(const QByteArray &cmd, QByteArray &frame)
{
    Q_UNUSED(cmd);
    Q_UNUSED(frame);
    return 0;
}

QByteArray GProtocol::getDevicesFrame()
{
    QByteArray frame;
    frame.append(proto_begin);
    frame.append(type_begin);
    frame.append(cmd_get_devices);
    frame.append(type_end);
    frame.append(content_begin);
    frame.append("1");
    frame.append(content_end);
    frame.append(proto_end);
    return frame;
}

QByteArray GProtocol::getPartedFrame(GJson* json)
{
    QByteArray frame;
    frame.append(proto_begin);
    frame.append(type_begin);
    frame.append(cmd_set_parted);
    frame.append(type_end);
    frame.append(content_begin);
    frame.append(json->data());
    frame.append(content_end);
    frame.append(proto_end);
    return frame;
}

QByteArray GProtocol::getSysInfoFrame(GJson *json)
{
    QByteArray frame;
    frame.append(proto_begin);
    frame.append(type_begin);
    frame.append(cmd_set_sys_info);
    frame.append(type_end);
    frame.append(content_begin);
    frame.append(json->data());
    frame.append(content_end);
    frame.append(proto_end);
    return frame;
}

QByteArray GProtocol::startInstallFrame()
{
    QByteArray frame;
    frame.append(proto_begin);
    frame.append(type_begin);
    frame.append(cmd_start_install);
    frame.append(type_end);
    frame.append(content_begin);
    frame.append("3");
    frame.append(content_end);
    frame.append(proto_end);
    return frame;
}

QByteArray GProtocol::exitServerFrame()
{
    QByteArray frame;
    frame.append(proto_begin);
    frame.append(type_begin);
    frame.append(cmd_exit_server);
    frame.append(type_end);
    frame.append(content_begin);
    frame.append("4");
    frame.append(content_end);
    frame.append(proto_end);
    return frame;
}
