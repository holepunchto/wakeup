#include <appling.h>
#include <assert.h>
#include <path.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <uv.h>

#include "../include/wakeup.h"

typedef struct {
  char *url;
  appling_platform_t platform;

  struct {
    uv_process_t process;
    appling_resolve_t resolve;
    appling_lock_t lock;
  } handles;
} wakeup_t;

static void
on_process_exit (uv_process_t *handle, int64_t exit_status, int term_signal) {
  uv_close((uv_handle_t *) handle, NULL);
}

static void
on_unlock (appling_lock_t *req, int status) {
  assert(status == 0);
}

static void
on_resolve (appling_resolve_t *req, int status) {
  int err;

  assert(status == 0);

  wakeup_t *wakeup = (wakeup_t *) req->data;

  appling_path_t pear;
  size_t path_len = sizeof(appling_path_t);

  err = path_join(
    (const char *[]){req->platform->path, "bin", "pear-runtime", NULL},
    pear,
    &path_len,
    path_behavior_system
  );
  assert(err == 0);

  err = appling_unlock(req->loop, &wakeup->handles.lock, on_unlock);
  assert(err == 0);

  char *args[] = {pear, "run", "--detached", wakeup->url, NULL};

  uv_process_options_t options = {
    .exit_cb = on_process_exit,
    .file = pear,
    .args = args,
    .flags = UV_PROCESS_WINDOWS_HIDE,
    .stdio_count = 3,
    .stdio = (uv_stdio_container_t[]){
      {.flags = UV_INHERIT_FD, .data.fd = 0},
      {.flags = UV_INHERIT_FD, .data.fd = 1},
      {.flags = UV_INHERIT_FD, .data.fd = 2},
    },
  };

  err = uv_spawn(req->loop, &wakeup->handles.process, &options);
  assert(err == 0);
}

static void
on_lock (appling_lock_t *req, int status) {
  int err;

  assert(status == 0);

  wakeup_t *wakeup = (wakeup_t *) req->data;

  err = appling_resolve(req->loop, &wakeup->handles.resolve, NULL, &wakeup->platform, on_resolve);
  assert(err == 0);
}

int
wakeup (const char *url) {
  int err;

  uv_loop_t loop;
  err = uv_loop_init(&loop);
  assert(err == 0);

  wakeup_t wakeup = {.url = strdup(url)};

  wakeup.handles.resolve.data = (void *) &wakeup;
  wakeup.handles.lock.data = (void *) &wakeup;

  err = appling_lock(&loop, &wakeup.handles.lock, NULL, on_lock);
  assert(err == 0);

  err = uv_run(&loop, UV_RUN_DEFAULT);
  assert(err == 0);

  err = uv_loop_close(&loop);
  assert(err == 0);

  free(wakeup.url);

  return 0;
}
