#include "gcomponentmanager.h"

#include <QVariant>

GComponentManager::GComponentManager(QObject *parent) : QObject(parent),
  GJson()
{

}

bool GComponentManager::state() const
{
    return (!(m_doc.isEmpty()) && m_doc.isObject());
}

QStringList GComponentManager::componentList() const
{
    return m_doc.object().keys();
}

QStringList GComponentManager::packagesList(const QString &component, const QString &type) const
{
    QStringList list;
    if (m_doc.object().contains(component)) {
        QJsonObject object = m_doc.object().value(component).toObject();
        if (object.contains(type)) {
            QVariantList array = object.value("defalut").toArray().toVariantList();
            for (const QVariant& it : array) {
                list << it.toString();
            }
        }
    }
    return list;
}
