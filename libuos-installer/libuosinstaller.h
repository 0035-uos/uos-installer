#ifndef LIBUOSINSTALLER_H
#define LIBUOSINSTALLER_H

#include <QStringList>
#include <QObject>

class LocalSocket;
class Libuosinstaller : public QObject
{
    Q_OBJECT
public:
    explicit Libuosinstaller(QObject* parent = nullptr);

    bool initConnect(const QStringList& parameter);
    void closeConnect();
    bool writeFile(const QString& filename);

private:
    LocalSocket* m_socket;
};

#endif // LIBUOSINSTALLER_H
