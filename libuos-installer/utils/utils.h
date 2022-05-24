#ifndef UTILS_H
#define UTILS_H

#include <QObject>


namespace Tools {

static const QString main_sh = "/usr/share/uos-installer/hooks/main.sh";

static const QString parted_parameter_path = "/uos-installer/parted.json";
static const QString sys_info_path = "/uos-installer/installer-settings.json";
static const QString component_path = "/uos-installer/package.list";
static const QString packages_default = "/usr/share/uos-installer/packages_default.json";


enum Installation{WTI_Default = 0, WTI_Local, WTI_SerialPort, WTI_Socket, WTI_PXE, WTI_AutoInstall};

QString scanValidFileName(const QString& path, const QString& basename);

Installation installation();



}


#endif // UTILS_H
