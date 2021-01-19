#include <SpaceHeater.h>

#include <Arduino.h>
#include <ArduinoJson.h>
#include <PubSubClient.h>

SpaceHeater::SpaceHeater(JsonObject config, PubSubClient client)
{
    Serial.println("creating heater object");
    _controlPin = config["controlPin"];
    maxTemp = config["maxTemp"];
    minTemp = config["minTemp"];
    maxRunTime = config["maxRunTime"];
    minOffTime = config["minRunTime"];

    Serial.print("control pin: ");
    Serial.println(_controlPin);
    // works
    
    // _client = client;
    // throws error...

    const JsonArray& first_pub = config["publish"];
    // char pub_topics[][200];
    // Serial.println(first_pub[0].as<char*>());
    // works

    for (int i = 0; i < 5; i++)
    {
        Serial.print("i = ");
        Serial.println(i);
        // const JsonObject& t = first_pub[i];
        // if (t.success()) {}
        const char* top = first_pub[i].as<char*>();
        // pub_topics[i] = top;
        Serial.println(top);
    }


    // subscriptions
    // publishes
}

void SpaceHeater::callback(char* topic, char* payload, unsigned int length)
{

}