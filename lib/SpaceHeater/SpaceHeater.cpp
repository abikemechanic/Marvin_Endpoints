#include <SpaceHeater.h>

#include <Arduino.h>
#include <ArduinoJson.h>
#include <PubSubClient.h>

SpaceHeater::SpaceHeater(JsonObject config, PubSubClient client)
{
    Serial.println("creating heater object");  

    // for (JsonObject::iterator it=config.begin(); it!=config.end(); ++it)
    // {
    //     const char* m = it->key().c_str();
    //     Serial.print(m);
    //     Serial.print(": ");
    //     const char* n = config[m].as<char*>();
    //     Serial.println(n);
    // }
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

    // subscriptions
    // publishes
}

void SpaceHeater::callback(char* topic, char* payload, unsigned int length)
{

}