#include "gprotomanager.h"
#include "utils/commands.h"

#include "protocol/gprotocol.h"

#include <QFile>
#include <QPair>

#include <QDebug>


GProtoManager::GProtoManager(QObject *parent) : QObject(parent)
{

}

//void GProtoManager::appendPartedItem(GPartedItem *item)
//{
//    m_partedItemArray.append(item->tojson());
//}

//void GProtoManager::removeAllPartedItem()
//{
//    while (!(m_partedItemArray.isEmpty())) {
//        m_partedItemArray.removeFirst();
//    }
//}

//bool GProtoManager::savePartedInfoToFile(const QString &filename)
//{
//    QJsonDocument doc(m_partedItemArray);
//    QFile file(filename);
//    if (file.open(QFile::ReadWrite)) {
//        file.write(doc.toJson());
//        file.close();
//        return true;
//    }
//    return false;
//}

void GProtoManager::appendSocketData(const QByteArray &data)
{
    m_bufferArray.append(data);
    parseDataFrame();
}

void GProtoManager::parseDataFrame()
{
    int ret;
    QByteArray frame;
    QByteArray type, content;


    while (m_bufferArray.length() > min_len) {
        ret = GProtocol::getDataFromFrame(proto_begin, proto_end, m_bufferArray, frame);
        switch (ret) {
        case 0:
            break;
        default:
            qInfo() << ret << frame;
            continue;
        }
        ret = GProtocol::getDataFromFrame(type_begin, type_end, frame, type);

        ret = GProtocol::getDataFromFrame(content_begin, content_end, frame, content);

        newFrame(type, content);
    }
}




