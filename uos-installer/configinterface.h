#ifndef CONFIGINTERFACE_H
#define CONFIGINTERFACE_H

#include <QObject>

class GJson;
class ConfigInterface : public QObject
{
    Q_OBJECT
public:
    explicit ConfigInterface(QObject *parent = nullptr);

    virtual void initData();
    virtual void run();
    virtual void cleanData();
    virtual GJson* data() = 0;
signals:

public slots:

protected:
};

#endif // CONFIGINTERFACE_H
