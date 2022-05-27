#ifndef USERINPUT_H
#define USERINPUT_H

#include <QObject>

class UserInput : public QObject
{
    Q_OBJECT
public:
    explicit UserInput(QObject *parent = nullptr);



    static bool UserSelect(const QStringList& target, const QString &tipmsg, int& outIndex, QString& outResult, bool mustSuccess = true, const QStringList& desc = QStringList());
};

#endif // USERINPUT_H
