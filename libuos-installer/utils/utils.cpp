#include "utils.h"

#include <QFile>
#include <QByteArray>
#include <QMap>
#include <QProcess>
#include <QDebug>
#include <QDomDocument>

#include <cmath>
#include <libintl.h>

namespace Tools {



QString scanValidFileName(const QString &path, const QString &basename)
{
    QString fp = path;
    if (!(path.endsWith("/"))) {
        fp.append("/");
    }
    int k = 2;
    QString fn = fp + basename + QString("_1");
    while (QFile::exists(fn)) {
        fn = QString("%1%2_%3").arg(fp).arg(basename).arg(k++);
    }
    return fn;
}

Installation installation()
{
    static const Installation mode = []() {
        Installation mode = WTI_Default;
        QFile file("/proc/cmdline");
        if (file.exists() && file.open(QFile::ReadOnly)) {
            QByteArray cmdline = file.readAll();
            file.close();
            if (cmdline.contains("nfsroot")) {
                mode = WTI_PXE;
            } else if (cmdline.contains("install-mode=local")) {
                mode = WTI_Local;
            } else if (cmdline.contains("install-mode=serialport")) {
                mode = WTI_SerialPort;
            } else if (cmdline.contains("install-mode=socket")) {
                mode = WTI_Socket;
            }
        }
        return mode;
    }();
    return mode;
}

bool isLive()
{
    static const bool live = []() {
        bool live = false;
        QFile file("/proc/cmdline");
        if (file.exists() && file.open(QFile::ReadOnly)) {
            QByteArray cmdline = file.readAll();
            file.close();
            if (cmdline.contains("boot=casper")) {
                return true; // ubuntu
            } else if (cmdline.contains("boot=live")) {
                return true; // uos
            }
        }
        return live;
    }();
    return live;
}


QString getCurrentPlatform()
{
    static const QMap<QString, QString> arch_map{ { "x86_64",  "x86" },
                                           { "i386", "x86" },
                                           { "i686", "x86" },
                                           { "amd64", "x86" },
                                           { "x86", "x86" },
                                           { "sw_64", "sw" },
                                           { "mips64", "loongson" },
                                           { "loongarch64", "loongarch64" },
                                           { "aarch64", "arm" } };
    static const QString platform = []() {
        QString res;
        QProcess p;
        p.start("uname -m");
        p.waitForFinished();
        res = p.readAllStandardOutput().trimmed();
        return res;
    }();
    return arch_map[platform];

}

bool is_x86()
{
    return (getCurrentPlatform() == "x86");
}

bool is_sw()
{
    return (getCurrentPlatform() == "sw");
}

bool is_loongson()
{
    return (getCurrentPlatform() == "loongson");
}

bool is_loongarch64()
{
    return (getCurrentPlatform() == "loongarch64");
}

QString ReadFile(const QString &path)
{
    QFile file(path);
    if (file.exists()) {
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qWarning() << "ReadFile() failed to open" << path;
            return "";
        }
        const QString &str = QString::fromUtf8(file.readAll());
        file.close();
        return str;
    } else {
        qWarning() << "ReadFileContent() file not found: " << path;
        return "";
    }
}

bool WriteFile(const QString &path, const QByteArray &data)
{
    QFile file(path);
    if (file.open(QFile::WriteOnly)) {
        file.write(data);
        file.close();
        return true;
    }
    return false;
}



// Domain name of xkb-data.
const char kXkbDomain[] = "xkeyboard-config";

const char kDefaultLang[] = "en_US.UTF-8";

const char kXkbBaseRule[] = "/usr/share/X11/xkb/rules/base.xml";



// Get localized |description|.
QString GetLocalDesc(const QString& description) {
    QString s_text = QString(dgettext(kXkbDomain, description.toLocal8Bit().constData()));
    return s_text;
}

