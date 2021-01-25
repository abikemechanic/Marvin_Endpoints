#include <SpaceHeater.h>

#include <Arduino.h>
#include <ArduinoJson.h>
#include <PubSubClient.h>

#include <PubStruct.h>
#include <SubStruct.h>

SpaceHeater::SpaceHeater(JsonObject config, PubSubClient* client)
{
    Serial.println("creating heater object");
    _controlPin = config["controlPin"];
    maxTemp = config["maxTemp"];
    minTemp = config["minTemp"];
    maxRunTime = config["maxRunTime"];
    minOffTime = config["minRunTime"];
    moduleID = config["id"];
    
    _client = client;

    const JsonArray& first_pub = config["publish"];
    for (_pubCount = 0; _pubCount < first_pub.size(); _pubCount++)
    {
        const char* t = first_pub[_pubCount].as<char*>();
        strcpy(publications[_pubCount], t);
    }

    const JsonArray& subs = config["subscribe"];
    for (_subCount = 0; _subCount < subs.size(); _subCount++)
    {
        const char* t = subs[_subCount].as<char*>();
        SubStruct s;
        s.topic = t;
        s.subModule = moduleID;
        subscriptions[_subCount] = s;
    }

    SubStruct s;
    s.topic = config["temperature_sub_topic"];
    s.subModule = moduleID;
    subscriptions[_subCount+1] = s;
}

void SpaceHeater::check_module()
{
    if (millis() > _lastUpdateTime)
    {
        publish_message("t", "s");
        // t and s not important now
    }
}


void SpaceHeater::callback(char* topic, char* payload, unsigned int length)
{

}

void SpaceHeater::publish_message(char* topic, char* message)
{
    _client->publish("test_topic", "from space heater module");    
}

void SpaceHeater::publish_message()
{
    Serial.println("pointer func in SpaceHeater");
}