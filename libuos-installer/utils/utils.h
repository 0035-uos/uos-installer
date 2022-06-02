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

#ifdef QT_DEBUG
static const QString installer_server_log_file = QString("/tmp/%1").arg("uos-installer-server.log");
static const QString installer_log_file = QString("/tmp/%1").arg("uos-installer.log");
#else
static const QString installer_server_log_file = QString("/var/log/%1").arg("uos-installer-server.log");
static const QString installer_log_file = QString("/var/log/%1").arg("uos-installer.log");
#endif

static const QString password_conf_file = "/etc/deepin/dde.conf";

static const qint64 TByte = 1024*1024*1024*1024L;
static const qint64 GByte = 1024*1024*1024L;
static const qint64 MByte = 1024*1024L;
static const qint64 KByte = 1024L;

enum Installation{WTI_Default = 0, WTI_Local, WTI_SerialPort, WTI_Socket, WTI_PXE, WTI_AutoInstall};

QString scanValidFileName(const QString& path, const QString& basename);

Installation installation();

bool isLive();
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
bool WriteFile(const QString& path, const QByteArray& data);



/// ==========================================================================================
struct XkbModel {
  QString name = "";
  QString description = "";
  QString vendor = "";
};
typedef QList<XkbModel> XkbModelList;

struct XkbLayoutVariant {
  QString name = "";
  QString layout_name = "";
  QString description = "";
  QString short_description = "";
  QStringList language_list;
};
typedef QList<XkbLayoutVariant> XKbLayoutVariantList;

struct XkbLayout {
  QString name = "";
  QString description = "";
  QString short_description = "";
  QStringList language_list;
  XKbLayoutVariantList variant_list;
};
typedef QList<XkbLayout> XkbLayoutList;

struct XkbConfig {
  XkbModelList model_list;
  XkbLayoutList layout_list;
};

// Read system keyboard layout, with localized description.
// |locale| is the desired locale name.
XkbConfig GetXkbConfig();


/// ==========================================================================================
const QString languages_path("/usr/share/uos-installer/languages.json");

/// ==========================================================================================
struct ZoneInfo {
 public:
  QString country;
  QString timezone;

  // Coordinates of zone.
  double latitude;
  double longitude;

  // Distance to clicked point for comparison.
  double distance;
};
typedef QList<ZoneInfo> ZoneInfoList;

double ConvertPos(const QString& pos, int digits);

ZoneInfoList GetZoneInfoList();


}

#endif // UTILS_H
