#define RED_LED 0
#define GREEN_LED 2
const int16_t minTemp = -50;
const int16_t maxTemp = 150;
const int tempPin = A1;
const float threshold = 40.0;

float calTemp(uint16_t sample) {
  uint16_t volt = map(sample, 0, 4096, 0, 1460);
  float temp = (5.506 - sqrt(pow(-5.506, 2) + 4*0.00176*(870.6 - volt))) / (2*(-0.00176)) + 30.0;
  if (temp > maxTemp)
    return maxTemp;
  else if (temp < minTemp)
    return minTemp;
  else
    return temp;
}

void setup() {
  Serial.begin(115200);
  pinMode(RED_LED, OUTPUT);
}

void loop() {
  uint16_t value = analogRead(tempPin);
  float temp = calTemp(value);
  Serial.println("Temp: ");
  Serial.println(temp);
  if(temp > threshold) {
    digitalWrite(RED_LED, HIGH);
    digitalWrite(GREEN_LED, LOW);
  }
  else {
    digitalWrite(RED_LED, LOW);
    digitalWrite(GREEN_LED, HIGH);
  }
}