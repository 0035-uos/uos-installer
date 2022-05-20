#include "serverstate.h"

ServerState::ServerState(QObject *parent) : PropertyReflection(parent)
{

}

int ServerState::getState() const
{
    return state;
}

void ServerState::setState(int value)
{
    state = value;
}

bool ServerState::getLoadPackagesDefault() const
{
    return loadPackagesDefault;
}

void ServerState::setLoadPackagesDefault(bool value)
{
    loadPackagesDefault = value;
}
