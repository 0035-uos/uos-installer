#ifndef GSYSINFO_H
#define GSYSINFO_H

#include "gobjectjson.h"

class GSysInfo : public GObjectJson
{
public:
    explicit GSysInfo(const QString& filename = QString());
    ~GSysInfo();
};

#endif // GSYSINFO_H
