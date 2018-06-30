#pragma once
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "PublishChannel.h"

class MQTTConnection : public PublishChannel
{
  public:
    MQTTConnection(char* mqttHostname, int mqttPort, char * thingHostname);
    void connectToMQTT();
    void loop();
    void publish(const char * topic, const char * payload);
    
  private:
    char* mqttHostname;
    int  mqttPort;
    char * mqttClientID;
    WiFiClient wificlient;
    PubSubClient mqttClient{wificlient};
};

