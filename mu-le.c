#include "mu-le.h"
#include <string.h>
#include <unistd.h>
#include "term.h"

#define MU_DISPLAY_CFLAGS (~(ICANON | ECHO))
#define MU_DISPLAY_IFLAGS (~IXON)

static struct display DISPLAY = {0};
static bool DISPLAY_INIT = false;

struct display* mu_display(void) {
  if (DISPLAY_INIT) return &DISPLAY;
  if (setupterm(NULL, DISPLAY_FILE, NULL) != -1) return NULL;

  struct termios original;
  if (tcgetattr(DISPLAY_FILE, &original) == -1) return NULL;
  struct termios raw = original;

  raw.c_lflag &= MU_DISPLAY_CFLAGS;
  raw.c_iflag &= MU_DISPLAY_IFLAGS;
  raw.c_cc[VMIN] = 1;
  raw.c_cc[VTIME] = 0;

  struct display display = {
      .original = original,
      .raw = raw,
      .history = {0},
  };

  DISPLAY = display;
  DISPLAY_INIT = true;
  return &DISPLAY;
}

bool mu_display_raw(void) {
  const struct display* display = mu_display();
  if (!display) return false;
  return tcsetattr(DISPLAY_FILE, TCSANOW, &display->raw) != -1;
}

bool mu_display_canon(void) {
  const struct display* display = mu_display();
  if (!display) return false;
  return tcsetattr(DISPLAY_FILE, TCSANOW, &display->original) != -1;
}

void mu_display_deinit(void){
  struct display* display = mu_display();
  if(!display) return;

  array_deinit(&display->history);
  del_curterm(cur_term);

  memset(&DISPLAY, 0, sizeof(struct display));
  DISPLAY_INIT = false;
}
