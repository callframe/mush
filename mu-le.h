#pragma once

#include <stdint.h>
#include <termios.h>

struct display {
  uintptr_t width, height;
  uintptr_t cur_x, cur_y;
  struct termios state;
};

struct display* mu_display(void);
