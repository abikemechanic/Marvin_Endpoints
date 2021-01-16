#include <Arduino.h>
#include <PubSubClient.h>
#include <Adafruit_BME280.h>
#include <ESP8266WiFi.h>
#include <SPI.h>
#include <Wire.h>
#include <LittleFS.h>

#include <MQTT_Controller.hpp>

#define WLAN_SSID   "JackInTheBox"
#define WLAN_PASS   "SofiaSoup2015"
#define ID_PREFIX     "relay_box"

WiFiClient espClient;
PubSubClient mqttClient(espClient);
MQTT_Controller mqtt_controller(espClient);

#define MQTT_SERVER     "192.168.1.2"
#define MQTT_PORT       "1883"

void connect_wifi()
{
  Serial.println("connecting wifi");
  Serial.print("ssid: ");
  Serial.println(WLAN_SSID);
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(WLAN_SSID, WLAN_PASS);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(100);
    Serial.print(".");
  }

  randomSeed(micros());
  Serial.print("local ip: ");
  Serial.println(WiFi.localIP());
}

void reconnect()
{
  while (mqttClient.connected())
  {
    String client_id = "Marvin_";
    client_id += String(random(0xffff), HEX);

    if (mqttClient.connect(client_id.c_str()))
    {
      Serial.println("mqtt connected");
    }
    else
    {
      Serial.println("failed mqtt connection");
      delay(1000);
    }
  }
}

void callback(char* topic, char* payload, unsigned int length)
{
  // call MQTT_Controller callback   
}


void setup() {
  Serial.begin(9600);
  Serial.println();

  connect_wifi();
  
  mqtt_controller.read_config();
}

void loop() {
  // put your main code here, to run repeatedly:
}