#ifndef PROPERTYREFLECTION_H
#define PROPERTYREFLECTION_H

#include <QObject>
#include <QJsonObject>

class PropertyReflection : public QObject
{
    Q_OBJECT
public:
    explicit PropertyReflection(QObject *parent = nullptr);

    virtual QJsonObject properyToJson() const;
signals:

public slots:
};

#endif // PROPERTYREFLECTION_H
