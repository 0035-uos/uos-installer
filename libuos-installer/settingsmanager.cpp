#include "settingsmanager.h"

#include <QDebug>



SettingsManager::SettingsManager() :
    GJson(), GJsonItem ()
{

}

bool SettingsManager::commitData()
{
    return GJson::commitData(tojson());
}


QJsonArray SettingsManager::array() const
{
    return QJsonArray();
}
