#include "garrayjson.h"

GArrayJson::GArrayJson(const QString &filename) : GJson(filename)
{
    if (m_doc.isArray())
        m_info = array();
}

GArrayJson::GArrayJson(const QJsonArray &array) : GJson (),
    m_info(array)
{

}

GArrayJson::GArrayJson(const QByteArray &array) : GJson (),
    m_info(QJsonDocument::fromJson(array).array())
{

}

GArrayJson::GArrayJson(const GArrayJson &other) : GJson (),
    m_info(other.m_info)
{

}

void GArrayJson::setAarrayJson(const QJsonArray &array)
{
    m_info = array;
}

bool GArrayJson::commitData()
{
    GJson::commitData(m_info);
    return true;
}

void GArrayJson::appendItem(GJsonItem *item)
{
    m_info.append(item->tojson());
}

int GArrayJson::count() const
{
    return m_info.count();
}

GJsonItem GArrayJson::value(int index) const
{
    if (m_info.count() > index && index >= 0)
        return GJsonItem(m_info.at(index).toObject());
    return GJsonItem();
}
