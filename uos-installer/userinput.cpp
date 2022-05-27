#include "userinput.h"

#include <iostream>

UserInput::UserInput(QObject *parent) : QObject(parent)
{

}

bool UserInput::UserSelect(const QStringList &target, const QString& tipmsg, int &outIndex, QString &outResult, bool mustSuccess, const QStringList &desc)
{
    if (target.length() <= 0) return false;
    QString default_result, result;
USER_RE_INPUT:
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
        result = default_result;
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
            goto USER_RE_INPUT;
        } else {
            return false;
        }
    }
    return true;
}
