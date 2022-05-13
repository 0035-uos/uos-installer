#ifndef PARAMETER_H
#define PARAMETER_H

#include <QObject>

class Parameter : public QObject
{
    Q_OBJECT
public:
    explicit Parameter(QObject *parent = nullptr);

signals:

public slots:
};

#endif // PARAMETER_H