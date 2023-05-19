#include "sim.h"

const int LIGHT_CNT = 3;
const int lights[] = { [0] = RED_LED, [1] = YELLOW_LED, [2] = GREEN_LED };
const int duration[] = { 2000, 500, 2000 };

const byte push = PUSH2;
const int green = 2;
int l = 0;

void
lighton(int light)
{
  digitalWrite(light, HIGH);
}
void
lightoff(int light)
{
  digitalWrite(light, LOW);
}
void
update()
{
  lighton(lights[l]);
  if (l == 2) {
    delay(duration[l] - 1000);
    for (int i = 0; i < 5; ++i) {
      lightoff(lights[l]);
      delay(100);
      lighton(lights[l]);
      delay(100);
    }
  } else {
    delay(duration[l]);
  }
  lightoff(lights[l]);
}

void
pass()
{
  l = green;
  for (int i = 0; i < LIGHT_CNT; ++i) {
    lightoff(lights[i]);
  }
  update();
}

void
setup()
{
  for (int i = 0; i < LIGHT_CNT; ++i) {
    pinMode(lights[i], OUTPUT);
  }
  pinMode(push, INPUT_PULLUP);
  attachInterrupt(push, pass, RISING);
  l = 0;
}

void
loop()
{
  update();
  l = (++l) % LIGHT_CNT;
}
