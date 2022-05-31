#ifndef GTIMEZONE_H
#define GTIMEZONE_H

#include "garrayjson.h"

class GTimezone : public GArrayJson
{
public:
    GTimezone(const QJsonArray& array);
    GTimezone();
};

#endif // GTIMEZONE_H
