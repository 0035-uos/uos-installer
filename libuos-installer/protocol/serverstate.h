#ifndef SERVERSTATE_H
#define SERVERSTATE_H

#include "utils/propertyreflection.h"
#include "utils/singleton.h"

class ServerState : public PropertyReflection, public Singleton<ServerState>
{
    Q_OBJECT
    Q_PROPERTY(int state READ getState WRITE setState)
    Q_PROPERTY(bool loadPackagesDefault READ getLoadPackagesDefault WRITE setLoadPackagesDefault)
    Q_PROPERTY(bool efi READ getEfi WRITE setEfi)

    Q_PROPERTY(bool bootValid READ getBootValid WRITE setBootValid)
    Q_PROPERTY(QString boot READ getBoot WRITE setBoot)
    Q_PROPERTY(QString cdrom READ getCdrom WRITE setCdrom)
    Q_PROPERTY(QString liveFileSystem READ getLiveFileSystem WRITE setLiveFileSystem)
    Q_PROPERTY(QString distribution READ getDistribution WRITE setDistribution)
    Q_PROPERTY(QString live READ getLive WRITE setLive)
    Q_PROPERTY(QString lupinRoot READ getLupinRoot WRITE setLupinRoot)

    Q_PROPERTY(QString partedFile READ getPartedFile WRITE setPartedFile)
    Q_PROPERTY(QString sysInfoFile READ getSysInfoFile WRITE setSysInfoFile)
    Q_PROPERTY(QString devicePath READ getDevicePath WRITE setDevicePath)
    Q_PROPERTY(bool autoInstall READ getAutoInstall WRITE setAutoInstall)

    Q_PROPERTY(qint64 buffers READ getBuffers WRITE setBuffers)
    Q_PROPERTY(qint64 cached READ getCached WRITE setCached)
    Q_PROPERTY(qint64 mem_available READ getMemAvailable WRITE setMemAvailable)
    Q_PROPERTY(qint64 mem_free READ getMemFree WRITE setMemFree)
    Q_PROPERTY(qint64 mem_total READ getMemTotal WRITE setMemTotal)
    Q_PROPERTY(qint64 swap_free READ getSwapFree WRITE setSwapFree)
    Q_PROPERTY(qint64 swap_total READ getSwapTotal WRITE setSwapTotal)

public:
    explicit ServerState(QObject *parent = nullptr);

    int getState() const;
    void setState(int value);

    QString getBoot() const;
    void setBoot(const QString &value);

    bool getLoadPackagesDefault() const;
    void setLoadPackagesDefault(bool value);

    bool getEfi() const;
    void setEfi(bool value);

    bool getBootValid() const;
    void setBootValid(bool value);

    QString getCdrom() const;
    void setCdrom(const QString &value);

    QString getLiveFileSystem() const;
    void setLiveFileSystem(const QString &value);

    QString getDistribution() const;
    void setDistribution(const QString &value);

    QString getLive() const;
    void setLive(const QString &value);

    QString getLupinRoot() const;
    void setLupinRoot(const QString &value);

    QString getPartedFile() const;
    void setPartedFile(const QString &value);

    QString getSysInfoFile() const;
    void setSysInfoFile(const QString &value);

    QString getDevicePath() const;
    void setDevicePath(const QString &value);

    bool getAutoInstall() const;
    void setAutoInstall(bool value);



    qint64 getBuffers() const;
    void setBuffers(const qint64 &value);

    qint64 getCached() const;
    void setCached(const qint64 &value);

    qint64 getMemAvailable() const;
    void setMemAvailable(const qint64 &value);

    qint64 getMemFree() const;
    void setMemFree(const qint64 &value);

    qint64 getMemTotal() const;
    void setMemTotal(const qint64 &value);

    qint64 getSwapFree() const;
    void setSwapFree(const qint64 &value);

    qint64 getSwapTotal() const;
    void setSwapTotal(const qint64 &value);

private:
    int  state;
    bool loadPackagesDefault;

    bool efi;

    // boot value
    bool bootValid;
    QString boot;
    QString cdrom;
    QString liveFileSystem;
    QString distribution;
    QString live;
    QString lupinRoot;

    QString  partedFile;
    QString  sysInfoFile;
    QString  devicePath;
    bool     autoInstall;

    // memeinfo
    qint64 buffers;
    qint64 cached;
    qint64 memAvailable;
    qint64 memFree;
    qint64 memTotal;
    qint64 swapFree;
    qint64 swapTotal;
};

#endif // SERVERSTATE_H
