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

    Q_PROPERTY(QString ignoreUsername READ getIgnoreUsername WRITE setIgnoreUsername)

    Q_PROPERTY(bool ddePwCheckFileExists READ getDdePwCheckFileExists WRITE setDdePwCheckFileExists)
    Q_PROPERTY(bool pwEnabled READ getPwEnabled WRITE setPwEnabled)
    Q_PROPERTY(int pwMaxLength READ getPwMaxLength WRITE setPwMaxLength)
    Q_PROPERTY(int pwMinLength READ getPwMinLength WRITE setPwMinLength)
    Q_PROPERTY(QString pwCharacterType READ getPwCharacterType WRITE setPwCharacterType)
    Q_PROPERTY(int pwCharacterNumRequired READ getPwCharacterNumRequired WRITE setPwCharacterNumRequired)
    Q_PROPERTY(int pwPalindromeMinNum READ getPwPalindromeMinNum WRITE setPwPalindromeMinNum)
    Q_PROPERTY(QString pwDictPath READ getPwDictPath WRITE setPwDictPath)
    Q_PROPERTY(int pwCheckWord READ getPwCheckWord WRITE setPwCheckWord)
    Q_PROPERTY(bool pwFirstLetterUppercase READ getPwFirstLetterUppercase WRITE setPwFirstLetterUppercase)
    Q_PROPERTY(int pwMonotoneCharacterNum READ getPwMonotoneCharacterNum WRITE setPwMonotoneCharacterNum)
    Q_PROPERTY(int pwConsecutiveSameCharacterNum READ getPwConsecutiveSameCharacterNum WRITE setPwConsecutiveSameCharacterNum)
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

    QString getIgnoreUsername() const;
    void setIgnoreUsername(const QString &value);

    bool getDdePwCheckFileExists() const;
    void setDdePwCheckFileExists(bool value);

    bool getPwEnabled() const;
    void setPwEnabled(bool value);

    int getPwMaxLength() const;
    void setPwMaxLength(int value);

    int getPwMinLength() const;
    void setPwMinLength(int value);

    QString getPwCharacterType() const;
    void setPwCharacterType(const QString &value);

    int getPwCharacterNumRequired() const;
    void setPwCharacterNumRequired(int value);

    int getPwPalindromeMinNum() const;
    void setPwPalindromeMinNum(int value);

    QString getPwDictPath() const;
    void setPwDictPath(QString value);

    int getPwCheckWord() const;
    void setPwCheckWord(int value);

    bool getPwFirstLetterUppercase() const;
    void setPwFirstLetterUppercase(bool value);

    int getPwMonotoneCharacterNum() const;
    void setPwMonotoneCharacterNum(int value);

    int getPwConsecutiveSameCharacterNum() const;
    void setPwConsecutiveSameCharacterNum(int value);

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

    QString ignoreUsername;

    // password
    bool ddePwCheckFileExists;
    bool pwEnabled; //
    int pwMaxLength;
    int pwMinLength;
    QString pwCharacterType;  // 可选字符列表
    int pwCharacterNumRequired; // 最少字符个数
    int pwPalindromeMinNum; // 回文最小检测数
    QString pwDictPath; //
    int pwCheckWord; // 不太清楚这个配置： 感觉像是一些特殊单词的使用限制（配置为空）配合dictpath使用的
    bool pwFirstLetterUppercase; // 首字母是否大写
    int pwMonotoneCharacterNum;         // 单调字符个数
    int pwConsecutiveSameCharacterNum; // 连续相似字符个数
};

#endif // SERVERSTATE_H
