
#include <stdio.h>

#include "mu-le.h"

int main(void) {
  bool ret = mu_display_raw();
  if (!ret) fprintf(stdout, "failed to put terminal into raw mode\n");

  ret = mu_display_canon();
  if (!ret) fprintf(stdout, "failed to put terminal back into canon\n");

  mu_display_deinit();
}
