#ifndef SERVERSTATE_H
#define SERVERSTATE_H

#include "utils/propertyreflection.h"
#include "utils/singleton.h"

class ServerState : public PropertyReflection, public Singleton<ServerState>
{
    Q_OBJECT
    Q_PROPERTY(int state READ getState WRITE setState)
public:
    explicit ServerState(QObject *parent = nullptr);

    int getState() const;
    void setState(int value);

private:
    int state;
};

#endif // SERVERSTATE_H
