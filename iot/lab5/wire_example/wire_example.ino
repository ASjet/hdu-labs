#include <Wire.h>

byte x = 0;
setup() {
  Wire.begin();
}

loop() {
  Wire.beginTransmission();
  // ...

  Wire.endTransmission();
}