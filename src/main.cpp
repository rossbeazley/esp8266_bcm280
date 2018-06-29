#include <Arduino.h>
#include <Wire.h>

#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>

Adafruit_BMP280 bmp; 

void setup() {
    // put your setup code here, to run once:
    //pinMode(2, OUTPUT);
     Serial.begin(9600);
    // Wire.pins(0, 2);
     Wire.begin(0, 2);

    if (!bmp.begin()) {
	    Serial.println("Could not find a valid BMP280 sensor, check wiring!");
        delay(2000);
    	while (1) {}
    }
}

void loop() {
    // put your main code here, to run repeatedly:
    Serial.write("PING");

    //digitalWrite(2, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(400);              // wait for a second

    Serial.print("Temperature = ");
    Serial.print(bmp.readTemperature());
    Serial.println(" *C");
    
    Serial.print("Pressure = ");
    Serial.print(bmp.readPressure());
    Serial.println(" Pa");
    
    // Calculate altitude assuming 'standard' barometric
    // pressure of 1013.25 millibar = 101325 Pascal
    Serial.print("Altitude = ");
    Serial.print(bmp.readAltitude());
    Serial.println(" meters");


  //digitalWrite(2, LOW);    // turn the LED off by making the voltage LOW
  delay(1000); 
}