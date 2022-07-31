/*##########Script Information###############################
  # Purpose: Temperature Controlled DC Fan  
  # Created: 08-07-2022                                  
  # Author : Rumesh                                   
  ###########################################################*/

#include "Arduino.h"
#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 7 //Temperature Sensor Connected to 7 of Arduino
#define fan 9 // Fan connected to PWM 9 pin of Arduino 
// but can also use one of PWM 3,5,6,9,10,11 pins
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

int temp;           // Measured Temperature
int tempMin = 20;   // Minimum Temperature to start the FAN
int tempMax = 100;  // Maximum Temperature to rotate FAN at full speed
int fanSpeed;       
int fanP;           // Fan Speed Percentage

void setup() 
{
  pinMode(fan, OUTPUT); // setting fan pin as output
  Serial.begin(9600); 
  sensors.begin();
}
 
void loop() 
{ 
  sensors.requestTemperatures();
  temp = sensors.getTempCByIndex(0);     // Read Temperature from Sensor in Celsius scale

   if(temp  <= tempMin) {                 // If temp is lower than minimum temperature
        fanSpeed = 0;                    // FAN speed = 0 when temperature lower than reference temperature 
        fanP = 0;
        analogWrite(fan, 0); // digitalWrite(fan, LOW);
   }  
   
   if((temp  > tempMin) && (temp <= tempMax)) { // if temperature is higher than minimum temp 
          fanSpeed = map(temp, tempMin, tempMax, 0, 1023); // Map an digital value to 10 bits (0 to 1023)  
           //map(value, fromLow, fromHigh, toLow, toHigh) //  Arduino Uno Resolution ==> volts / 1024 units
          analogWrite(fan, fanSpeed); // spin the fan at based on temperature value
          fanP = map(temp, tempMin, tempMax, 0, 100); // speed of fan to display 
   }
   
     Serial.print("Current Temperature: ");
     Serial.print(temp);
     Serial.print("°C "); //°C
     Serial.print("| fan Speed(%): ");
     Serial.print(fanP);
     Serial.println("%  ");
     delay(200);

}
 
