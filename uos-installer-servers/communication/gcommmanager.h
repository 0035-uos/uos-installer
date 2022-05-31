#ifndef GCOMMMANAGER_H
#define GCOMMMANAGER_H

#include "utils/singleton.h"

#include <QObject>

class CommunicationInterface;
class GCommManager : public QObject, public Singleton<GCommManager>
{
    Q_OBJECT
public:
    explicit GCommManager(QObject *parent = nullptr);


    static CommunicationInterface* commInterface();
    static void release();

private:
    static CommunicationInterface* m_inter;


};

#endif // GCOMMMANAGER_H
