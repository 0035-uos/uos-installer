#include "gparteditem.h"

GPartedItem::GPartedItem() : GJsonItem()
{

}

void GPartedItem::setFilesystem(const QString &fs)
{
    attributes.insert("filesystem", fs);
}

void GPartedItem::setlabel(const QString &label)
{
    attributes.insert("label", label);
}

void GPartedItem::setMountPoint(const QString &mountpoint)
{
    attributes.insert("mountpoint", mountpoint);
}

void GPartedItem::setUsage(const QString &usage)
{
    attributes.insert("usage", usage);
}
