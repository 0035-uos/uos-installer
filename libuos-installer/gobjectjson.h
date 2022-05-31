#ifndef GOBJECTJSON_H
#define GOBJECTJSON_H

#include "gjson.h"
#include "gjsonitem.h"


class GObjectJson : public GJson
{
public:
    explicit GObjectJson(const QString& filename = QString());
    explicit GObjectJson(const QJsonObject &object);
    explicit GObjectJson(const GObjectJson &other);

    bool commitData();
    virtual void appendItem(const QString& key, GJsonItem* item);
    virtual GJsonItem value(const QString& key) const;

protected:
    QJsonObject m_info;
};

#endif // GOBJECTJSON_H
