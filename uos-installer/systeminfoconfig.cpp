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
    {
        GJsonItem user_item;
        user_item.appendValue("username", "deepin");
        user_item.appendValue("password", "deepin12!");
        user_item.appendValue("rootpassword", "deepin12!");
        user_item.appendValue("hostname", "deepin-pc");
        m_data->appendItem("user", &user_item);
    }
    {
        GJsonItem item;
        item.appendValue("xkblayout", "");
        item.appendValue("xkbvariant", "");
        item.appendValue("xkboptions", "");
        item.appendValue("xkbmodel", "");
        m_data->appendItem("keyboard", &item);
    }
    {
        GJsonItem item;
        item.appendValue("locale", "");
        m_data->appendItem("language", &item);
    }
    {
        GJsonItem item;
        item.appendValue("DI_TIMEZONE", "Asia/Shanghai");
        item.appendValue("DI_IS_LOCAL_TIME", "true");
        item.appendValue("DI_IS_ENABLE_NTP", "true");
        item.appendValue("SET_DATE_TIME", "2022-05-17 15:39:13");
        item.appendValue("timezone_is_sysnc", "true");
        m_data->appendItem("timezone", &item);
    }
    m_data->commitData(); // 数据确认后，提交修改
}

void SystemInfoConfig::cleanData()
{

}

GJson *SystemInfoConfig::data()
{
    return m_data;
}