// Read modelList node.
void ReadModelList(const QDomNode& root, XkbModelList& model_list) {
  const QDomNodeList model_nodes(root.childNodes());
  for (int index = 0; index < model_nodes.length(); index++) {
    XkbModel xkb_model;
    const QDomNodeList config_nodes(model_nodes.at(index).childNodes());
    if (config_nodes.length() == 1) {
      // Read modelList / model / configItem.
      const QDomNodeList props(config_nodes.at(0).childNodes());
      for (int props_idx = 0; props_idx < props.length(); props_idx++) {
        const QDomNode prop(props.at(props_idx));
        if (prop.nodeName() == "name") {
          xkb_model.name = prop.toElement().text();
        } else if (prop.nodeName() == "description") {
          xkb_model.description = GetLocalDesc(prop.toElement().text());
        } else if (prop.nodeName() == "vendor") {
          xkb_model.vendor = prop.toElement().text();
        }
      }
    }
    model_list.append(xkb_model);
  }
}

// Read configItem in layoutVariant node.
void ReadLayoutVariantList(const QDomNode& root,
                           XKbLayoutVariantList& variant_list) {
  const QDomNodeList variant_nodes(root.childNodes());
  for (int variant_idx = 0; variant_idx < variant_nodes.length();
       variant_idx++) {
    const QDomNode variant_node(variant_nodes.at(variant_idx));
    XkbLayoutVariant layout_variant;
    const QDomNode config_node(variant_node.firstChild());
    if (config_node.isNull()) {
      continue;
    }
    const QDomNodeList props(config_node.childNodes());
    for (int prop_idx = 0; prop_idx < props.length(); prop_idx++) {
      const QDomNode prop(props.at(prop_idx));
      if (prop.nodeName() == "name") {
        layout_variant.name = prop.toElement().text();
      } else if (prop.nodeName() == "description") {
        layout_variant.description = GetLocalDesc(prop.toElement().text());
      } else if (prop.nodeName() == "shortDescription") {
        layout_variant.short_description = prop.toElement().text();
      } else if (prop.nodeName() == "languageList") {
        // Read layout / configItem / languageList
        const QDomNodeList lang_nodes(prop.childNodes());
        for (int lang_idx = 0; lang_idx < lang_nodes.length(); lang_idx++) {
          const QDomNode lang_node(lang_nodes.at(lang_idx));
          layout_variant.language_list.append(lang_node.toElement().text());
        }
      }
    }
    variant_list.append(layout_variant);
  }
}

// Read configItem in layout node.
void ReadLayoutConfigItem(const QDomNode& root, XkbLayout& xkb_layout) {
  const QDomNodeList props(root.childNodes());
  for (int prop_idx = 0; prop_idx < props.length(); prop_idx++) {
    const QDomNode prop(props.at(prop_idx));
    if (prop.nodeName() == "name") {
      xkb_layout.name = prop.toElement().text();
    } else if (prop.nodeName() == "description") {
      xkb_layout.description = prop.toElement().text();
    } else if (prop.nodeName() == "shortDescription") {
      xkb_layout.short_description = prop.toElement().text();
    } else if (prop.nodeName() == "languageList") {
      // Read layout / configItem / languageList
      const QDomNodeList lang_nodes(prop.childNodes());
      for (int lang_idx = 0; lang_idx < lang_nodes.length(); lang_idx++) {
        const QDomNode lang_node(lang_nodes.at(lang_idx));
        xkb_layout.language_list.append(lang_node.toElement().text());
      }
    }
  }
}

// Read layoutList node.
void ReadLayoutList(const QDomNode& root, XkbLayoutList& layout_list) {
  const QDomNodeList layout_nodes(root.childNodes());
  for (int layout_idx = 0; layout_idx < layout_nodes.length(); layout_idx++) {
    XkbLayout xkb_layout;
    const QDomNodeList content_nodes(layout_nodes.at(layout_idx).childNodes());
    for (int content_idx = 0; content_idx < content_nodes.length();
         content_idx++) {
      const QDomNode content_node(content_nodes.at(content_idx));
      if (content_node.nodeName() == "configItem") {
        // Read layout / configItem
        ReadLayoutConfigItem(content_node, xkb_layout);

      } else if (content_node.nodeName() == "variantList") {
        // Read layout / variantList
        ReadLayoutVariantList(content_node, xkb_layout.variant_list);
      }
    }
    layout_list.append(xkb_layout);
  }
}

