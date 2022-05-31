#ifndef GPARTED_H
#define GPARTED_H

#include "utils/singleton.h"

#include <QObject>

class GParted : public QObject, public Singleton<GParted>
{
    Q_OBJECT
public:
    explicit GParted(QObject *parent = nullptr);

signals:

public slots:
};

#endif // GPARTED_H
