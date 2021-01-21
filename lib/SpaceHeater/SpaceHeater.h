#ifndef SpaceHeater_h
#define SpaceHeater_h

#include <Arduino.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>


class SpaceHeater
{
public:
    SpaceHeater(JsonObject config, PubSubClient client);

    void callback(char* topic, char* payload, unsigned int length);

    bool setLocalMonitor(bool localMonitor);
    int setMaxTemp(int temp);
    int setMinTemp(int temp);
    int setMaxRunTime(int seconds);
    int setMinOffTime(int seconds);

    int maxTemp;
    int minTemp;
    int maxRunTime;
    int minOffTime;
    char subscriptions[][200];
    char publications[][200];
    int _subCount;
    int _pubCount;

private:
    bool localMonitor = true;
    int _controlPin;
    float historical_temps[10];
    PubSubClient _client;
};

#endif