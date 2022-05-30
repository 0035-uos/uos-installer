#ifndef GSCRIPTSERVER_H
#define GSCRIPTSERVER_H

#include "utils/singleton.h"

#include <QObject>
#include <QMap>

#include <functional>

class GScriptsRunAbstract;
class GScriptServer : public QObject, public Singleton<GScriptServer>
{
    Q_OBJECT
public:
    explicit GScriptServer(QObject *parent = nullptr);

signals:
    void sigSend(const QByteArray&);
    void sigExitServer();

public slots:
    void start(const QByteArray &cmd, const QByteArray &parameter);
    void finished(const QString& cmd, const QByteArray &data);


private:
    void onGetDevices(const QByteArray& data);
    void onSetDevice(const QByteArray& data);
    void onSetParted(const QByteArray& data);
    void onSetSysInfo(const QByteArray& data);
    void onGetComponent(const QByteArray& data);
    void onSetComponent(const QByteArray& data);
    void onStartInstall(const QByteArray& data);
    void onExit(const QByteArray& data);
private:
    GScriptsRunAbstract* m_script;
    QMap<QByteArray, std::function<void(const QByteArray&)>> m_registerFunction;

};

#endif // GSCRIPTSERVER_H
