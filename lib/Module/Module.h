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
        void callback(char* topic, char* payload, unsigned int length);
        void build_config(JsonObject config) { Serial.println("not an implementation"); }
        static void publish_message() { Serial.println("Not an implementation");}
        virtual void update() { Serial.println("not an implementation"); }

        char id[20] = "base_module";
        const char* moduleID;
        const char* moduleType;
};


#endif