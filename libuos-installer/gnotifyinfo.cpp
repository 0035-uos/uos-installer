#include "gnotifyinfo.h"

GNotifyItem::GNotifyItem(const QString &cmd)
{
    attributes.insert("command", cmd);
}

void GNotifyItem::setState(bool isSuccess)
{
    attributes.insert("success", isSuccess);
}

void GNotifyItem::setDescribe(const QString &desc)
{
    attributes.insert("describe", desc);
}



GNotifyInfo::GNotifyInfo() :
    GJson ()
{

}

GNotifyInfo::GNotifyInfo(const QJsonObject &info) :
    GJson (), m_info(info)
{

}

QJsonObject GNotifyInfo::object() const
{
    return m_info;
}

bool GNotifyInfo::commitData()
{
    return GJson::commitData(m_info);
}

void GNotifyInfo::appendItem(const QString &key, QJsonValue item)
{
    m_info.insert(key, item);
}

void GNotifyInfo::appendItem(const QString &key, GJsonItem *item)
{
    m_info.insert(key, item->tojson());
}

void GNotifyInfo::setResult(GJsonItem *item)
{
    m_info.insert("result", item->tojson());
}

GNotifyInfo GNotifyInfo::reponse(const QByteArray cmd, bool success, const QByteArray &desc)
{
    GNotifyInfo info;

    GNotifyItem resultItem(cmd);
    resultItem.setState(success);
    resultItem.setDescribe(desc);
    info.setResult(&resultItem);
    info.commitData();
    return info;
}

GNotifyInfo GNotifyInfo::fromeByteArray(const QByteArray &data)
{
    return GNotifyInfo(QJsonDocument::fromJson(data).object());
}

