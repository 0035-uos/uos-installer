#include "gobjectjson.h"


GObjectJson::GObjectJson(const QString &filename) : GJson(filename)
{
    if (m_doc.isObject())
        m_info = object();
}

GObjectJson::GObjectJson(const QJsonObject &object): GJson (),
    m_info(object)
{
    GJson::commitData(m_info);
}

GObjectJson::GObjectJson(const GObjectJson &other) : GJson (),
    m_info(other.m_info)
{

}

bool GObjectJson::commitData()
{
    return GJson::commitData(m_info);
}

void GObjectJson::appendItem(const QString &key, GJsonItem *item)
{
    m_info.insert(key, item->tojson());
}

GJsonItem GObjectJson::value(const QString &key) const
{
    if (m_info.contains(key)) {
        return GJsonItem(m_info.value(key).toObject());
    }
    return GJsonItem();
}
