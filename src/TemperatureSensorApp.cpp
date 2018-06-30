#include "TemperatureSensorApp.h"
#include <stdlib_noniso.h>

TemperatureSensorApp::TemperatureSensorApp()
{
    Wire.begin(0, 2);

    if (!bmp.begin()) {
	    Serial.println("Could not find a valid BMP280 sensor, check wiring!");
        delay(2000);
    	while (1) {}
    }
}

void TemperatureSensorApp::loop()
{
    serialLog.println("PING");
    this->mqttConnection.loop();

    float tmp = bmp.readTemperature();
    serialLog.print(tmp);
    serialLog.println(" degs");
    
    char buffer[4]; 
    dtostrf(tmp, 4,2,buffer);
    const char *topic = "temperature";
    this->mqttConnection.publish(topic,buffer);

    delay(5 * 60 * 1000); 

}