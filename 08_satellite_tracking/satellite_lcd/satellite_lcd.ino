#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>

SoftwareSerial satSerial(4, 3); // RX, TX for satellite modem
LiquidCrystal_I2C lcd(0x27, 2, POSITIVE); // 0x3F or 0x20

void setup() {
  Serial.begin(115200); // Start Serial Monitor for debugging
  satSerial.begin(9600); // Start satellite modem serial communication
  
  lcd.begin(16, 2, LCD_5x8DOTS);
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Satellite Ready...");
}

void loop() {
  if (satSerial.available()) { // Check for data from satellite modem
    String data = satSerial.readStringUntil('\n'); // Read data until newline
    displaySatelliteData(data);
  }
}

void displaySatelliteData(String data) {
  lcd.clear(); // Clear the LCD
  lcd.setCursor(0, 0);
  
  lcd.print("Data: ");
  lcd.print(data); // Display the satellite data
}
