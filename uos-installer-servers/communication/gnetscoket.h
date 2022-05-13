#ifndef GNETSCOKET_H
#define GNETSCOKET_H

#include "communication/communicationinterface.h"

class QTcpServer;
class GNetScoket : public CommunicationInterface
{
    Q_OBJECT
public:
    explicit GNetScoket(QObject *parent = nullptr);
    ~GNetScoket();

protected slots:
    void recvData(const QByteArray& data);
protected:
    bool init();

private slots:
    void newConnection();
protected:
    QTcpServer* m_server;
};

#endif // GNETSCOKET_H
