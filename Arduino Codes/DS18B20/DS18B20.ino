#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 7 // Sensor Data Pin connected to Digital Pin 7 in Arduino
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

float Celsius = 0;
float Fahrenheit = 0;

void setup() {
  Serial.begin(9600); //Baud rate for Serial Monitor
  sensors.begin();
  //sensors.setResolution(12);   
}

void loop() {
  sensors.requestTemperatures();
  Celsius = sensors.getTempCByIndex(0);       // Using only one sensor
  Fahrenheit = sensors.toFahrenheit(Celsius); 
  if (Celsius == -127.00)
    {
      // do nothing in transient reading
    }
    else {
  Serial.print("Temperature: In Celsius Scale ");
  Serial.print(Celsius);                      // To get temperature in Celsius
  Serial.print("°C | In Fahrenheit Scale ");  //°C & F text
  Serial.print(Fahrenheit);                   // To get temperature in Fahrenheit
  Serial.println("F");
  delay(200); 
    }
}
