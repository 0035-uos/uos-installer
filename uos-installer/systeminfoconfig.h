#ifndef SYSTEMINFOCONFIG_H
#define SYSTEMINFOCONFIG_H

#include "utils/singleton.h"
#include "configinterface.h"
#include "glanguageinfo.h"
#include "gxkblayout.h"
#include "gtimezone.h"

class GSysInfo;
class SystemInfoConfig : public ConfigInterface, public Singleton<SystemInfoConfig>
{
    Q_OBJECT
public:
    explicit SystemInfoConfig(QObject *parent = nullptr);

    void initData();
    void run();
    void cleanData();
    GJson* data();

    void setLanguage(const GLanguageInfo &language);

    void setXkblayout(const GXkbLayout &xkblayout);

    void setTimerzone(const GTimezone &timerzone);

private:
    QString getusername();
    QString getpassword();
    bool usernameCheck(const QString& username);
    bool passwordCheck(const QString& password);

private:
    GSysInfo* m_data;

    GLanguageInfo m_language;
    GXkbLayout m_xkblayout;
    GTimezone m_timerzone;
};

#endif // SYSTEMINFOCONFIG_H
