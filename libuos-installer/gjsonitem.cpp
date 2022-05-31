#include "gjsonitem.h"

GJsonItem::GJsonItem()
{

}

GJsonItem::GJsonItem(const QJsonObject &object):
    attributes(object)
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

QString GJsonItem::value(const QString &key)
{
    return attributes.value(key).toString();
}

bool GJsonItem::contains(const QString &key)
{
    return attributes.contains(key);
}
