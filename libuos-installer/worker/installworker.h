#ifndef INSTALLWORKER_H
#define INSTALLWORKER_H

#include "gnotifyinfo.h"
#include "glanguageinfo.h"
#include "gxkblayout.h"
#include "gtimezone.h"

class DeviceInfo;
class CommunicationInterface;
class InstallWorker : public QObject
{
    Q_OBJECT
public:
    explicit InstallWorker(QObject* parent = nullptr);

    virtual CommunicationInterface* communication();

    virtual void startInstall();

    virtual void installResult(const QByteArray& data);
public slots:
    virtual void recvData(const QByteArray& type, const QByteArray& frame);
    virtual void recvOtherData(const QByteArray& type, const QByteArray& frame);
    virtual void heartPackets();
    virtual void notifyResponse(const GNotifyInfo& info);
    virtual void next();

protected:
    virtual void setLanguage(const GLanguageInfo &language);
    virtual void setXkblayout(const GXkbLayout &xkblayout);
    virtual void setTimerzone(const GTimezone &timezone);
public:
    virtual void setComponent();
    virtual void setDevices(const QList<const DeviceInfo*>& devicelist);
    virtual void setParted();
    virtual void setSystemInfo();

signals:
    void sigStart();

protected:
    CommunicationInterface* m_inter;

    QList<QByteArray> m_flowList;

    bool m_serverReady;

    bool m_autoInstall;

    QList<QByteArray> m_commandList;
};

#endif // INSTALLWORKER_H
