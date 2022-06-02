#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

#include "utils/singleton.h"
#include "utils/propertyreflection.h"
#include "gjson.h"
#include "gjsonitem.h"

class SettingsManager : public GJson,  public GJsonItem, public Singleton<SettingsManager>
{
public:
    explicit SettingsManager();

    bool commitData();


private:
    QJsonArray array() const;

private:
    bool aotuDetectEfi{false};
    bool fixEfi{false};
    bool fixMsdoss{false};
};

#endif // SETTINGSMANAGER_H
