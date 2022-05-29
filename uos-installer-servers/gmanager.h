#ifndef GMANAGER_H
#define GMANAGER_H

#include <QObject>
#include <QMap>

class QThread;
class GProtoManager;
class GManager : public QObject
{
    Q_OBJECT

    struct JobItem {
        QThread *thread;
        QObject *worker;
    };
public:
    explicit GManager(QObject *parent = nullptr);
    ~GManager();


    void init();
signals:
    void sigStartCommunication();
    void sendData(const QByteArray&);
public slots:
    void onExitServer();
private:
    void initCommunication();
    void initInstaller();

    void appendJob(const QString& key, QObject *object);

private:
    bool initBoot();
    bool checkEfi();
    bool readMemInfo();
    bool readExitUser();
    bool readPwConf();
private:

    QMap<QString, JobItem> m_jobMap;
};

#endif // GMANAGER_H
