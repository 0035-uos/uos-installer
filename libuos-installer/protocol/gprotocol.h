#ifndef GPROTOCOL_H
#define GPROTOCOL_H

#include "serverstate.h"

#include <QObject>

class GJson;
class GProtocol : public QObject
{
    Q_OBJECT
public:
    explicit GProtocol(QObject *parent = nullptr);


    static int getDataFromFrame(const QByteArray& begin, const QByteArray& end, QByteArray &frame, QByteArray &data);
    static int getFrameFromFile(const QString& filename, QByteArray& frame);

    static int getFrameFromCmd(const QByteArray& cmd, QByteArray& frame);
signals:

public slots:

public:
    static QByteArray generateFrame(const QByteArray& cmd, const QByteArray& data);
    static QByteArray getDevicesFrame();
    static QByteArray getPartedFrame(GJson *json);
    static QByteArray getSysInfoFrame(GJson* json);
    static QByteArray startInstallFrame();
    static QByteArray getNotifyFrame(const QByteArray& data);

    static QByteArray exitServerFrame();
};

#endif // GPROTOCOL_H
