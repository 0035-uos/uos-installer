#ifndef COMMUNICATIONINTERFACE_H
#define COMMUNICATIONINTERFACE_H


#include <QObject>
#include <QIODevice>

class CommunicationInterface : public QObject
{
    Q_OBJECT
public:
    explicit CommunicationInterface(QObject* parent = nullptr);
    ~CommunicationInterface();

public slots:
    virtual bool start();
    virtual void send(const QByteArray& data);

protected slots:
    virtual bool init();
    virtual void close();
    virtual void recvData(const QByteArray& data);

signals:
    void sigRecvData(const QByteArray& data);

protected slots:
    virtual void appendDevice(QIODevice* dev);
    virtual void writeData(const QByteArray& data);
    virtual void readData();
protected:
    QList<QIODevice*> m_ioDevices;
};

#endif // COMMUNICATIONINTERFACE_H
