#include "gjson.h"


GJson::GJson(const QString &filename)
{
    if (!filename.isEmpty())
        loadfile(filename);
}

GJson::~GJson()
{
}

QByteArray GJson::data() const
{
    return m_doc.toJson(QJsonDocument::Compact);
}


bool GJson::loadfile(const QString &filename)
{
    QFile file(filename);
    if (file.open(QFile::ReadOnly)) {
        m_doc = QJsonDocument::fromJson(file.readAll());
        file.close();
        //check undo
        return true;
    }
    return false;
}

bool GJson::exportfile(const QString &filename) const
{
    QFile file(filename);
    if (file.open(QFile::WriteOnly)) {
        file.write(m_doc.toJson(QJsonDocument::Indented));
        file.close();
        return true;
    }
    return false;
}

bool GJson::commitData()
{
    return true;
}

bool GJson::commitData(const QJsonArray &array)
{
    m_doc = QJsonDocument(array);
    return true;
}

bool GJson::commitData(const QJsonObject &object)
{
    m_doc = QJsonDocument(object);
    return true;
}
