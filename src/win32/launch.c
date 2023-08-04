#include <appling.h>
#include <shellapi.h>

#include "../../include/wakeup.h"
#include "../platform.h"

int
wakeup_launch (const appling_app_t *app, const char *url) {
  INT_PTR res = (INT_PTR) ShellExecute(NULL, "open", app->path, url, NULL, 0);

  return res == 32 ? 0 : -1;
}
