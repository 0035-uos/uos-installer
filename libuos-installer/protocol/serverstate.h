#ifndef SERVERSTATE_H
#define SERVERSTATE_H

#include "utils/propertyreflection.h"
#include "utils/singleton.h"

class ServerState : public PropertyReflection, public Singleton<ServerState>
{
    Q_OBJECT
    Q_PROPERTY(int state READ getState WRITE setState)
    Q_PROPERTY(bool loadPackagesDefault READ getLoadPackagesDefault WRITE setLoadPackagesDefault)
public:
    explicit ServerState(QObject *parent = nullptr);

    int getState() const;
    void setState(int value);

    bool getLoadPackagesDefault() const;
    void setLoadPackagesDefault(bool value);

private:
    int state;
    bool loadPackagesDefault;
};

#endif // SERVERSTATE_H
