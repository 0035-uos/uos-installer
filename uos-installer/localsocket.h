#ifndef LOCALSOCKET_H
#define LOCALSOCKET_H

#include "communication/communicationinterface.h"

class QLocalSocket;
class LocalSocket : public CommunicationInterface
{
    Q_OBJECT
public:
    explicit LocalSocket(QObject *parent = nullptr);

protected slots:
    virtual bool init();

private:
    QLocalSocket *m_socket;
};

#endif // LOCALSOCKET_H
