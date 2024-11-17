#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 2, POSITIVE); // 0x3F or 0x20

void setup() {
  Wire.begin();
  lcd.begin(16, 2, LCD_5x8DOTS);
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("I LOVE BUILD CLUB");
  lcd.setCursor(0, 1);
  lcd.print("VISHNU INSTITUTE");
}

void loop() {
  // No actions are performed in the loop
}
