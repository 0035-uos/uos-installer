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
signals:

public slots:

private:

private:
    QCommandLineParser m_parser;

    QCommandLineOption m_partedOption;
    QCommandLineOption m_sysInfoOption;
    QCommandLineOption m_deviceOption;
    QCommandLineOption m_autoOption;
};

#endif // PARAMETER_H
