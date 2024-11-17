#include "DHT.h"

#define DHTTYPE DHT11

const int DHTPin = 15;

DHT dht(DHTPin, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
  Serial.println("DHT Sensor is initializing...");
}

void loop() {
  delay(2000);
  
  float tempC = dht.readTemperature();
  float humidity = dht.readHumidity();
  
  if (isnan(tempC) || isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  float tempF = dht.readTemperature(true);
  
  Serial.print("Temperature: ");
  Serial.print(tempC);
  Serial.print(" °C  |  ");
  Serial.print(tempF);
  Serial.print(" °F  |  ");
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");
}
