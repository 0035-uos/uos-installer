#include "propertyreflection.h"

#include <QMetaProperty>

PropertyReflection::PropertyReflection(QObject *parent) : QObject(parent)
{

}

QJsonObject PropertyReflection::properyToJson() const
{
    QJsonObject object;
    int count = this->metaObject()->propertyCount();
    for (int i = 0;i < count; i++) {
        auto property = metaObject()->property(i);
        object.insert(property.name(), QJsonValue::fromVariant(property.read(this)));
    }
    return object;
}
