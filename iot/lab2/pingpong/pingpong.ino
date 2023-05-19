#define RED 0
#define YELLOW 1
#define GREEN 2
#define LED_CNT 3

const byte leds[] = {
   RED_LED,
   YELLOW_LED,
   GREEN_LED,
};

const byte intpin1 = PUSH1;
const byte intpin2 = PUSH2;
int dir = 1;
int l = 0;

void setall(int stat) {
  for(int i = 0; i < LED_CNT; ++i) {
    digitalWrite(leds[i], stat);
  }
}

void lose(int cnt) {
  for(int i = 0; i < cnt; ++i) {
    setall(HIGH);
    delay(150);
    setall(LOW);
    delay(150);
  }
}

void hit1() {
  delay(20);
  if(digitalRead(intpin1) == HIGH) {
    if(l == 2)
      dir = -1;
  }
}

void hit2() {
  delay(20);
  if(digitalRead(intpin2) == HIGH) {
    if(l == 0)
      dir = 1;
  }
}

// void hit2() {
//   delay(20);
//   if(digitalRead(intpin2) == HIGH) {
//     if(l == 0 || l == 2)
//       dir = -dir;
//   }
// }

void setup() {
  for(int i = 0; i < LED_CNT; ++i) {
    pinMode(leds[i], OUTPUT);
  }
  pinMode(intpin1, INPUT_PULLUP);
  pinMode(intpin2, INPUT_PULLUP);
  attachInterrupt(intpin1, hit1, RISING);
  attachInterrupt(intpin2, hit2, RISING);
}

void loop() {
  delay(500);
  l += dir;
  if(l == 3 || l == -1) {
    lose(3);
    l = 1;
    dir = -1;
  }
  setall(LOW);
  digitalWrite(leds[l], HIGH);
}
