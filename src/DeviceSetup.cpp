#include "DeviceSetup.h"
#include <WiFiManager.h> 
#include <Arduino.h>

//gets called when WiFiManager enters configuration mode
void configModeCallback (WiFiManager *myWiFiManager) {
  Serial.println("Entered config mode");
  Serial.println(WiFi.softAPIP());
  //if you used auto generated SSID, print it
  Serial.println(myWiFiManager->getConfigPortalSSID());
}


//flag for saving data
bool shouldSaveConfig = false;

//callback notifying us of the need to save config
void saveConfigCallback () {
  Serial.println("Should save config");
  shouldSaveConfig = true;
}

DeviceSetup::DeviceSetup(EEPROMSettings & settings, Log & log)
{

log.println("Constructing wifi");
  
  if(! settings.configured()) {

  log.println("WiFi.disconnect()` due to  settings.configured()");
  
    WiFi.disconnect();
    delay(1000);
  }

    const char *hostname = settings.thingHostname();

  WiFiManager wifiManager;
  //set callback that gets called when connecting to previous WiFi fails, and enters Access Point mode
  wifiManager.setAPCallback(configModeCallback);

  //timeout - this will quit WiFiManager if it's not configured in 3 minutes, causing a restart
  wifiManager.setConfigPortalTimeout(180);


  WiFiManagerParameter custom_sonoff_hostname_text("<br/>Thing Hostname");
  wifiManager.addParameter(&custom_sonoff_hostname_text);
  WiFiManagerParameter custom_sonoff_hostname("sonoff-hostname", "thingHostname", settings.thingHostname(), 10);
  wifiManager.addParameter(&custom_sonoff_hostname);

  WiFiManagerParameter custom_mqtt_text("<br/>MQTT hostname and port");
  wifiManager.addParameter(&custom_mqtt_text);
  WiFiManagerParameter custom_mqtt_hostname("mqtt-hostname", "Hostname", settings.mqttServer(), 33);
  wifiManager.addParameter(&custom_mqtt_hostname);
  WiFiManagerParameter custom_mqtt_port("mqtt-port", "port", settings.mqttPort(), 6);
  wifiManager.addParameter(&custom_mqtt_port);


  //set config save notify callback
  wifiManager.setSaveConfigCallback(saveConfigCallback);


log.println("Wifi about to connect");

  if (!wifiManager.autoConnect(hostname)) {
    log.println("failed to connect and hit timeout");
    //reset and try again, or maybe put it to deep sleep
    ESP.reset();
    delay(1000);
  }

  //Serial.println(custom_blynk_token.getValue());
  //save the custom parameters to FS
  if (shouldSaveConfig) {
    log.println("Saving config");
    WMSettings newSettings;
    strcpy(newSettings.mqttServer, custom_mqtt_hostname.getValue());
    strcpy(newSettings.mqttPort, custom_mqtt_port.getValue());
    strcpy(newSettings.thingHostname, custom_sonoff_hostname.getValue());
    
    settings.save(newSettings);
    
    ESP.restart();
  }

  log.println("Constructed wifi");
}


