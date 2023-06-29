#include <appling.h>
#include <stddef.h>

#include "../include/wakeup.h"

typedef struct appling_app_with_link_s appling_app_with_link_t;

struct appling_app_with_link_s {
  appling_app_t app;
  appling_link_t link;
};

/**
 * @todo This should be read from a configuration file somewhere.
 */
static const appling_app_with_link_t apps[] = {
  {
    .app = {
#if defined(APPLING_OS_DARWIN)
      .path = "/Applications/Keet.app",
#endif
    },
    .link = {
      .key = {0x4b, 0x32, 0x78, 0xfc, 0x44, 0xe9, 0x71, 0x6c, 0x03, 0x42, 0x71, 0x5f, 0x42, 0xe3, 0x14, 0x05, 0x0a, 0x3c, 0x82, 0x5a, 0x51, 0x05, 0x6a, 0xc5, 0x3e, 0xe8, 0x17, 0x09, 0x86, 0xa8, 0xbb, 0x86},
    },
  },
};

int
wakeup (const char *url) {
  int err;

  appling_link_t link;

  err = appling_parse(url, &link);
  if (err < 0) return err;

  const appling_app_t *app;

  for (size_t i = 0, n = sizeof(apps) / sizeof(appling_app_with_link_t); i < n; i++) {
    if (memcmp(apps[i].link.key, link.key, sizeof(appling_key_t)) == 0) {
      app = &apps[i].app;
      break;
    }
  }

  if (app == NULL) return -1;

  return wakeup_launch(app->path, 1, &url);
}
