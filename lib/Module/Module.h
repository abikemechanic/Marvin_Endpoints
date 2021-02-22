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
        Module(JsonObject config, PubSubClient* client);

        void callback(char* topic, char* payload, unsigned int length);
        void build_config(JsonObject config);
        static void publish_message();
        void update();

    private:
};


#endif