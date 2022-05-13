#ifndef GPARTEDINFO_H
#define GPARTEDINFO_H

/*
 * eg:
[
    {
        "filesystem": "ext4",
        "label": "rootb",
        "mountPoint": "/",
        "usage": "800"
    },
    {
        "filesystem": "ext4",
        "label": "roota",
        "mountPoint": "/",
        "usage": "800"
    }
]
*
*/

#include "gjson.h"

#include <QJsonArray>

class GJsonItem;
class GPartedInfo : public GJson
{
public:
    explicit GPartedInfo(const QString& filename = QString());
    ~GPartedInfo();

    bool commitData();
    void appendItem(GJsonItem* item);

private:
    QJsonArray m_info;
};

#endif // GPARTEDINFO_H
