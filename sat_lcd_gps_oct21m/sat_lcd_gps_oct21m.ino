#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <TinyGPS++.h>

TinyGPSPlus gps; // Create an instance of TinyGPS++

const int satelliteTX = 7; // Define the pin for Satellite TX
const int satelliteRX = 6; // Define the pin for Satellite RX

LiquidCrystal_I2C lcd(0x27, 2, POSITIVE); // 0x3F or 0x20

void setup() {
  Serial.begin(9600); // Initialize the Serial Monitor
  Serial1.begin(9600); // Initialize the GPS module Serial connection
  Serial2.begin(9600); // Initialize Satellite communication Serial
  
  lcd.begin(16, 2, LCD_5x8DOTS);
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Waiting for GPS");
}

void loop() {
  while (Serial1.available() > 0) { // Read data from GPS
    char c = Serial1.read();
    if (gps.encode(c)) {
      displayGPSInfo();
      sendGPSDataToSatellite();
    }
  }
}

void displayGPSInfo() { // Display GPS data on the LCD
  if (gps.location.isValid()) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Lat: ");
    lcd.print(gps.location.lat(), 6);
    lcd.setCursor(0, 1);
    lcd.print("Lon: ");
    lcd.print(gps.location.lng(), 6);
    delay(2000);
  } else {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Waiting for GPS");
  }
}

void sendGPSDataToSatellite() { // Send GPS data via the satellite module
  if (gps.location.isValid()) {
    String gpsData = "Lat: " + String(gps.location.lat(), 6) + 
                     ", Lon: " + String(gps.location.lng(), 6);
    
    Serial2.println(gpsData);  // Send data to the satellite module
    Serial.println("GPS Data Sent to Satellite: " + gpsData);
  } else {
    Serial.println("No valid GPS data to send.");
  }
}
