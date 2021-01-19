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
    int i = 0;
    Serial.println("publications");
    while (cont)
    {
        const char* t = first_pub[i].as<char*>();
        if (!strcmp("", t))
        {
            strcpy(publications[i], t);
            Serial.println(t);
            i++;
        }
        else{ cont = false; }
    }

    const JsonArray& subs = config["subscriptions"];
    cont = true;
    i = 0;
    Serial.println("Subscriptions");
    while (cont)
    {
        const char* t = subs[i].as<char*>();
        if (!strcmp("", t))
        {
            strcpy(subscriptions[i], t);
            Serial.println(t);
            i++;
        }
        else { cont = false; }
    }
    strcpy(subscriptions[i], config["temperature_sub_topic"]);
}

void SpaceHeater::callback(char* topic, char* payload, unsigned int length)
{

}