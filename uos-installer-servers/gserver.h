#ifndef GSERVER_H
#define GSERVER_H

#include <QObject>
#include <QList>

class QLocalServer;
class QLocalSocket;
class GServer : public QObject
{
    Q_OBJECT
public:
    explicit GServer(QObject *parent = nullptr);

signals:

public slots:
    bool start();

private slots:
    void newConnection();
    void NewData();

private:

private:
    QLocalServer* m_server;
    QList<QLocalSocket*> m_socketList;
};

#endif // GSERVER_H
