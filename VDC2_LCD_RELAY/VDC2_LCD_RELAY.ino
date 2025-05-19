#include <Wire.h>
#include <LiquidCrystal_PCF8574.h>

// Relay pin definitions
#define RELAY1 5   // Channel 1 - Inlet Solenoid Valve
#define RELAY2 18  // Channel 2 - Drain Solenoid Valve
#define RELAY3 19  // Channel 3 - Heating Element
#define RELAY4 21  // Channel 4 - Final Process

// Initialize LCD
LiquidCrystal_PCF8574 lcd(0x27);

void setup() {
  // Initialize Relays
  pinMode(RELAY1, OUTPUT);
  pinMode(RELAY2, OUTPUT);
  pinMode(RELAY3, OUTPUT);
  pinMode(RELAY4, OUTPUT);

  digitalWrite(RELAY1, HIGH);
  digitalWrite(RELAY2, HIGH);
  digitalWrite(RELAY3, HIGH);
  digitalWrite(RELAY4, HIGH);

  // Initialize LCD
  Wire.begin(12,13);
  lcd.begin(16, 2);
  lcd.setBacklight(255);
  lcd.setCursor(0, 0);
  lcd.print("System Init...");
  delay(2000);
  lcd.clear();
}

void loop() {
  // --- STEP 1: Inlet Solenoid ON ---
  digitalWrite(RELAY1, LOW);
  lcd.setCursor(0, 0);
  lcd.print("Normal Water");
  lcd.setCursor(0, 1);
  lcd.print("Released      ");
  delay(8000);

  digitalWrite(RELAY1, HIGH);
  lcd.setCursor(0, 1);
  lcd.print("Released Stop ");
  delay(2000);
  lcd.clear();

  // --- STEP 2: Drain + Heating ON ---
  digitalWrite(RELAY2, LOW);
  digitalWrite(RELAY3, LOW);
  lcd.setCursor(0, 0);
  lcd.print("Draining...");
  lcd.setCursor(0, 1);
  lcd.print("Heating...");
  delay(8000);  

  digitalWrite(RELAY2, HIGH);
  lcd.setCursor(0, 0);
  lcd.print("Drain Stop    ");
  lcd.setCursor(0, 1);
  lcd.print("Heating...    ");
  delay(500); 

  digitalWrite(RELAY3, HIGH);
  lcd.setCursor(0, 1);
  lcd.print("Heating OFF   ");
  delay(2000);
  lcd.clear();

  // --- STEP 3: Inlet again ---
  digitalWrite(RELAY1, LOW);
  lcd.setCursor(0, 0);
  lcd.print("Hot Water");
  lcd.setCursor(0, 1);
  lcd.print("Released      ");
  delay(8000);

  digitalWrite(RELAY1, HIGH);
  lcd.setCursor(0, 1);
  lcd.print("Released Stop ");
  delay(2000);
  lcd.clear();

 // --- STEP 4: Inlet again ---
  digitalWrite(RELAY2, LOW);
  lcd.setCursor(0, 0);
  lcd.print("Draining...");
  lcd.setCursor(0, 1);
  lcd.print("Released      ");
  delay(8000);

  digitalWrite(RELAY2, HIGH);
  lcd.setCursor(0, 1);
  lcd.print("Drain Stop ");
  delay(2000);
  lcd.clear();

  // --- STEP 5: Final Process ---
  digitalWrite(RELAY4, LOW);
  lcd.setCursor(0, 0);
  lcd.print("Solution");
  lcd.setCursor(0, 1);
  lcd.print("Released      ");
  delay(8000);

  digitalWrite(RELAY4, HIGH);
  lcd.setCursor(0, 1);
  lcd.print("Released Stop ");
  delay(2000);
  lcd.clear();

  // End loop
  while (true);
}
