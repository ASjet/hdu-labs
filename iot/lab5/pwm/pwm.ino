const uint8_t ledPin = 40;

const uint8_t buttonPin = PUSH1;

const uint8_t brightStep = 64;

uint8_t bright = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(buttonPin, INPUT_PULLUP);
  analogWrite(ledPin,bright);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(buttonPin)) {
    delay(20);

    //watting for push up
    while(digitalRead(buttonPin));

    bright += brightStep;
    analogWrite(ledPin,bright);
    Serial.print("bright: ");
    Serial.println(bright);
  }
}