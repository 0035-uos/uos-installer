#ifndef GLOCALMANAGER_H
#define GLOCALMANAGER_H

#include "utils/singleton.h"
#include "gnotifyinfo.h"

#include <QObject>

class CommunicationInterface;
class GLocalManager : public QObject, public Singleton<GLocalManager>
{
    Q_OBJECT
public:
    explicit GLocalManager(QObject *parent = nullptr);

    CommunicationInterface* communication();

    void startInstall();

public slots:
    void recvData(const QByteArray& type, const QByteArray& frame);
    void heartPackets();
    void notifyResponse(const GNotifyInfo& info);
    void next();

signals:
    void sigStart();
private:
    CommunicationInterface* m_inter;

    QList<QByteArray> m_flowList;

    bool m_serverReady;
};

#endif // GLOCALMANAGER_H
