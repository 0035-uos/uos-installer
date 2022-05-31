#ifndef GARRAYJSON_H
#define GARRAYJSON_H

#include "gjson.h"
#include "gjsonitem.h"

#include <QJsonArray>


class GArrayJson : public GJson
{
public:
    explicit GArrayJson(const QString& filename = QString());
    explicit GArrayJson(const QJsonArray& array);
    explicit GArrayJson(const QByteArray& array);
    explicit GArrayJson(const GArrayJson& other);

    virtual void setAarrayJson(const QJsonArray& array);

    bool commitData();
    virtual void appendItem(GJsonItem* item);
    virtual int count() const;
    virtual GJsonItem value(int index) const;


protected:
    QJsonArray m_info;
};

#endif // GARRAYJSON_H
