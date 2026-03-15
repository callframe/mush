#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <termios.h>

#define DISPLAY_FILE STDIN_FILENO

struct display {
  struct termios original;
  struct termios raw;
};

bool mu_display_raw(void);
bool mu_display_canon(void);
