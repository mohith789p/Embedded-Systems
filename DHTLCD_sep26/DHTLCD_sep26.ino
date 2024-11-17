#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "DHT.h"

// Initialize the LCD with the I2C address (0x27)
LiquidCrystal_I2C lcd(0x27, 2, POSITIVE);

// Define the DHT sensor type (DHT11 or DHT22)
#define DHTTYPE DHT11  // or DHT22, depending on the sensor used

// Define the pin where the data pin of DHT is connected
const int DHTPin = 15;

// Initialize DHT sensor
DHT dht(DHTPin, DHTTYPE);

void setup() {
  // Initialize I2C communication and the LCD
  Wire.begin();
  lcd.begin(16, 2,LCD_5x8DOTS);
  lcd.backlight();
  
  // Set the initial message on the LCD
  lcd.setCursor(0, 0);
  lcd.print("Initializing...");

  // Start the serial communication for debugging
  Serial.begin(9600);
  
  // Start the DHT sensor
  dht.begin();
  
  Serial.println("DHT Sensor is initializing...");
  delay(2000);  // Allow time for initialization
}

void loop() {
  // Wait a few seconds between measurements
  delay(2000);
  
  // Read temperature in Celsius
  float tempC = dht.readTemperature();
  
  // Read humidity
  float humidity = dht.readHumidity();
  
  // Check if any reads failed and exit early (to try again)
  if (isnan(tempC) || isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor!");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Sensor Error!");
    return;
  }

  // Convert temperature to Fahrenheit (optional)
  float tempF = dht.readTemperature(true);
  
  // Print the results to the Serial Monitor
  Serial.print("Temperature: ");
  Serial.print(tempC);
  Serial.print(" °C  |  ");
  Serial.print(tempF);
  Serial.print(" °F  |  ");
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");
  
  // Display the temperature and humidity on the LCD
  lcd.clear();
  
  // Display temperature in Celsius and Fahrenheit on the first row
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(tempC);
  lcd.print(" C ");
  
  lcd.setCursor(0, 1);
  lcd.print("Hum: ");
  lcd.print(humidity);
  lcd.print(" %");
}
