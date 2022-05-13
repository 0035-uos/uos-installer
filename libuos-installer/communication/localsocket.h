#ifndef LOCALSOCKET_H
#define LOCALSOCKET_H

#include "communication/localinterface.h"


class QLocalSocket;
class LocalSocket : public LocalInterface
{
    Q_OBJECT
public:
    explicit LocalSocket(QObject *parent = nullptr);

signals:

public slots:
    bool initConnection();
    void disConnection();
    void writeData(const QByteArray& data);

public:
    void recvData(QByteArray& data, int timeout = 30000);

private:
    QLocalSocket *m_socket;
};

#endif // LOCALSOCKET_H
