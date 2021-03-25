#include <Arduino.h>
#include <PubSubClient.h>
#include <Adafruit_BME280.h>
#include <ESP8266WiFi.h>
#include <SPI.h>
#include <Wire.h>
#include <LittleFS.h>

#include <MQTT_Controller.hpp>

#define WLAN_SSID   "SSID Name"
#define WLAN_PASS   "SSID Password"
#define ID_PREFIX     "relay_box"

const char* wlan_ssid;
const char* wlan_pass;

WiFiClient espClient;
PubSubClient mqttClient(espClient);
MQTT_Controller mqtt_controller(espClient);

#define MQTT_SERVER     "192.168.1.2"
#define MQTT_PORT       "1883"

void getWifiDetails();

void connect_wifi()
{
  Serial.println("Getting WIiFi details...");
  getWifiDetails();

  Serial.println("connecting wifi");
  Serial.print("ssid: ");
  Serial.println(wlan_ssid);
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(wlan_ssid, wlan_pass);

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

void getWifiDetails()
{
  if (!LittleFS.begin())
  {
    Serial.println("unable to mount LittleFS");
    return;
  }

  File f = LittleFS.open("/wifi_config.json", "r");
  StaticJsonDocument<256> doc;

  DeserializationError er = deserializeJson(doc, f);
  if (er)
  {
    Serial.println("Failed to read wifi config file");
    Serial.println(er.c_str());
    f.close();
    return;
  }

  wlan_ssid = doc["wlan_ssid"];
  wlan_pass = doc["wlan_pass"];
  
}


void setup() {
  Serial.begin(9600);
  Serial.println();

  connect_wifi();

  mqtt_controller.read_config();
  Serial.println("finished setup");
  delay(500);
}

void loop() {
  mqtt_controller.mqtt_check();
}