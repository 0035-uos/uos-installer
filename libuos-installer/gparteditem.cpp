#include "gparteditem.h"

GPartedItem::GPartedItem() : GJsonItem()
{

}

GPartedItem::GPartedItem(const QString &fs, const QString &label, const QString &mountpoint, const QString &usage):
    GJsonItem ()
{
    attributes.insert("filesystem", fs);
    attributes.insert("label", label);
    attributes.insert("mountPoint", mountpoint);
    attributes.insert("usage", usage);
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
    attributes.insert("mountPoint", mountpoint);
}

void GPartedItem::setUsage(const QString &usage)
{
    attributes.insert("usage", usage);
}
