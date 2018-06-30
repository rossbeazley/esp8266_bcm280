#pragma once

#include "debug/SerialLog.h"
#include "EEPROMSettings.h"
#include "DeviceSetup.h"
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>

#include "mqtt/MQTTConnection.h"


class TemperatureSensorApp
{
    public:
        TemperatureSensorApp();
        void loop();
    private:
        SerialLog serialLog;
        EEPROMSettings eepromSettings;
        Adafruit_BMP280 bmp; 
        DeviceSetup deviceSetup{eepromSettings,serialLog};
        MQTTConnection mqttConnection{eepromSettings.mqttServer(),eepromSettings.mqttPortNumber(), eepromSettings.thingHostname()};
};