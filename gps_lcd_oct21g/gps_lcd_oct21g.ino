#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <TinyGPS++.h>

LiquidCrystal_I2C lcd(0x27, 2, POSITIVE); // 0x3F or 0x20
TinyGPSPlus gps; // Create an instance of TinyGPSPlus

void setup() {
  Serial.begin(115200); // Start Serial Monitor for debugging
  
  lcd.begin(16, 2, LCD_5x8DOTS);
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("GPS Ready...");
}

void loop() {
  while (Serial.available() > 0) { // Read data from GPS
    char c = Serial.read();
    gps.encode(c);
    
    if (gps.location.isUpdated()) { // If a valid location is available
      displayGPSInfo();
    }
  }
}

void displayGPSInfo() {
  lcd.clear(); // Clear the LCD
  lcd.setCursor(0, 0);
  
  if (gps.location.isValid()) {
    lcd.print("Lat: ");
    lcd.print(gps.location.lat(), 6); // Display Latitude
  } else {
    lcd.print("Lat: Waiting...");
  }
  
  lcd.setCursor(0, 1); // Move to second line

  if (gps.location.isValid()) {
    lcd.print("Lng: ");
    lcd.print(gps.location.lng(), 6); // Display Longitude
  } else {
    lcd.print("Lng: Waiting...");
  }
}
