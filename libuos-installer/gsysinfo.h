#ifndef GSYSINFO_H
#define GSYSINFO_H

#include "gjson.h"

class GJsonItem;
class GSysInfo : public GJson
{
public:
    explicit GSysInfo(const QString& filename = QString());
    ~GSysInfo();

    bool commitData();
    void appendItem(const QString& key, GJsonItem* item);

private:
    QJsonObject m_info;
};

#endif // GSYSINFO_H
