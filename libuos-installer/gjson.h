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
    virtual ~GJson();

    virtual QByteArray data() const;
    virtual bool loadfile(const QString& filename);
    virtual bool exportfile(const QString& filename) const;
    virtual bool commitData();

protected:
    bool commitData(const QJsonArray& array);
    bool commitData(const QJsonObject& object);
protected:
    QJsonDocument m_doc;

};


#endif // GJSON_H
