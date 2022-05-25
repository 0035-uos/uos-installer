#ifndef PARTEDCONFIG_H
#define PARTEDCONFIG_H

#include "utils/singleton.h"
#include "configinterface.h"
#include "utils/deviceinfo.h"

#include <QList>

class GPartedInfo;
class PartedConfig : public ConfigInterface, public Singleton<PartedConfig>
{
    Q_OBJECT
public:
    explicit PartedConfig(QObject *parent = nullptr);

    void initData();
    void run();
    void cleanData();
    GJson* data();

    void appendDevice(const DeviceInfo *info);
signals:

public slots:

private:
    GPartedInfo* m_data;
    QList<const DeviceInfo*> m_devicelist;
};

#endif // PARTEDCONFIG_H
