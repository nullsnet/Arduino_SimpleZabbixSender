#include <M5StickC.h>
#include <WiFi.h>
#include <Wire.h>

#include "Adafruit_Sensor.h"
#include "Adafruit_SHT31.h"

#include "ZabbixSender.hpp"

// Create an trapper item in Zabbix beforehand.
const char * HOST_NAME = "ArduinoSensor";
const String SENSOR_ID = "home.sensor1";

// Set your Zabbix server parameter
const char * ZABBIX_IP = "YOUR_ZABBIX_IP";
const int ZABBIX_PORT = 10051;

// Set yout WiFi settings.
const char * SSID = "YOUR_WIFI_SSID";
const char * PASSPHRASE = "YOUR_WIFI_PASSPHRASE";

Adafruit_SHT31 sht3x = Adafruit_SHT31(&Wire);
WiFiClient client;

void setup() {
  M5.begin();
  Wire.begin(26,32);
  sht3x.begin(0x44);

  WiFi.begin(SSID,PASSPHRASE);
}

void loop() {
  ZabbixSender data;
  data.Add(HOST_NAME,SENSOR_ID + ".temperature",String(sht3x.readTemperature()));
  data.Add(HOST_NAME,SENSOR_ID + ".humidity",String(sht3x.readHumidity()));

  data.Send(Serial); // Debug Output

  client.connect(ZABBIX_IP, ZABBIX_PORT);
  data.Send(client);
  delay(5000);
}