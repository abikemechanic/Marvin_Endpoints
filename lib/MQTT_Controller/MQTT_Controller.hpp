#ifndef MQTT_Controller_h
#define MQTT_Controller_h

#include <Arduino.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

#include "SpaceHeater.h"

struct module_subscription
{
    char* topic;
    char* module_id;
};

struct module_publish
{
    char* topic;
    char* message;
};


class MQTT_Controller
{
public:
    MQTT_Controller(PubSubClient client);
    void recv_message(char* topic, char* payload, unsigned int length);
    void read_config();

    bool config_success = false;

private:
    PubSubClient _client;
    module_subscription _subs[];

    SpaceHeater _create_space_heater(JsonObject dict);
};

#endif