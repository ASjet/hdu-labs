#include "def.h"

static bool run_once = false;

int main() {
  if(run_once == 0) {
    init();
    setup();
    run_once = true;
  }

  while(true) {
    loop();
  }
}