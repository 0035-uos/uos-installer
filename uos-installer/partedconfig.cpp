#include "partedconfig.h"
#include "gpartedinfo.h"
#include "parameter.h"

#include <QDebug>

#include <iostream>

static const qint64 GByte = 1024*1024*1024;

PartedConfig::PartedConfig(QObject *parent) : ConfigInterface(parent)
{
    m_data = new GPartedInfo(Parameter::Instance()->getPartedFile());
}

void PartedConfig::initData()
{
    m_devicelist.clear();
}

void PartedConfig::run()
{
    for (const DeviceInfo* &info : m_devicelist) {
        qInfo() << info->getPath() << info->getSectorSize() << info->getLength() << (1.0 * info->getSectorSize() * info->getLength()/GByte);
    }

}

void PartedConfig::cleanData()
{

}

GJson *PartedConfig::data()
{
    return m_data;
}

void PartedConfig::appendDevice(const DeviceInfo *info)
{
    m_devicelist.append(info);
}
