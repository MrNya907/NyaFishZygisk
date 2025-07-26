#ifndef DAEMON_H
#define DAEMON_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <stdbool.h>

#include <unistd.h>

#ifdef __LP64__
  #define LP_SELECT(lp32, lp64) lp64
#else
  #define LP_SELECT(lp32, lp64) lp32
#endif

#define SOCKET_FILE_NAME LP_SELECT("cp32", "cp64") ".sock"

enum nyafishzygiskd_actions {
  PingHeartbeat,
  GetProcessFlags,
  GetInfo,
  ReadModules,
  RequestCompanionSocket,
  GetModuleDir,
  ZygoteRestart,
  SystemServerStarted,
  UpdateMountNamespace
};

struct zygisk_modules {
  char **modules;
  size_t modules_count;
};

enum root_impl {
  ROOT_IMPL_NONE,
  ROOT_IMPL_APATCH,
  ROOT_IMPL_KERNELSU,
  ROOT_IMPL_MAGISK
};

struct nyafishzygisk_info {
  struct zygisk_modules *modules;
  enum root_impl root_impl;
  pid_t pid;
  bool running;
};

enum mount_namespace_state {
  Clean,
  Mounted
};

#define TMP_PATH "/data/adb/nyafishzygisk"

static inline const char *nyafishzygiskd_get_path() {
  return TMP_PATH;
}

int nyafishzygiskd_connect(uint8_t retry);

bool nyafishzygiskd_ping();

uint32_t nyafishzygiskd_get_process_flags(uid_t uid, const char *const process);

void nyafishzygiskd_get_info(struct nyafishzygisk_info *info);

void free_nyafishzygisk_info(struct nyafishzygisk_info *info);

bool nyafishzygiskd_read_modules(struct zygisk_modules *modules);

void free_modules(struct zygisk_modules *modules);

int nyafishzygiskd_connect_companion(size_t index);

int nyafishzygiskd_get_module_dir(size_t index);

void nyafishzygiskd_zygote_restart();

void nyafishzygiskd_system_server_started();

bool nyafishzygiskd_update_mns(enum mount_namespace_state nms_state, char *buf, size_t buf_size);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* DAEMON_H */