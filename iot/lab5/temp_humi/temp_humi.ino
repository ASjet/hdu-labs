#include <Wire.h>
#define ADDRESS 0x40
#define REG_TEMPERATURE 0x00
#define REG_HUMIDITY 0x01
#define REG_CONFIGURATION 0x02
#define NORMAL_OPERATION 0x0000
const float temp_threshold = 28.0;
const float humi_threshold = 40.0;
//////////////////////////////////////////////////////////////////
uint16_t read(uint8_t regAddress) {
  uint16_t data = 0;
  Wire.beginTransmission(ADDRESS);
  Wire.write(regAddress);
  Wire.endTransmission();
  delay(40);
  Wire.requestFrom(ADDRESS, 2);
  if(Wire.available() >= 2) {
    data = Wire.read() << 8;
    data |= Wire.read();
  }
  return data;
}
void write(uint8_t regAddress,uint8_t*pdata,uint8_t length) {
  Wire.beginTransmission(ADDRESS);
  Wire.write(regAddress);
  Wire.write(pdata,length);
  Wire.endTransmission();
}
void hdc1080_init(void) {
  Wire.begin();
  uint8_t data[2]={0};
  data[0]=(NORMAL_OPERATION >>8)&0xFF;
  data[1]= NORMAL_OPERATION &0xFF;
  write(REG_CONFIGURATION, data,2);
}
float hdc1080_getTemperature(void) {
  uint16_t temperature =0;
  temperature = read(REG_TEMPERATURE);
  return(temperature /65536.0*165.0-40.0);
}
float hdc1080_getHumidity(void) {
  uint16_t humidity =0;
  humidity = read(REG_HUMIDITY);
  return (humidity / 65536.0*100.0);
}
void alert_temp(float temp) {
  digitalWrite(RED_LED, ((temp > temp_threshold)?HIGH:LOW));
  Serial.print("temperature: ");
  Serial.println(temp);
  if(temp > temp_threshold)
    Serial.println("tempover");
}
void alert_humi(float humi) {
  digitalWrite(YELLOW_LED, ((humi > humi_threshold)?HIGH:LOW));
  Serial.print("humidity: ");
  Serial.println(humi);
  if(humi > humi_threshold)
    Serial.println("humiover");
}
//////////////////////////////////////////////////////////////////
void setup() {
  pinMode(RED_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  Serial.begin(115200);
  hdc1080_init();
}
void loop() {
  alert_temp(hdc1080_getTemperature());
  alert_humi(hdc1080_getHumidity());
  delay(1000);
}
