#include "parameter.h"

#include <QCoreApplication>
#include <QDebug>

Parameter::Parameter(QObject *parent) : QObject(parent),
    m_partedOption(QStringList()<< "p" <<"parted" , tr("desc-parted") , tr("eg")),
    m_sysInfoOption(QStringList()<< "s" <<"system-info" , tr("desc-system-info") , tr("eg")),
    m_deviceOption(QStringList()<< "d" <<"device" , tr("desc-device") , tr("eg")),
    m_autoOption(QStringList()<< "auto" <<"auto-install" , tr("desc-auto") , tr("eg"))
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

//    qInfo() << ;
    m_parser.showHelp(0);
}

