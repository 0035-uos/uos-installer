#ifndef GPROTOMANAGER_H
#define GPROTOMANAGER_H

#include "utils/singleton.h"
#include "gparteditem.h"

#include <QObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QMap>

class PartedItem;
class GProtoManager : public QObject, public Singleton<GProtoManager>
{
    Q_OBJECT
public:
    explicit GProtoManager(QObject *parent = nullptr);

//    void appendPartedItem(GPartedItem* item);
//    void removeAllPartedItem();

public slots:
//    bool savePartedInfoToFile(const QString& filename);
    void appendSocketData(const QByteArray& data);
signals:
    void newFrame(const QByteArray& type, const QByteArray& frame);

private:
    void parseDataFrame();

private:
    QJsonArray m_partedItemArray;
    QByteArray m_bufferArray;
};




#endif // GPROTOMANAGER_H
