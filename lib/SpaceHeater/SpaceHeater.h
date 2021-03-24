#ifndef SpaceHeater_h
#define SpaceHeater_h

#include <Arduino.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

#include <SubStruct.h>
#include <PubStruct.h>
#include <Module.h>


class SpaceHeater: public Module
{
public:
    SpaceHeater(JsonObject config, PubSubClient* client);

    void callback(char* topic, char* payload, unsigned int length);
    // void publish_message(char* topic, char* message);
    static void publish_message();
    void check_module();
    void update();

    bool setLocalMonitor(bool localMonitor);
    int setMaxTemp(int temp);
    int setMinTemp(int temp);
    int setMaxRunTime(int seconds);
    int setMinOffTime(int seconds);

    int maxTemp;
    int minTemp;
    int maxRunTime;
    int minOffTime;
    const char* moduleID;
    const char* moduleType;
    SubStruct subscriptions[20];
    char publications[20][200];
    unsigned int _subCount;
    unsigned int _pubCount;

    const char* module_type;
    const char* module_id;

private:
    bool localMonitor = true;
    int _controlPin;
    float historicalTemps[10];
    unsigned long _lastUpdateTime = 0;
    unsigned long _update_frequency;

    int publish_callback;
    PubSubClient* _client;
};

#endif