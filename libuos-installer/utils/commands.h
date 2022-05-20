#ifndef COMMANDS_H
#define COMMANDS_H

#include <QByteArray>

static const QByteArray proto_begin("PROTO_BEGIN");
static const QByteArray proto_end("PROTO_END");
static const QByteArray type_begin("TYPE_BEGIN");
static const QByteArray type_end("TYPE_BEGIN");
static const QByteArray content_begin("CONTENT_BEGIN");
static const QByteArray content_end("CONTENT_BEGIN");
static const int min_len = proto_begin.length()+proto_end.length()+type_begin.length()+type_end.length()+content_begin.length()+content_end.length();

static const QByteArray type_file("FILE");
static const QByteArray type_cmd("CMD");

static const QByteArray heartbeat_packets("HEARTBEAT_PACKETS");

static const QByteArray cmd_get_devices("CMD_GET_DEVICES");
static const QByteArray cmd_set_parted("CMD_SET_PARTED");
static const QByteArray cmd_set_sys_info("CMD_SET_SYS_INFO");
static const QByteArray cmd_start_install("CMD_START_INSTALL");
static const QByteArray cmd_stop_install("CMD_STOP_INSTALL");
static const QByteArray cmd_info_progress("CMD_INFO_PROGRESS");
static const QByteArray cmd_exit_server("CMD_EXIT_SERVER");
static const QByteArray cmd_set_component("CMD_SET_COMPONENT");


static const QByteArray cmd_notify_response("CMD_NOTIFY_RESPONSE");
static const QByteArray cmd_notify_install_result("CMD_NOTIFY_INSTALL_RESULT");



#endif // COMMANDS_H