// Read xkb config file at |filepath|. Returns false if failed.
bool ReadConfig(const QString& filepath, XkbConfig& config) {
  QDomDocument doc;
  if (!doc.setContent(ReadFile(filepath), true)) {
    return false;
  }

  const QDomElement root = doc.documentElement();
  const QDomNodeList nodes(root.childNodes());

  for (int index = 0; index < nodes.length(); index++) {
    const QDomNode node = nodes.at(index);
    if (node.nodeName() == "modelList") {
      // Read model list.
      ReadModelList(node, config.model_list);
    } else if (node.nodeName() == "layoutList") {
      // Read layout list.
      ReadLayoutList(node, config.layout_list);
    }
  }

  return true;
}

XkbConfig GetXkbConfig() {
  XkbConfig config;
  if (!ReadConfig(kXkbBaseRule, config)) {
    qWarning() << "Failed to read xkb config file" << kXkbBaseRule;
    // Reset locale.
    (void) setlocale(LC_ALL, kDefaultLang);
    return config;
  }


  XkbConfig reset;
  XKbLayoutVariantList variant_list;
  for (XkbLayout& layout : config.layout_list) {
      XkbLayoutVariant variant;
      variant.name = layout.name;
      variant.layout_name = layout.name;
      variant.description = GetLocalDesc(layout.description);
      variant.short_description = layout.short_description;
      variant.language_list = layout.language_list;
      layout.variant_list.prepend(variant);

      // 保存键盘布局
      for (XkbLayoutVariant& var : layout.variant_list) {
           var.layout_name = layout.name;
      }

      if (layout.description == "Taiwanese") {
          variant_list = layout.variant_list;
      } else {
          reset.layout_list.append(layout);
      }
  }

  // 合并台湾语和汉语
  for (XkbLayout& layout : reset.layout_list) {
      if (layout.description == "Chinese") {
          layout.variant_list += variant_list;
      }
      layout.description = GetLocalDesc(layout.description);
  }

  // NOTE(xushaohua): Do not read extra keyboard layout list currently.
//  if (!ReadConfig(kXkbExtraRule, config)) {
//    qWarning() << "Failed to read xkb config file" << kXkbExtraRule;
//  }

  (void) setlocale(LC_ALL, kDefaultLang);

  return reset;
}





double ConvertPos(const QString& pos, int digits) {
  if (pos.length() < 4 || digits > 9) {
    return 0.0;
  }

  const QString integer = pos.left(digits + 1);
  const QString fraction = pos.mid(digits + 1);
  const double t1 = integer.toDouble();
  const double t2 = fraction.toDouble();
  if (t1 > 0.0) {
    return t1 + t2 / pow(10.0, fraction.length());
  } else {
    return t1 - t2 / pow(10.0, fraction.length());
  }
}

ZoneInfoList GetZoneInfoList() {
  ZoneInfoList list;
  const QString content(ReadFile("/usr/share/zoneinfo/zone.tab"));
  for (const QString& line : content.split('\n')) {
    if (!line.startsWith('#')) {
      const QStringList parts(line.split('\t'));
      // Parse latitude and longitude.
      if (parts.length() >= 3) {
        if (parts.at(2).contains("Antarctica")){
            continue;
        }

        const QString coordinates = parts.at(1);
        int index = coordinates.indexOf('+', 3);
        if (index == -1) {
          index = coordinates.indexOf('-', 3);
        }
        Q_ASSERT(index > -1);
        const double latitude = ConvertPos(coordinates.left(index), 2);
        const double longitude = ConvertPos(coordinates.mid(index), 3);
        const ZoneInfo zone_info = {parts.at(0), parts.at(2),
                                    latitude, longitude, 0.0};
        list.append(zone_info);
      }
    }
  }
  return list;
}






}
