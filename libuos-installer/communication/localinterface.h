#ifndef LOCALINTERFACE_H
#define LOCALINTERFACE_H

#include <QObject>

class LocalInterface : public QObject
{
    Q_OBJECT
public:
    explicit LocalInterface(QObject *parent = nullptr);

public slots:
    virtual bool initConnection() = 0;
    virtual void disConnection() = 0;
    virtual void writeData(const QByteArray& data) = 0;

public:
    virtual void recvData(QByteArray& data, int timeout = 30000) = 0;
};

#endif // LOCALINTERFACE_H
