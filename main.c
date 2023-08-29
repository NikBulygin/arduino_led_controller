#include "main_window/main_window_init.h"

#include "structures/config.h"

int main(int argc, char *argv[]) {
  Config* cfg = cfg_init("config.cfg");
  main_window_init(cfg, argc, argv);
}
