#include <Arduino.h>
#include <Wire.h>
#include "TemperatureSensorApp.h"
#include <ESP8266WiFi.h>

TemperatureSensorApp * app = nullptr;

void setup() {
    // put your setup code here, to run once:
    //pinMode(2, OUTPUT);
     Serial.begin(9600);
    // Wire.pins(0, 2);

    app = new TemperatureSensorApp{};
}

void loop() {
    // put your main code here, to run repeatedly:
    app->loop();
    //ESP.deepSleep(2e6);
    
}