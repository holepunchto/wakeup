#include <appling.h>
#include <sys/types.h>
#include <unistd.h>

#include "../../include/wakeup.h"
#include "../platform.h"

int
wakeup_launch (const appling_app_t *app, const char *url) {
  pid_t pid = fork();

  if (pid < 0) return -1;

  if (pid == 0) execlp(app->path, url, NULL);

  return 0;
}
