#include <MQTT_Controller.hpp>

#include <Arduino.h>
#include <PubSubClient.h>
#include <LittleFS.h>
#include <ArduinoJson.h>
#include <PubStruct.h>
#include <SubStruct.h>

#include "SpaceHeater.h"

MQTT_Controller::MQTT_Controller(PubSubClient client)
{
    _client = client;
    Serial.println("creating MQTT Controller");
    // read_config();
}


void MQTT_Controller::recv_message(
    char* topic,
    char* payload,
    unsigned int length
)
{
    return;
}

                                
void MQTT_Controller::read_config()
{
    if (!LittleFS.begin())
    {
        Serial.println("unable to mount LittleFS");
        return;
    }

    File f = LittleFS.open("/config.json", "r");
    StaticJsonDocument<1024> doc;

    DeserializationError er = deserializeJson(doc, f);
    if (er)
    {
        Serial.println("Failed to read json file");
        Serial.println(er.c_str());
        f.close();
        return;
    }    
    f.close();

    topicRoot = doc["topic_root"];
    clientID = doc["client_id"];
    _serverIP = doc["server_ip"];
    _serverPort = doc["server_port"];

    const JsonArray& modules = doc["modules"];
    unsigned int module_count;
    for (module_count = 0; module_count < modules.size(); module_count++)
    {
        const JsonObject& m = modules[module_count];
        const char* m_type = m["module_type"];
        const char* m_id = m["id"];

        if (!strcmp(m_type, "heater"))
        {
            SpaceHeater mod = _create_space_heater(m);
            mqtt_modules[module_count] = &mod;
        }
        else if (!strcmp(m_type, "led_light"))
        {
        }
    }
}

SpaceHeater MQTT_Controller::_create_space_heater(JsonObject dict)
{
    SpaceHeater sp(dict, &_client);

    Serial.print("number of subscriptions: ");
    Serial.println(sp._subCount);
    return sp;       
}

void MQTT_Controller::reconnect()
{
    while (!_client.connected())
    {
        String id = clientID;
        id += String(random(0xffff), HEX);
        Serial.println(clientID);
        Serial.println(id);

        if (_client.connect(id.c_str()))
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

void MQTT_Controller::mqtt_check()
{
    if (!_client.loop())
    {
        reconnect();
    }

    for (int i=0; i < MAX_MODULE_COUNT; i++)
    {
        if (mqtt_modules[i])
        {
            mqtt_modules[i]->update();
        }

    }
}



