#ifndef GNOTIFYINFO_H
#define GNOTIFYINFO_H

#include "gjson.h"
#include "gjsonitem.h"

class GNotifyItem : public GJsonItem
{
public:
    GNotifyItem(const QString& cmd);
    void setState(bool isSuccess);
    void setDescribe(const QString& desc);
};

class GNotifyInfo : public GJson
{
public:
    GNotifyInfo();
    GNotifyInfo(const QJsonObject& info);
    QJsonObject object() const;

    bool commitData();
    void appendItem(const QString& key, QJsonValue item);
    void appendItem(const QString& key, GJsonItem* item);
    void setResult(GJsonItem* item);


    static GNotifyInfo reponse(const QByteArray cmd, bool success, const QByteArray& desc);

    static GNotifyInfo fromeByteArray(const QByteArray& data);
    static QJsonObject byteArray(const QByteArray& data);
private:
    QJsonObject m_info;
};




#endif // GNOTIFYINFO_H
