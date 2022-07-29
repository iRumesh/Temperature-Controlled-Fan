#include "Arduino.h"
#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal.h>

#define ONE_WIRE_BUS 7 //Temperature Sensor Connected to digital pin 7 of Arduino
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

int fan = 3;        // FAN pin connected to arduino PWM 3 pin
float temp;
int tempMin = 25;   // Minimum Temperature to start the FAN
int tempMax = 100;  // Maximum Temperature to rotate FAN at full speed
int fanSpeed;       
int fanP;           // Fan Speed Percentage

void setup() 
{
  pinMode(fan, OUTPUT);
  Serial.begin(9600); 
  sensors.begin();
}
 
void loop() 
{
  sensors.requestTemperatures();
  temp = sensors.getTempCByIndex(0);     // Read Temperature from Sensor

   if(temp  < tempMin) {                 // If temp is lower than minimum temperature
        fanSpeed = 0;                    // FAN speed = 0 when temperature lower than reference temperature 
        digitalWrite(fan, LOW);
   } 
   if((temp  >= tempMin) && (temp <= tempMax)) { // if temperature is higher than minimum temp 
          fanSpeed = map(temp, tempMin, tempMax, 20, 255); // the actual speed of fan
          fanSpeed = 2*fanSpeed; // 2 is a calibration parameter, can be adjusted  get a observable FAN speed
          fanP = map(temp, tempMin, tempMax, 0, 100); // speed of fan to display on LCD 
          analogWrite(fan, fanSpeed); // spin the fan at the fanSpeed speed 
   }
   Serial.print("Current Temperature: ");
   Serial.print(temp);
   Serial.print("°C  ");
   Serial.print("fan Speed(%): ");
   Serial.print(fanP);
   Serial.println(" %  ");
}
 
