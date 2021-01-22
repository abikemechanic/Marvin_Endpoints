#ifndef MQTT_Controller_h
#define MQTT_Controller_h

#include <Arduino.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

#include <PubStruct.h>
#include <SubStruct.h>
#include "SpaceHeater.h"


class MQTT_Controller
{
public:
    MQTT_Controller(PubSubClient client);
    void recv_message(char* topic, char* payload, unsigned int length);
    void read_config();
    void publish_message(PubStruct message_data);

    bool config_success = false;

private:
    PubSubClient _client;
    SubStruct _subs[];
    int _subCount = 0;

    SpaceHeater _create_space_heater(JsonObject dict);
};

#endif