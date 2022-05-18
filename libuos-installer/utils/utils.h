#ifndef UTILS_H
#define UTILS_H

#include <QObject>


namespace Tools {

static const QString parted_parameter_path = "/installer/parted.json";
static const QString parted_sys_info_path = "/installer/installer-settings.json";


enum Installation{WTI_Default = 0, WTI_Local, WTI_SerialPort, WTI_Socket, WTI_PXE, WTI_AutoInstall};

QString scanValidFileName(const QString& path, const QString& basename);

Installation installation();



}


#endif // UTILS_H
