#include "userinput.h"

#include <iostream>

UserInput::UserInput(QObject *parent) : QObject(parent)
{

}

bool UserInput::UserSelect(int &outIndex, QString &outResult, const QStringList &target, const QString &tipmsg, bool mustSuccess, const QStringList &desc)
{
    if (target.length() <= 0) return false;
    QString default_result, result;
    bool exit = false;
    fflush(stdout);
    do {
        exit = false;
        for (int i = 0; i < target.length(); i++) {
            std::cout << std::to_string(i+1) << " " << target.at(i).toStdString();
            if (i < desc.length()) {
                std::cout << "\t" << desc.at(i).toStdString();
            }
            if (i == 0) {
                std::cout << "\t[default]";
                default_result = target.at(i);
            }
            std::cout << std::endl;
        }
        std::cout << tipmsg.toStdString() << std::endl;
        std::cout << tr("@: ").toStdString();
        std::string c;
        std::cin >> c;
        result = QString::fromStdString(c).trimmed();

        if (result.isEmpty()) {
            outResult = default_result;
            outIndex = 0;
        } else {
            bool ok = false;
            outIndex = result.toInt(&ok);
            if (ok && outIndex <= target.length() && outIndex > 0) {
                outIndex -= 1;
                outResult = target.at(outIndex);
            } else if (target.contains(result)) {
                outResult = result;
                outIndex = target.indexOf(result);
            } else if (mustSuccess) {
                exit = true;
                fflush(stdout);
                std::cout << tr("Please enter a valid option").toStdString() << std::endl;
            } else {
                return false;
            }
        }
    } while(exit);
    return true;
}

bool UserInput::ReadInput(QString &outResult, std::function<bool (const QString &)> func, const QString &tipmsg)
{
    QString result;
    fflush(stdout);
    bool exit = false;
    do {
        exit = false;
        std::cout << tipmsg.toStdString() << std::endl;
        std::cout << tr("@: ").toStdString();
        std::string c;
        std::cin >> c;
        outResult = QString::fromStdString(c).trimmed();

        if (func) {
            if (func(outResult)) {
            } else {
                exit = true;
                fflush(stdout);
            }
        }
    } while(exit);
    return true;
}
