#ifndef GSERIALPORT_H
#define GSERIALPORT_H

#include "communication/communicationinterface.h"

#include <QList>


class QSerialPort;
class GSerialPort : public CommunicationInterface
{
public:
    explicit GSerialPort(QObject *parent = nullptr);

public slots:
    void send(const QByteArray& data);
protected:
    bool init();

private slots:
    void NewData();

private:
    QSerialPort* m_server;
};

#endif // GSERIALPORT_H
