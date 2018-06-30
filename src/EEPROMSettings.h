#pragma once
#define EEPROM_SALT 250579

typedef struct {
  char  mqttServer[33]  = "192.168.10.2";
  char  mqttPort[6]       = "1883";
  char  thingHostname[10] = "esp01";
  bool  configured        = false;
  int   salt              = EEPROM_SALT;
} WMSettings;


class EEPROMSettings
{
  public:
    EEPROMSettings();
    void save(WMSettings);
    WMSettings load();
    void debugDump();
    
    char* mqttServer();
    char*  mqttPort();
    int mqttPortNumber();
    char* thingHostname();
    bool configured();
  private:
      WMSettings settings;
};


