#ifndef GCOMMSERVER_H
#define GCOMMSERVER_H


#include "utils/singleton.h"


#include <QObject>

class GCommServer : public QObject, public Singleton<GCommServer>
{
    Q_OBJECT
public:
    explicit GCommServer(QObject *parent = nullptr);
    ~GCommServer();

signals:

public slots:
    void start();

    void sendData(const QByteArray& data);
protected:

private slots:

};

#endif // GCOMMSERVER_H
