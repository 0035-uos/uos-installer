#ifndef UTILS_H
#define UTILS_H

#include <QObject>


namespace Tools {

static const QString main_sh = "/usr/share/uos-installer/hooks/main.sh";

static const QString parted_parameter_path = "/uos-installer/parted.json";
static const QString sys_info_path = "/uos-installer/installer_settings.json";
static const QString component_path = "/uos-installer/package.list";
static const QString packages_default = "/usr/share/uos-installer/packages_default.json";
//static const QString packages_default = "/home/deepin/uos-installer/packages_default.json";

static const QString ignore_username = "/usr/share/uos-installer/username.ignore";

static const QString password_conf_file = "/etc/deepin/dde.conf";

static const qint64 TByte = 1024*1024*1024*1024L;
static const qint64 GByte = 1024*1024*1024L;
static const qint64 MByte = 1024*1024L;
static const qint64 KByte = 1024L;

enum Installation{WTI_Default = 0, WTI_Local, WTI_SerialPort, WTI_Socket, WTI_PXE, WTI_AutoInstall};

QString scanValidFileName(const QString& path, const QString& basename);

Installation installation();

//!
//! \brief getCurrentPlatform
//! \return x86/sw/loongson/loongarch64/arm
//!
QString getCurrentPlatform();
bool is_x86();
bool is_sw();
bool is_loongson();
bool is_loongarch64();


QString ReadFile(const QString& path);


}

#endif // UTILS_H
