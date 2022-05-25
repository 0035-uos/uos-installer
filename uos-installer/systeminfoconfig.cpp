#include "systeminfoconfig.h"
#include "gjsonitem.h"
#include "gsysinfo.h"
#include "parameter.h"

#include <iostream>

SystemInfoConfig::SystemInfoConfig(QObject *parent) : ConfigInterface(parent)
{
    m_data = new GSysInfo(Parameter::Instance()->getSysInfoFile());
}

void SystemInfoConfig::initData()
{
}

void SystemInfoConfig::run()
{
    // 这里可以增加用户自定义设置
    GJsonItem user_item;
    user_item.appendValue("username", "deepin");
    user_item.appendValue("password", "deepin12!");
    m_data->appendItem("user", &user_item);
    m_data->commitData(); // 数据确认后，提交修改
}

void SystemInfoConfig::cleanData()
{

}

GJson *SystemInfoConfig::data()
{
    return m_data;
}
