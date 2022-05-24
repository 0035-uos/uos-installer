#ifndef SERVERSTATE_H
#define SERVERSTATE_H

#include "utils/propertyreflection.h"
#include "utils/singleton.h"

class ServerState : public PropertyReflection, public Singleton<ServerState>
{
    Q_OBJECT
    Q_PROPERTY(int state READ getState WRITE setState)
    Q_PROPERTY(bool loadPackagesDefault READ getLoadPackagesDefault WRITE setLoadPackagesDefault)

    Q_PROPERTY(bool bootValid READ getBootValid WRITE setBootValid)
    Q_PROPERTY(QString boot READ getBoot WRITE setBoot)
    Q_PROPERTY(QString cdrom READ getCdrom WRITE setCdrom)
    Q_PROPERTY(QString liveFileSystem READ getLiveFileSystem WRITE setLiveFileSystem)
    Q_PROPERTY(QString distribution READ getDistribution WRITE setDistribution)
    Q_PROPERTY(QString live READ getLive WRITE setLive)
    Q_PROPERTY(QString lupinRoot READ getLupinRoot WRITE setLupinRoot)

public:
    explicit ServerState(QObject *parent = nullptr);

    int getState() const;
    void setState(int value);

    QString getBoot() const;
    void setBoot(const QString &value);

    bool getLoadPackagesDefault() const;
    void setLoadPackagesDefault(bool value);

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

private:
    int  state;
    bool loadPackagesDefault;

    // boot value
    bool bootValid;
    QString boot;
    QString cdrom;
    QString liveFileSystem;
    QString distribution;
    QString live;
    QString lupinRoot;

};

#endif // SERVERSTATE_H