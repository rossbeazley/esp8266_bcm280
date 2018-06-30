#include "MQTTConnection.h"


int         lastMQTTConnectionAttempt = 0;


MQTTConnection::MQTTConnection(char* mqttHostname, int mqttPort, char * thingHostname) :
    mqttHostname{mqttHostname}
  , mqttPort{mqttPort}
  , mqttClientID{thingHostname}
{
    this->mqttClient.setServer(this->mqttHostname, this->mqttPort);
}

void MQTTConnection::loop()
{
  if (!this->mqttClient.connected()) {
     this->connectToMQTT();
  } else {
     this->mqttClient.loop();
  }
}

void MQTTConnection::connectToMQTT()
{
  //more than 3 minutes has passed
  if (lastMQTTConnectionAttempt == 0 || millis() > lastMQTTConnectionAttempt + 3 * 60 * 1000)
  {
    lastMQTTConnectionAttempt = millis();
    Serial.println(millis());
    Serial.println("Trying to connect to mqtt");
    if (this->mqttClient.connect(this->mqttClientID)) {
      Serial.println("connected");
    } else {
      Serial.println("failed");
    }
  }
  else
  {
    Serial.println("Not trying to connect to mqtt");
  }
}


void MQTTConnection::publish(const char * topic, const char * payload)
{
  Serial.print("About to publsh ");
  Serial.print(topic);
  Serial.print(" ");
  Serial.println(payload);
  if ( this->mqttClient.connected() ) {
    this->mqttClient.publish(topic, payload);
  } else {
    Serial.println("but not connected");
  }

}






