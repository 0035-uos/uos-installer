#include "parameter.h"
#include "protocol/serverstate.h"

#include <QCoreApplication>
#include <QDebug>

Parameter::Parameter(QObject *parent) : QObject(parent),
    m_partedOption(QStringList()<< "p" <<"parted" , tr("desc-parted") , tr("eg")),
    m_sysInfoOption(QStringList()<< "s" <<"system-info" , tr("desc-system-info") , tr("eg")),
    m_deviceOption(QStringList()<< "d" <<"device" , tr("desc-device") , tr("eg")),
    m_componentOption(QStringList()<< "c" <<"component" , tr("desc-component") , tr("eg")),
    m_autoOption(QStringList()<< "auto" <<"auto-install" , tr("desc-auto") , tr("eg")),
    autoInstall(false)
{
    m_parser.setApplicationDescription(tr("main", "Qt"));

    m_parser.addHelpOption();
    m_parser.addVersionOption();
    m_parser.setSingleDashWordOptionMode(QCommandLineParser::ParseAsLongOptions);

    m_parser.addOption(m_partedOption);
    m_parser.addOption(m_sysInfoOption);
    m_parser.addOption(m_deviceOption);
}

void Parameter::parser()
{
    m_parser.process(*qApp);

    if (m_parser.isSet(m_deviceOption)) {
        devicePath = m_parser.value(m_deviceOption);
        // check undo
    }
    if (m_parser.isSet(m_partedOption)) {
        partedFile = m_parser.value(m_partedOption);
        // check undo
    }
    if (m_parser.isSet(m_sysInfoOption)) {
        sysInfoFile = m_parser.value(m_sysInfoOption);
        // check undo
    }
    if (m_parser.isSet(m_autoOption)) {
        autoInstall = true;
        // check undo
    }
}

QString Parameter::getPartedFile() const
{
    return partedFile;
}

QString Parameter::getSysInfoFile() const
{
    return sysInfoFile;
}

QString Parameter::getDevicePath() const
{
    return devicePath;
}

bool Parameter::getAutoInstall() const
{
    return autoInstall;
}

QString Parameter::getComponentName() const
{
    return componentName;
}

void Parameter::setPartedFile(const QString &value)
{
    partedFile = value;
}

void Parameter::setSysInfoFile(const QString &value)
{
    sysInfoFile = value;
}

void Parameter::setDevicePath(const QString &value)
{
    devicePath = value;
}

void Parameter::setComponentName(const QString &value)
{
    componentName = value;
}

