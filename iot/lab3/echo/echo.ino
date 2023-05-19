String buffer = "";
bool stringComplete = false;

void setup() {
  Serial.begin(115200);
  buffer.reserve(512);
}

void loop() {
  if(stringComplete) {
    Serial.println(buffer);
    buffer = "";
    stringComplete = false;
  }
}

void serialEvent() {
  char chr = 0;
  while(Serial.available()) {
    while((chr = (char)Serial.read()) != '\n')
      buffer += chr;
    stringComplete = true;
  }
}