#ifndef GHEARTBEATTHREAD_H
#define GHEARTBEATTHREAD_H

#include "utils/singleton.h"

#include <QObject>

class GHeartBeatThread : public QObject, public Singleton<GHeartBeatThread>
{
    Q_OBJECT
    Q_PROPERTY(bool m_exit WRITE setExit)
public:
    explicit GHeartBeatThread(QObject *parent = nullptr);

    void setExit(bool exit);

signals:
    void sigSend(const QByteArray&);
signals:
    void sigStartHeartBeat(ulong);

public slots:
    void startHeartBeat(ulong interval); // msec

private:
    bool m_exit;
};

#endif // GHEARTBEATTHREAD_H
