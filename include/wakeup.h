#ifndef WAKEUP_H
#define WAKEUP_H

#ifdef __cplusplus
extern "C" {
#endif

#include <appling.h>
#include <stddef.h>

typedef struct wakeup_app_s wakeup_app_t;

struct wakeup_app_s {
  appling_key_t key;
  const char *path;
};

int
wakeup (const char *url);

int
wakeup_launch (const wakeup_app_t *app, size_t argc, const char *argv[]);

#ifdef __cplusplus
}
#endif

#endif // WAKEUP_H
