#include <SpaceHeater.h>

#include <Arduino.h>
#include <ArduinoJson.h>

SpaceHeater::SpaceHeater(JsonObject config)
{
    _controlPin = config["controlPin"];
    maxTemp = config["maxTemp"];
    minTemp = config["minTemp"];
    maxRunTime = config["maxRunTime"];
    minOffTime = config["minRunTime"];

    // subscriptions
    // publishes
}

void SpaceHeater::callback(char* topic, char* payload, unsigned int length)
{

}