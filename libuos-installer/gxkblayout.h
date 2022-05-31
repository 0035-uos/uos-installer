#ifndef GXKBLAYOUT_H
#define GXKBLAYOUT_H

#include "gobjectjson.h"
#include "garrayjson.h"

class GXkbLayout : public GObjectJson
{
public:
    explicit GXkbLayout(const QJsonObject& object);
    explicit GXkbLayout();

    void appendArray(const QString& key, const GArrayJson& array);
    bool valueArray(const QString& key, GArrayJson& array) const;
};

#endif // GXKBLAYOUT_H

