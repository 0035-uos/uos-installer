#ifndef PARAMETER_H
#define PARAMETER_H

#include "utils/singleton.h"

#include <QObject>
#include <QCommandLineParser>
#include <QCommandLineOption>

class Parameter : public QObject, public Singleton<Parameter>
{
    Q_OBJECT
public:
    explicit Parameter(QObject *parent = nullptr);

    void parser();
    QString getPartedFile() const;

    QString getSysInfoFile() const;

    QString getDevicePath() const;

    bool getAutoInstall() const;

    QString getComponentName() const;

    void setPartedFile(const QString &value);

    void setSysInfoFile(const QString &value);

    void setDevicePath(const QString &value);

    void setComponentName(const QString &value);

signals:

public slots:

private:

private:
    QCommandLineParser m_parser;

    QCommandLineOption m_partedOption;
    QCommandLineOption m_sysInfoOption;
    QCommandLineOption m_deviceOption;
    QCommandLineOption m_componentOption;
    QCommandLineOption m_autoOption;

private:
    QString  partedFile;
    QString  sysInfoFile;
    QString  devicePath;
    bool     autoInstall;
    QString  componentName;
};

#endif // PARAMETER_H
