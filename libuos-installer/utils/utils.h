#ifndef UTILS_H
#define UTILS_H

#include <QObject>


namespace Tools {

static const QString main_sh = "/usr/share/uos-installer/hooks/main.sh";

static const QString parted_parameter_path = "/uos-installer/parted.json";
static const QString sys_info_path = "/uos-installer/installer-settings.json";
static const QString component_path = "/uos-installer/package.list";
//static const QString packages_default = "/usr/share/uos-installer/packages_default.json";
static const QString packages_default = "/home/deepin/uos-installer/packages_default.json";


enum Installation{WTI_Default = 0, WTI_Local, WTI_SerialPort, WTI_Socket, WTI_PXE, WTI_AutoInstall};

QString scanValidFileName(const QString& path, const QString& basename);

Installation installation();

//!
//! \brief getCurrentPlatform
//! \return x86/sw/loongson/loongarch64/arm
//!
QString getCurrentPlatform();
bool is_sw();
bool is_loongson();
bool is_loongarch64();

}

#endif // UTILS_H
