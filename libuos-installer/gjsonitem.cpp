#include "gjsonitem.h"

GJsonItem::GJsonItem()
{

}

GJsonItem::~GJsonItem()
{

}

QJsonObject GJsonItem::tojson() const
{
    return  attributes;
}

void GJsonItem::appendValue(const QString &key, const QString &value)
{
    attributes.insert(key, value);
}

void GJsonItem::removeValue(const QString &key)
{
    attributes.remove(key);
}
