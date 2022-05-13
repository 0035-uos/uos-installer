#ifndef GPARTEDITEM_H
#define GPARTEDITEM_H

#include "gjsonitem.h"

class GPartedItem : public GJsonItem
{
public:
    explicit GPartedItem();

public:
    void setFilesystem(const QString& fs);
    void setlabel(const QString& label);
    void setMountPoint(const QString& mountpoint);
    void setUsage(const QString& usage);

};

#endif // GPARTEDITEM_H
