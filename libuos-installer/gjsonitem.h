#ifndef GJSONITEM_H
#define GJSONITEM_H


#include <QJsonObject>

class GJsonItem
{
public:
    explicit GJsonItem();
    virtual ~GJsonItem();

    virtual QJsonObject tojson() const;

    virtual void appendValue(const QString& key, const QString& value);
    virtual void removeValue(const QString& key);

protected:
    QJsonObject attributes;
};

#endif // GJSONITEM_H
