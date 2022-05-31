#include "partitioninfo.h"

PartitionInfo::PartitionInfo(QObject *parent) : PropertyReflection(parent)
{

}

PartitionInfo::PartitionType PartitionInfo::getType() const
{
    return type;
}

void PartitionInfo::setType(const PartitionInfo::PartitionType &value)
{
    type = value;
}

QList<QVariant> PartitionInfo::getFlags() const
{
    QList<QVariant> list;
    for (int i = 0;i < flags.length(); i++) {
        list.append(QVariant::fromValue(flags.at(i)));
    }
    return list;
}

void PartitionInfo::setFlags(const QList<QVariant> &value)
{
    flags.clear();
    for (int i = 0;i < value.length(); i++) {
        flags.append(value.at(i).value<PartitionFlag>());
    }
}

void PartitionInfo::appendFlag(PartitionInfo::PartitionFlag flag)
{
    flags.append(flag);
}

QString PartitionInfo::getFsType() const
{
    return fsType;
}

void PartitionInfo::setFsType(const QString &value)
{
    fsType = value;
}

qint64 PartitionInfo::getStartSector() const
{
    return startSector;
}

void PartitionInfo::setStartSector(const qint64 &value)
{
    startSector = value;
}

qint64 PartitionInfo::getEndSector() const
{
    return endSector;
}

void PartitionInfo::setEndSector(const qint64 &value)
{
    endSector = value;
}

qint64 PartitionInfo::getNumSector() const
{
    return numSector;
}

void PartitionInfo::setNumSector(const qint64 &value)
{
    numSector = value;
}
