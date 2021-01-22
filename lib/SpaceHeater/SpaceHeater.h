#ifndef SpaceHeater_h
#define SpaceHeater_h

#include <Arduino.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>


class SpaceHeater
{
public:
    SpaceHeater(JsonObject config, PubSubClient* client);

    void callback(char* topic, char* payload, unsigned int length);
    void publish_message(char* topic, char* message);

    bool setLocalMonitor(bool localMonitor);
    int setMaxTemp(int temp);
    int setMinTemp(int temp);
    int setMaxRunTime(int seconds);
    int setMinOffTime(int seconds);

    int maxTemp;
    int minTemp;
    int maxRunTime;
    int minOffTime;
    char* module_id;
    SubStruct subscriptions[20];
    char publications[20][200];
    int _subCount;
    int _pubCount;

private:
    bool localMonitor = true;
    int _controlPin;
    float historical_temps[10];

    int publish_callback;
    PubSubClient* _client;
};

#endif