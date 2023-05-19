#include "SPI.h"

#define LDC_CS 8
#define LDC_WRITEBIT 0x00
#define LDC_READBIT 0x80
#define REG_RPMAX 0x01
#define REG_RPMIN 0x02
#define REG_SENSORFREQUENCY 0x03
#define REG_LDCCONFIG 0x04
#define REG_CLKCONFIG 0x05
#define REG_THRESHOLDHIGH_LSB 0x06
#define REG_THRESHOLDHIGH_MSB 0x07
#define REG_THRESHOLDLOW_LSB 0x08
#define REG_THRESHOLDLOW_MSB 0x09
#define REG_INTCONFIG 0x0A
#define REG_PWRCONFIG 0x0B
#define REG_PROXIMITY_LSB 0x21
#define REG_PROXIMITY_MSB 0x22
#define REG_FREQUENCY_LSB 0x23
#define REG_FREQUENCY_MID 0x24
#define REG_FREQUENCY_MSB 0x25
#define VALUE_SENSORFREQUENCY 0xD1
#define VALUE_LDCCONFIG 0x17
#define VALUE_CLKCONFIG 0x02
#define VALUE_INICONFIG 0x04
#define VALUE_THRESHOLDHIGH_LSB 0x50
#define VALUE_THRESHOLDHIGH_MSB 0x14
#define VALUE_THRESHOLDLOW_LSB 0xC0
#define VALUE_THRESHOLDLOW_MSB 0x12
#define VALUE_PWRCONFIG 0x01
#define VALUE_RPMAX 0x13
#define VALUE_RPMIN 0x3A
#define LDC_FREQUENCY_EXT 8
#define LDC_RESPONSE_TIME 6144
#define LDC_PARALLEI_CAP 100

const float EPSINON = 0.00001;

void write(uint8_t regAddress, uint8_t data) {
  digitalWrite(LDC_CS, LOW);
  SPI.transfer(regAddress | LDC_WRITEBIT);
  SPI.transfer(data);
  digitalWrite(LDC_CS, HIGH);
}

uint8_t read(uint8_t regAddress) {
  uint8_t result = 0;
  digitalWrite(LDC_CS, LOW);
  SPI.transfer(regAddress | LDC_READBIT);
  result = SPI.transfer(0x00);
  digitalWrite(LDC_CS, HIGH);
  return result;
}

void ldc1000_init(void) {
  pinMode(LDC_CS, OUTPUT);
  SPI.begin();
  write(REG_RPMAX, VALUE_RPMAX);
  write(REG_RPMIN, VALUE_RPMIN);
  write(REG_SENSORFREQUENCY, VALUE_SENSORFREQUENCY);
  write(REG_LDCCONFIG, VALUE_LDCCONFIG);
  write(REG_CLKCONFIG, VALUE_CLKCONFIG);
  write(REG_THRESHOLDHIGH_LSB, VALUE_THRESHOLDHIGH_LSB);
  write(REG_THRESHOLDHIGH_MSB, VALUE_THRESHOLDHIGH_MSB);
  write(REG_THRESHOLDLOW_LSB, VALUE_THRESHOLDLOW_LSB);
  write(REG_THRESHOLDLOW_MSB, VALUE_THRESHOLDLOW_MSB);
  write(REG_PWRCONFIG, VALUE_PWRCONFIG);
}

uint16_t ldc1000_getProximity(void) {
  uint16_t temp[2] = {0};
  uint16_t proximity = 0;
  temp[0] = read(REG_PROXIMITY_LSB) & 0x00FF;
  temp[1] = read(REG_PROXIMITY_MSB) & 0x00FF;
  proximity = (temp[1] << 8) | temp[0];
  return proximity;
}

uint32_t ldc1000_getFrequency(void) {
  uint32_t count[3] = {0};
  uint32_t frequency = 0;
  count[0] = read(REG_FREQUENCY_LSB) & 0x000000FF;
  count[1] = read(REG_FREQUENCY_MID) & 0x000000FF;
  count[2] = read(REG_FREQUENCY_MSB) & 0x000000FF;
  frequency = (count[2] << 16) | (count[1] << 8) | count[0];
  return frequency;
}

float ldc1000_calcInductance(uint32_t frequency) {
  if (!frequency) {
    return 0.0;
  }

  float sensorFreq =
      (1.0 / 3) * (1.0 * LDC_FREQUENCY_EXT / frequency) * LDC_RESPONSE_TIME;
  if ((sensorFreq >= -EPSINON) && (sensorFreq <= EPSINON)) {
    return 0.0;
  }

  float inductance =
      1.0 * 1000000 / (LDC_PARALLEI_CAP * pow(TWO_PI * sensorFreq, 3));
  return inductance;
}
void setup() {
  Serial.begin(11500);
  ldc1000_init();
}

void loop() {
  uint16_t proximity = ldc1000_getProximity();
  Serial.print("Proximity:");
  Serial.print(proximity);
  uint32_t frequency = ldc1000_getFrequency();
  Serial.print("\t\tFrequency:");
  Serial.print(frequency);
  Serial.print("\t\tIndcutance:");
  Serial.println(ldc1000_calcInductance(frequency));
  delay(1000);
}