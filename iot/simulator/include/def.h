#ifndef DEF_H
#define DEF_H

#include <ncurses.h>
#include <string>
#include <thread>
#include <unordered_map>
#include "sim.h"

extern WINDOW* win;
const int KEY_PUSH_INTERVAL = 50;

class Pin{
  public:
    inline PinStat readStat() const { return stat; }
    inline void writeStat(PinStat _stat) { stat = _stat; }
    inline PinDir readDir() const { return dir; }
    inline void writeDir(PinDir _dir) { dir = _dir; }

  protected:
    PinStat stat = UNKNOWN;
    PinDir dir = INVALID;
};

class LEDPin: public Pin {
  public:
    inline void turnon() { stat = HIGH; }
    inline void turnoff() { stat = LOW; }
    inline char led() const { return (stat == HIGH)? LIGHT: DARK; }
  private:
    static const char LIGHT = '*';
    static const char DARK = '.';
};

// pin
extern std::unordered_map<PinName, Pin*> pins;


void led_refresh();

void
led_init();
void led_disp(void);

// utils
void
init(void);

void
dock(void);

// the setup routine runs once
void
setup();

// the loop routine runs over and over again forever
void
loop();



#endif