#ifndef GJSON_H
#define GJSON_H


#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QMap>
#include <QFile>
#include <QFileInfo>


class GJson
{
public:
    explicit GJson(const QString &filename = QString());
    explicit GJson(const QByteArray& data);
    virtual ~GJson();

    virtual QByteArray data() const;
    virtual bool loadfile(const QString& filename);
    virtual bool loaddata(const QByteArray& data);
    virtual bool exportfile(const QString& filename) const;
    virtual bool commitData();

public:
    virtual bool commitData(const QJsonArray& array);
    virtual bool commitData(const QJsonObject& object);

    QJsonArray array() const;
    QJsonObject object() const;
protected:
    QJsonDocument m_doc;

};


#endif // GJSON_H
