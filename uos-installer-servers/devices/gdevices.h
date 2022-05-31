#ifndef GDEVICES_H
#define GDEVICES_H

#include "utils/singleton.h"

#include <QObject>
#include <QList>
#include <QJsonArray>
#include <QJsonObject>

class DeviceInfo;
class PartitionInfo;
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
    void scanDisk(void* device, QList<PartitionInfo*> &partitions);
private:
    QList<DeviceInfo*> m_devices;
};

#endif // GDEVICES_H
