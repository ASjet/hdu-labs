#include "def.h"


const int red_x = 27;
const int red_y = 2;

const int green_x = 27;
const int green_y = 4;

const int yellow_x = 27;
const int yellow_y = 3;

void
led_refresh(void)
{
  LEDPin* rl = static_cast<LEDPin*>(pins[RED_LED]);
  LEDPin* gl = static_cast<LEDPin*>(pins[GREEN_LED]);
  LEDPin* yl = static_cast<LEDPin*>(pins[YELLOW_LED]);
  mvwaddch(win, red_y, red_x, rl->led());
  mvwaddch(win, green_y, green_x, gl->led());
  mvwaddch(win, yellow_y, yellow_x, yl->led());
  dock();
  wrefresh(win);
}

void
led_disp()
{
  while (1) {
    led_refresh();
  }
}

void
enable_led_disp(void)
{
  int err;
  std::thread p(led_disp);
  p.detach();
}

void
led_init()
{
  wrefresh(win);
  wclear(win);
  mvwprintw(win, 0, 0, "*******CC3200 Core Board*******");
  wrefresh(win);
  mvwprintw(win, 1, 0, "*                     PUSH[2] *");
  wrefresh(win);
  mvwprintw(win, 2, 0, "*                     RED [ ] *");
  wrefresh(win);
  mvwprintw(win, 3, 0, "*                  YELLOW [ ] *");
  wrefresh(win);
  mvwprintw(win, 4, 0, "*                   GREEN [ ] *");
  wrefresh(win);
  mvwprintw(win, 5, 0, "*                     PUSH[1] *");
  wrefresh(win);
  mvwprintw(win, 6, 0, "*******************************");
  wrefresh(win);
  // enable_led_disp();
}