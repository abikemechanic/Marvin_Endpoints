#include <SpaceHeater.h>

#include <Arduino.h>
#include <ArduinoJson.h>
#include <PubSubClient.h>

SpaceHeater::SpaceHeater(JsonObject config, PubSubClient client)
{
    _controlPin = config["controlPin"];
    maxTemp = config["maxTemp"];
    minTemp = config["minTemp"];
    maxRunTime = config["maxRunTime"];
    minOffTime = config["minRunTime"];
    
    _client = client;

    // subscriptions
    // publishes
}

void SpaceHeater::callback(char* topic, char* payload, unsigned int length)
{

}