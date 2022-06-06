#ifndef GLOCALMANAGER_H
#define GLOCALMANAGER_H

#include "utils/singleton.h"
#include "gnotifyinfo.h"
#include "worker/installworker.h"

#include <QObject>

class CommunicationInterface;
class GLocalManager : public InstallWorker, public Singleton<GLocalManager>
{
    Q_OBJECT
public:
    explicit GLocalManager(QObject *parent = nullptr);

    CommunicationInterface* communication();

    void installResult(const QByteArray& data);
public slots:
    void recvOtherData(const QByteArray& type, const QByteArray& frame);
    void notifyResponse(const GNotifyInfo& info);

protected:
    virtual void setLanguage(const GLanguageInfo &language);
    virtual void setXkblayout(const GXkbLayout &xkblayout);
    virtual void setTimerzone(const GTimezone &timezone);
public:
    virtual void setComponent();
    virtual void setDevices(const QList<const DeviceInfo*>& devicelist);
    virtual void setParted();
    virtual void setSystemInfo();
};

#endif // GLOCALMANAGER_H
