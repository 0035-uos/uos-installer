#ifndef USERINPUT_H
#define USERINPUT_H

#include <QObject>

#include <functional>

class UserInput : public QObject
{
    Q_OBJECT
public:
    explicit UserInput(QObject *parent = nullptr);



    static bool UserSelect(int& outIndex, QString& outResult, const QStringList& target, const QString &tipmsg, bool mustSuccess = true, const QStringList& desc = QStringList());
    static bool ReadInput(QString& outResult, std::function<bool(const QString&)> func, const QString &tipmsg);
};

#endif // USERINPUT_H
