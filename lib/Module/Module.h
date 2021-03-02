#ifndef Module_h
#define Module_h

#include <Arduino.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

#include <SubStruct.h>
#include <PubStruct.h>


class Module
{
    public:
        // Module(JsonObject config, PubSubClient* client);
        // Module();

        void callback(char* topic, char* payload, unsigned int length);
        void build_config(JsonObject config) { Serial.println("not an implementation"); }
        static void publish_message() { Serial.println("Not an implementation");}
        void update() { Serial.println("not an implementation"); }

    private:
};


#endif