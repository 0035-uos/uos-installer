#ifndef GDEVICES_H
#define GDEVICES_H

#include "utils/singleton.h"
#include "utils/deviceinfo.h"

#include <QObject>
#include <QList>
#include <QJsonArray>
#include <QJsonObject>

class GDevices : public QObject, public Singleton<GDevices>
{
    Q_OBJECT
public:
    explicit GDevices(QObject *parent = nullptr);

    const QList<DeviceInfo *> &Devices();
    QJsonArray DevicesJson() const;
signals:

public slots:

private:
    void scanDevices();

private:
    QList<DeviceInfo*> m_devices;
};

#endif // GDEVICES_H
