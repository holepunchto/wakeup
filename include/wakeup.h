#ifndef WAKEUP_H
#define WAKEUP_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

int
wakeup (const char *url);

int
wakeup_launch (const char *app, size_t argc, const char *argv[]);

#ifdef __cplusplus
}
#endif

#endif // WAKEUP_H
