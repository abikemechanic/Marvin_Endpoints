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
    
    // _client = client;
    // throws error...

    const JsonArray& first_pub = config["publish"];
    bool cont = true;
    _pubCount = 0;
    Serial.println("publications");
    while (cont)
    {
        const char* t = first_pub[_pubCount].as<char*>();
        if (strcmp("", t))
        {
            strcpy(publications[_pubCount], t);
            Serial.println(t);
            _pubCount++;
            delay(1000);
        }
        else{ cont = false; }
    }

    const JsonArray& subs = config["subscribe"];
    cont = true;
    _subCount = 0;
    Serial.println("subscriptions");
    while (cont)
    {
        const char* t = subs[_subCount].as<char*>();
        if (!strcmp("", t))
        {
            strcpy(subscriptions[_subCount], t);
            Serial.println(t);
            _subCount++;
        }
        else { cont = false; }
    }
    strcpy(subscriptions[_subCount], config["temperature_sub_topic"]);

    Serial.println("ending creation of heater module");
}



void SpaceHeater::callback(char* topic, char* payload, unsigned int length)
{

}