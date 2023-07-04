#include "../../include/wakeup.h"

int
main (int argc, char *argv[]) {
  if (argc < 1) return 1;

  int err = wakeup(argv[0]);

  return err < 0 ? 1 : 0;
}
