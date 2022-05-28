#ifndef SYSTEMINFOCONFIG_H
#define SYSTEMINFOCONFIG_H

#include "utils/singleton.h"
#include "configinterface.h"

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

private:
    QString getusername();
    QString getpassword();
    bool usernameCheck(const QString& username);
    bool passwordCheck(const QString& password);

private:
    GSysInfo* m_data;
};

#endif // SYSTEMINFOCONFIG_H
