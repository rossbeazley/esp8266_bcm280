#include "EEPROMSettings.h"

#include <Arduino.h>
#include <EEPROM.h>

EEPROMSettings::EEPROMSettings()
{
  Serial.println("constructing EEPROMSettings");
  this->settings = this->load();
  
  Serial.println("validating EEPROMSettings");
  
  if (settings.salt != EEPROM_SALT) {
    Serial.println("Invalid settings in EEPROM, trying with defaults");
    WMSettings defaults;
    this->settings = defaults;
  }
  
  Serial.println("constructed EEPROMSettings");
}

WMSettings EEPROMSettings::load()
{
  WMSettings result;
  EEPROM.begin(512);
  EEPROM.get(0, result);
  EEPROM.end();
  return result;
}

void EEPROMSettings::save(WMSettings settings)
{
    settings.configured = true;
    EEPROM.begin(512);
    EEPROM.put(0, settings);
    EEPROM.end();
}

void EEPROMSettings::debugDump()
{  
  Serial.println(this->settings.mqttServer);
  Serial.println(this->settings.mqttPort);
  Serial.println(this->settings.thingHostname);
  Serial.println(this->settings.configured);
}

char*  EEPROMSettings::mqttServer()
{
  return this->settings.mqttServer;
}

char*  EEPROMSettings::mqttPort()
{
  return this->settings.mqttPort;
}

int EEPROMSettings::mqttPortNumber()
{
  return atoi(this->mqttPort());
}

char*  EEPROMSettings::thingHostname()
{
  return this->settings.thingHostname;
}

bool EEPROMSettings::configured()
{
  return this->settings.configured;
}


