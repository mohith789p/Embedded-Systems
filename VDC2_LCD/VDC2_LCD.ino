#include <Wire.h>
#include <LiquidCrystal_PCF8574.h>

// Initialize the LCD with the correct I2C address (use 0x27 or 0x3F depending on your module)
LiquidCrystal_PCF8574 lcd(0x27);

void setup() {
  Wire.begin(12,13);            // Start I2C communication
  lcd.begin(16, 2);        // Initialize 16x2 LCD
  lcd.setBacklight(255);   // Turn on LCD backlight
  lcd.setCursor(0, 0);
  lcd.print("System Init...");
  delay(2000);
  lcd.clear();
}

void loop() {
  // Normal Water Released
  lcd.setCursor(0, 0);
  lcd.print("Normal Water");
  lcd.setCursor(0, 1);
  lcd.print("Released      ");
  delay(8000);

  lcd.setCursor(0, 1);
  lcd.print("Released Stop ");
  delay(2000);
  lcd.clear();

  // Draining and Heating
  lcd.setCursor(0, 0);
  lcd.print("Draining...");
  lcd.setCursor(0, 1);
  lcd.print("Heating...");
  delay(8000); // Change as needed for full duration

  lcd.setCursor(0, 0);
  lcd.print("Drain Stop    ");
  lcd.setCursor(0, 1);
  lcd.print("Heating OFF   ");
  delay(2000);
  lcd.clear();

  // Hot Water Released
  lcd.setCursor(0, 0);
  lcd.print("Hot Water");
  lcd.setCursor(0, 1);
  lcd.print("Released      ");
  delay(8000);

  lcd.setCursor(0, 1);
  lcd.print("Released Stop ");
  delay(2000);
  lcd.clear();

  // Solution Released
  lcd.setCursor(0, 0);
  lcd.print("Solution");
  lcd.setCursor(0, 1);
  lcd.print("Released      ");
  delay(8000);

  lcd.setCursor(0, 1);
  lcd.print("Released Stop ");
  delay(2000);
  lcd.clear();

  // Stop the loop
  while (true);
}
