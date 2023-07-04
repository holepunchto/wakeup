#include <appling.h>
#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <uv.h>

#include "../include/wakeup.h"
#include "platform.h"

static appling_app_t *wakeup_apps = NULL;
static size_t wakeup_apps_len = 0;

static uv_once_t wakeup_init_guard = UV_ONCE_INIT;

static void
on_paths (appling_paths_t *req, int status, const appling_app_t *apps, size_t apps_len) {
  assert(status == 0);

  wakeup_apps = malloc(apps_len * sizeof(appling_app_t));
  wakeup_apps_len = apps_len;

  memcpy(wakeup_apps, apps, apps_len * sizeof(appling_app_t));
}

static void
on_wakeup_init (void) {
  int err;

  uv_loop_t loop;
  err = uv_loop_init(&loop);
  assert(err == 0);

  appling_paths_t req;
  err = appling_paths(&loop, &req, NULL, on_paths);
  assert(err == 0);

  err = uv_run(&loop, UV_RUN_DEFAULT);
  assert(err == 0);

  err = uv_loop_close(&loop);
  assert(err == 0);
}

int
wakeup (const char *url) {
  uv_once(&wakeup_init_guard, on_wakeup_init);

  int err;

  appling_link_t link;
  err = appling_parse(url, &link);
  if (err < 0) return err;

  const appling_app_t *app = NULL;

  for (size_t i = 0; i < wakeup_apps_len; i++) {
    if (memcmp(wakeup_apps[i].key, link.key, sizeof(appling_key_t)) == 0) {
      app = &wakeup_apps[i];
      break;
    }
  }

  if (app == NULL) return -1;

  return wakeup_launch(app, url);
}
