#include "gxkblayout.h"

#include <QDebug>

GXkbLayout::GXkbLayout(const QJsonObject &object) :
    GObjectJson(QJsonDocument::fromJson(object.value("xkblayout").toString().toLocal8Bit()).object())
{
}

GXkbLayout::GXkbLayout() :
    GObjectJson()
{

}

void GXkbLayout::appendArray(const QString &key, const GArrayJson &array)
{
    m_info.insert(key, array.array());
}

bool GXkbLayout::valueArray(const QString &key, GArrayJson &array) const
{
    if (m_info.contains(key)) {
        array =  GArrayJson(m_info.value(key).toArray());
        return true;
    }
    return false;
}
