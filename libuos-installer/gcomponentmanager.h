#ifndef GCOMPONENTMANAGER_H
#define GCOMPONENTMANAGER_H

#include "utils/singleton.h"
#include "gjson.h"
#include <QObject>

class GComponentManager : public QObject, public GJson, public Singleton<GComponentManager>
{
    Q_OBJECT
public:
    explicit GComponentManager(QObject *parent = nullptr);

    bool state() const;

    QStringList componentList() const;
    QStringList packagesList(const QString &component, const QString& type = "default") const;

signals:

public slots:

private:
};

#endif // GCOMPONENTMANAGER_H
