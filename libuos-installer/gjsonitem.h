#ifndef GJSONITEM_H
#define GJSONITEM_H


#include <QJsonObject>

class GJsonItem
{
public:
    explicit GJsonItem();
    explicit GJsonItem(const QJsonObject& object);
    virtual ~GJsonItem();

    virtual QJsonObject tojson() const;

    virtual void appendValue(const QString& key, const QString& value);
    virtual void removeValue(const QString& key);
    virtual QString value(const QString& key);
    virtual bool contains(const QString& key);

protected:
    QJsonObject attributes;
};

#endif // GJSONITEM_H
