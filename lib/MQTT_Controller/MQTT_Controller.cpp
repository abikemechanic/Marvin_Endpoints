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

    JsonObject obj = doc["modules"].as<JsonObject>();
    for (JsonObject::iterator it=obj.begin(); it!=obj.end(); ++it)
    {
        const char* mod = it->key().c_str();
        Serial.print("module: ");
        Serial.println(mod);

        if (!strcmp(mod, "heater"))
        {
            Serial.println("module is heater");
            JsonObject m = obj["heater"];
            _create_space_heater(m);
        }
        else if (!strcmp(mod, "led_light"))
        {
            Serial.println("create module for led_light");
        }
        else if(!strcmp(mod, "exhaust_fan"))
        {
            Serial.println("create module for exhaust_fan");
        }
        else if (!strcmp(mod, "circulating_fan"))
        {
            Serial.println("create module for circulating_fan");
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



