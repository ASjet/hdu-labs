#include "def.h"

std::unordered_map<PinName, Pin*> pins;

void
pinMode(int _pin, PinDir _mode)
{
  pins[static_cast<PinName>(_pin)]->writeDir(_mode);
}

PinStat
digitalRead(int _pin)
{
  return pins[static_cast<PinName>(_pin)]->readStat();
}

void
digitalWrite(int _pin, PinStat _stat)
{
  Pin* p = pins[static_cast<PinName>(_pin)];
  if (p->readDir() == OUTPUT)
    p->writeStat(_stat);
  led_refresh();
}