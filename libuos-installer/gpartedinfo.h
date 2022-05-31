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

#include "garrayjson.h"

class GPartedInfo : public GArrayJson
{
public:
    explicit GPartedInfo(const QString& filename = QString());
    ~GPartedInfo();

};

#endif // GPARTEDINFO_H
