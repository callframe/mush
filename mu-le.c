#include "mu-le.h"
#include <stdbool.h>

static struct display DISPLAY = {0};
static bool DISPLAY_INIT = false;

struct display* mu_display(void) {
  if(DISPLAY_INIT) return &DISPLAY;



  return &DISPLAY;
}
