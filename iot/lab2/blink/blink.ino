#define RED 0
#define YELLOW 1
#define GREEN 2
#define LED_CNT 3

const byte leds[] = {
   RED_LED,
   YELLOW_LED,
   GREEN_LED,
};

const byte intpin = PUSH2;
int l = 0;

void setup() {
  for(int i = 0; i < LED_CNT; ++i) {
    pinMode(leds[i], OUTPUT);
  }
  pinMode(intpin, INPUT_PULLUP);
  attachInterrupt(intpin, blink, RISING);
}

void loop() {
}


void blink() {
  delay(20);
  if(digitalRead(intpin) == HIGH) {
    l = (++l) % 3;
    for(int i = 0; i < LED_CNT; ++i) {
      digitalWrite(leds[i], LOW);
    }
    digitalWrite(leds[l], HIGH);
  }
}