#ifndef MQTT_Controller_h
#define MQTT_Controller_h

#include <Arduino.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

#include <PubStruct.h>
#include <SubStruct.h>
#include <Module.h>
#include "SpaceHeater.h"


class MQTT_Controller
{
public:
    MQTT_Controller(PubSubClient client);
    void recv_message(char* topic, char* payload, unsigned int length);
    void read_config();
    void reconnect();
    void callback();
    void mqtt_check();
    void publish_message(PubStruct message_data);

    bool config_success = false;

private:
    void add_update_function(void (*update_func)());

    PubSubClient _client;
    SubStruct _subs[];
    int update_callbacks[];

    int _subCount = 0;
    const char* topicRoot;
    const char* clientID;
    const char* _serverIP;
    int _serverPort;

    // array of function pointers to module update functions
    void (Module::*updates[50])();

    // array of modules
    Module *mqtt_modules[50];

    SpaceHeater _create_space_heater(JsonObject dict);
};

#endif