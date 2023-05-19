#include <Wire.h>
#include <SPI.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
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
#define ADDRESS 0x40
#define REG_TEMPERATURE 0x00
#define REG_HUMIDITY 0x01
#define REG_CONFIGURATION 0x02
#define NORMAL_OPERATION 0x0000
const float temp_threshold = 28.0;
const float humi_threshold = 40.0;
const float EPSINON = 0.00001;
WiFiServer server(80);
////////////////////////////////////////////////////////////////////////////////
// your network name also called SSID
char ssid[] = "iot-wifilab-bbb";
// your network password
char password[] = "123456789";
// your network key Index number (needed only for WEP)
int keyIndex = 0;
//////////////////////////////////////////////////////////////////
void writeSPI(uint8_t regAddress, uint8_t data) {
  digitalWrite(LDC_CS, LOW);
  SPI.transfer(regAddress | LDC_WRITEBIT);
  SPI.transfer(data);
  digitalWrite(LDC_CS, HIGH);
}

uint8_t readSPI(uint8_t regAddress) {
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
  writeSPI(REG_RPMAX, VALUE_RPMAX);
  writeSPI(REG_RPMIN, VALUE_RPMIN);
  writeSPI(REG_SENSORFREQUENCY, VALUE_SENSORFREQUENCY);
  writeSPI(REG_LDCCONFIG, VALUE_LDCCONFIG);
  writeSPI(REG_CLKCONFIG, VALUE_CLKCONFIG);
  writeSPI(REG_THRESHOLDHIGH_LSB, VALUE_THRESHOLDHIGH_LSB);
  writeSPI(REG_THRESHOLDHIGH_MSB, VALUE_THRESHOLDHIGH_MSB);
  writeSPI(REG_THRESHOLDLOW_LSB, VALUE_THRESHOLDLOW_LSB);
  writeSPI(REG_THRESHOLDLOW_MSB, VALUE_THRESHOLDLOW_MSB);
  writeSPI(REG_PWRCONFIG, VALUE_PWRCONFIG);
}

uint16_t ldc1000_getProximity(void) {
  uint16_t temp[2] = {0};
  uint16_t proximity = 0;
  temp[0] = readSPI(REG_PROXIMITY_LSB) & 0x00FF;
  temp[1] = readSPI(REG_PROXIMITY_MSB) & 0x00FF;
  proximity = (temp[1] << 8) | temp[0];
  return proximity;
}

uint32_t ldc1000_getFrequency(void) {
  uint32_t count[3] = {0};
  uint32_t frequency = 0;
  count[0] = readSPI(REG_FREQUENCY_LSB) & 0x000000FF;
  count[1] = readSPI(REG_FREQUENCY_MID) & 0x000000FF;
  count[2] = readSPI(REG_FREQUENCY_MSB) & 0x000000FF;
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
void send_header(WiFiClient& client) {
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("Connection: close");  // the connection will be closed after completion of the response
  client.println("Refresh: 5");  // refresh the page automatically every 5 sec
  client.println();
}
void alert_temp(WiFiClient& client, float temp) {
  digitalWrite(RED_LED, ((temp > temp_threshold)?HIGH:LOW));
  Serial.print("temperature: ");
  Serial.println(temp);
  client.print("temperature: ");
  client.print(temp);
  if(temp > temp_threshold) {
    Serial.println("!tempover!");
    client.print(" <b>tempover</b>");
  }
}
void alert_humi(WiFiClient& client, float humi) {
  digitalWrite(YELLOW_LED, ((humi > humi_threshold)?HIGH:LOW));
  Serial.print("humidity: ");
  Serial.println(humi);
  client.print("humidity: ");
  client.print(humi);
  if(humi > humi_threshold)
    Serial.println("!humiover!");
    client.print(" <b>humiover</b>");
}
void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("Network Name: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}
//////////////////////////////////////////////////////////////////
void setup() {
  pinMode(RED_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  Serial.begin(115200);
  hdc1080_init();
  ldc1000_init();

  // attempt to connect to Wifi network:
  Serial.print("Attempting to connect to Network named: ");
  // print the network name (SSID);
  Serial.println(ssid);
  // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
  WiFi.begin(ssid, password);
  while ( WiFi.status() != WL_CONNECTED) {
    // print dots while we wait to connect
    Serial.print(".");
    delay(300);
  }

  Serial.println("\nYou're connected to the network");
  Serial.println("Waiting for an ip address");

  while (WiFi.localIP() == INADDR_NONE) {
    // print dots while we wait for an ip addresss
    Serial.print(".");
    delay(300);
  }

  // you're connected now, so print out the status
  printWifiStatus();

  Serial.println("Starting webserver on port 80");
  server.begin();                           // start the web server on port 80
  Serial.println("Webserver started!");

}
void loop() {
  WiFiClient client = server.available();
  if (client) {
    Serial.println("new client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          // send a standard http response header
          send_header(client);
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          delay(1);
          alert_temp(client, hdc1080_getTemperature());
          client.println("<br />");
          delay(1);
          alert_humi(client, hdc1080_getHumidity());
          client.println("<br />");
          delay(1);
          uint16_t proximity = ldc1000_getProximity();
          uint32_t frequency = ldc1000_getFrequency();
          float induct = ldc1000_calcInductance(frequency);
          Serial.print("Proximity: ");
          Serial.println(proximity);
          Serial.print("Frequency: ");
          Serial.println(frequency);
          Serial.print("Indcutance: ");
          Serial.println(induct);

          client.print("Proximity: ");
          client.print(proximity);
          client.println("<br />");
          delay(1);
          client.print("Frequency: ");
          client.print(frequency);
          client.println("<br />");
          delay(1);
          client.print("Indcutance: ");
          client.print(induct);
          client.println("<br />");
          delay(1);
          client.println("</html>");
          delay(1);
          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        }
        else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);

    // close the connection:
    client.stop();
    Serial.println("client disonnected");
  }
}