#include "systeminfoconfig.h"
#include "gjsonitem.h"
#include "gsysinfo.h"
#include "parameter.h"
#include "protocol/serverstate.h"
#include "userinput.h"
#include <deepin_pw_check.h>
#include <iostream>
#include <QDebug>
#include <QRegExp>
#include <QSettings>

#define PASSWORD_LEVEL 0

SystemInfoConfig::SystemInfoConfig(QObject *parent) : ConfigInterface(parent)
{
    m_data = new GSysInfo(Parameter::Instance()->getSysInfoFile());
}

void SystemInfoConfig::initData()
{
}

void SystemInfoConfig::run()
{
    { // test
        int c1 = m_language.count();
        for (int i = 0;i < c1; i++) {
            qInfo() << i+1 << m_language.value(i).value("name") << m_language.value(i).value("locale") ;
        }
        qInfo() << "====================";
        int c2 = m_timerzone.count();
        for (int i = 0;i < c2; i++) {
            //qInfo() << i+1 << m_timerzone.value(i).value("country") << m_timerzone.value(i).value("timezone");
        }
        qInfo() << "====================";
        GArrayJson array;
        qInfo() << m_xkblayout.valueArray("layout_list", array);
        m_xkblayout.commitData();
        int c3 = array.count();
        for (int i = 0;i < c3; i++) {
            qInfo() << i+1 << array.value(i).value("name") << array.value(i).value("description");
            GArrayJson variantList(array.value(i).value("variantList").toLocal8Bit());
            for (int j = 0; j < variantList.count(); j++) {
                qInfo() << "\t" << variantList.value(j).value("name") << variantList.value(j).value("description");
            }
        }
        qInfo() << "====================";
    }
    // 这里可以增加用户自定义设置
    {
        m_username  = getusername();
        QString password  = getpassword();

        GJsonItem user_item;
        user_item.appendValue("username", m_username);
        user_item.appendValue("password", password);
        user_item.appendValue("rootpassword", password);
        user_item.appendValue("hostname", m_username + "-pc");
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
    int usernameMinLen = 3;
    int usernameMaxLen = 32;
    static QStringList ignore = ServerState::Instance()->getIgnoreUsername().split(":", QString::SkipEmptyParts);
    if ((username.isEmpty() && (usernameMinLen > 0))) {
        std::cout << tr("Username can only contain lowercase letters, numbers and symbols (_-)").toStdString() << std::endl;
        return false;
    } else if ((username.length() > usernameMaxLen) || (username.length() < usernameMinLen)) {
        std::cout << tr("Please input a username longer than %1 characters and "
                        "shorter than %2 characters")
                     .arg(usernameMinLen)
                     .arg(usernameMaxLen).toStdString() << std::endl;
        return false;
    }  else if (username.at(0).unicode() < 'a' || username.at(0).unicode() > 'z') {
        std::cout << tr("The first letter must be in lowercase").toStdString() << std::endl;
        return false;
    } else if (!(QRegExp("[a-z][a-z0-9_-]*").exactMatch(username))) {
        std::cout << tr("Username can only contain lowercase letters, numbers and symbols (_-)").toStdString() << std::endl;
        return false;
    } else if (ignore.contains(username)) {
        std::cout << tr("The user name already exitsts").toStdString() << std::endl;
        return false;
    }
    return true;
}

bool SystemInfoConfig::passwordCheck(const QString &password)
{
    PW_ERROR_TYPE type = deepin_pw_check(m_username.toStdString().c_str(), password.toStdString().c_str(), PASSWORD_LEVEL, nullptr);
//    qDebug() << "password checked: " << err_to_string(type);

    int passwdMinLen = get_pw_min_length(PASSWORD_LEVEL);
    int passwdMaxLen = get_pw_max_length(PASSWORD_LEVEL);
    bool ret = false;

    static QMap<PW_ERROR_TYPE, QString> err_string {
        {PW_ERR_PASSWORD_EMPTY, tr("The password cannot be empty​")},
        {PW_ERR_LENGTH_SHORT, tr("Password must be between %1 and %2 characters")
                    .arg(passwdMinLen).arg(passwdMaxLen)},
        {PW_ERR_CHARACTER_INVALID, tr("The password should contain at least %1 of the four available character types: "
                                      "lowercase letters, uppercase letters, numbers, and symbols (~`!@#$%^&*()-_+=|\\{}[]:\"'<>,.?/)")
                    .arg(get_pw_min_character_type(PASSWORD_LEVEL))},
        {PW_ERR_PALINDROME, tr("Password must not contain more than %1 palindrome characters")
                    .arg(get_pw_palimdrome_num(PASSWORD_LEVEL))},
        {PW_ERR_WORD, tr("Do not use common words and combinations as password")},
        {PW_ERR_PW_MONOTONE, tr("Create a strong password please")},
        {PW_ERR_PW_REPEAT, tr("It does not meet password rules")}
    };

    err_string [PW_ERR_LENGTH_LONG] = err_string[PW_ERR_LENGTH_SHORT];
    err_string [PW_ERR_PW_CONSECUTIVE_SAME] = err_string [PW_ERR_PW_MONOTONE];
    err_string [PW_ERR_PW_FIRST_UPPERM] = err_string [PW_ERR_PARA] = err_string [PW_ERR_INTERNAL] =
            err_string [PW_ERR_USER] = err_string [PW_ERR_MAX] = err_string [PW_ERR_PW_REPEAT];

    if (type == PW_NO_ERR) {
        ret = true;
    } else if (err_string.contains(type)) {
        std::cout << err_string.value(type).toStdString() << std::endl;
    } else {
        std::cout << tr("Unknown error").toStdString() << std::endl;
    }
    return ret;
}

void SystemInfoConfig::setTimerzone(const GTimezone &timerzone)
{
    m_timerzone = timerzone;
}

void SystemInfoConfig::setXkblayout(const GXkbLayout &xkblayout)
{
    m_xkblayout = xkblayout;
}

void SystemInfoConfig::setLanguage(const GLanguageInfo &language)
{
    m_language = language;
}
