#include <stddef.h>

#include "../../include/wakeup.h"

int
main (int argc, char *argv[]) {
  if (argc < 2) return 1;

  int err = wakeup(argv[1], NULL);

  return err < 0 ? 1 : 0;
}
