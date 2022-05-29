#include "systeminfoconfig.h"
#include "gjsonitem.h"
#include "gsysinfo.h"
#include "parameter.h"
#include "protocol/serverstate.h"
#include "userinput.h"
#ifdef DEEEPIN_PW_CHECK
#include "deepin_pw_check.h"
#endif
#include <QDebug>

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
        QString username  = getusername();
        QString password  = getpassword();

        GJsonItem user_item;
        user_item.appendValue("username", username);
        user_item.appendValue("password", password);
        user_item.appendValue("rootpassword", password);
        user_item.appendValue("hostname", username + "-pc");
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

QString SystemInfoConfig::getusername()
{
    QString outResout;
    UserInput::ReadInput(outResout, std::bind(&SystemInfoConfig::usernameCheck, this, std::placeholders::_1), tr("please input username"));
    return outResout;
}

QString SystemInfoConfig::getpassword()
{
    QString outResout;
    UserInput::ReadInput(outResout, std::bind(&SystemInfoConfig::passwordCheck, this, std::placeholders::_1), tr("please input password"));
    return outResout;
}

bool SystemInfoConfig::usernameCheck(const QString &username)
{
    static QStringList ignore = ServerState::Instance()->getIgnoreUsername().split(":", QString::SkipEmptyParts);
    if (ignore.contains(username)) {
        std::cout << tr("The user name already exitsts").toStdString() << std::endl;
        return false;
    }
    return true;
}

bool SystemInfoConfig::passwordCheck(const QString &password)
{
#ifdef DEEEPIN_PW_CHECK
    // 这里可以调用dde-pw-check检查，使用dde-pw-check要记得添加依赖
    if (password.length() < 2) {
        std::cout << tr("Please enter a longer passwrod").toStdString() << std::endl;
        return false;
    }
#else
#endif
    return  true;
}
