#ifndef GLOCALSOCKET_H
#define GLOCALSOCKET_H

#include "communication/communicationinterface.h"

class QLocalServer;
class QLocalSocket;
class GLocalSocket : public CommunicationInterface
{
    Q_OBJECT
public:
    explicit GLocalSocket(QObject *parent = nullptr);
    ~GLocalSocket();

protected slots:
    void recvData(const QByteArray& data);
protected:
    bool init();

private slots:
    void newConnection();

private:

private:
    QLocalServer* m_server;
};

#endif // GLOCALSOCKET_H
