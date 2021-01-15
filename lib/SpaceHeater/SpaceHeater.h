#ifndef SpaceHeater_h
#define SpaceHeater_h

#include <Arduino.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>


class SpaceHeater
{
public:
    SpaceHeater(JsonObject config);

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

private:
    bool localMonitor = true;
    int _controlPin;
};

#endif