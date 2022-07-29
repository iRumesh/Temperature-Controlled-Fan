#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 7 // Sensor Data Pin connected to Digital Pin 7 in Arduino
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

float Celsius = 0;
float Fahrenheit = 0;

void setup() {
  Serial.begin(9600);
  sensors.begin();
}

void loop() {
  sensors.requestTemperatures();
  Celsius = sensors.getTempCByIndex(0); // To get temperature in Celsius
  Fahrenheit = sensors.toFahrenheit(Celsius); // To get temperature in Fahrenheit
  Serial.print("Temperature: ");
  Serial.print(Celsius);
  Serial.print("°C  ");
  Serial.print(Fahrenheit);
  Serial.println(" F");
  delay(1000); 
}
