#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

#include "utils/singleton.h"

#include <QObject>
#include <QSettings>

class SettingsManager : public QObject, public Singleton<SettingsManager>
{
    Q_OBJECT
public:
    explicit SettingsManager(QObject *parent = nullptr);

signals:

public slots:

private:
    QSettings m_settings;
};

#endif // SETTINGSMANAGER_H
