#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <termios.h>
#include "mu-array.h"

#define DISPLAY_FILE STDIN_FILENO

struct display {
  struct termios original;
  struct termios raw;
  struct array lines;
};

bool mu_display_raw(void);
bool mu_display_canon(void);
