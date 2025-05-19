#include <Wire.h>
#include <LiquidCrystal_PCF8574.h>

// Relay pin definitions
#define RELAY1 5   // Channel 1 - Inlet Solenoid Valve
#define RELAY2 18  // Channel 2 - Drain Solenoid Valve
#define RELAY3 19  // Channel 3 - Heating Element
#define RELAY4 2  // Channel 4 - Final Process

#define BUZZER 4   // Buzzer pin

// Initialize LCD
LiquidCrystal_PCF8574 lcd(0x27);

// Function to beep the buzzer
void beep(int duration = 200) {
  digitalWrite(BUZZER, HIGH);
  delay(duration);
  digitalWrite(BUZZER, LOW);
}

void setup() {
  // Initialize Relays
  pinMode(RELAY1, OUTPUT);
  pinMode(RELAY2, OUTPUT);
  pinMode(RELAY3, OUTPUT);
  pinMode(RELAY4, OUTPUT);

  // Initialize Buzzer
  pinMode(BUZZER, OUTPUT);
  digitalWrite(BUZZER, LOW);

  digitalWrite(RELAY1, HIGH);
  digitalWrite(RELAY2, HIGH);
  digitalWrite(RELAY3, HIGH);
  digitalWrite(RELAY4, HIGH);

  // Initialize LCD
  Wire.begin();
  lcd.begin(16, 2);
  lcd.setBacklight(255);
  lcd.setCursor(1, 0);
  lcd.print("AUTOONE PROCESS");
  lcd.setCursor(5,1);
  lcd.print("START");
  beep(300);
  delay(5000);
  lcd.clear();
}

void loop() {
  // --- STEP 1: Inlet Solenoid ON ---
  beep();
  digitalWrite(RELAY1, LOW);
  lcd.setCursor(2, 0);
  lcd.print("NORMAL WATER");
  lcd.setCursor(4, 1);
  lcd.print("RELEASED");
  delay(8000);
  digitalWrite(RELAY1, HIGH);
  delay(3000);
  lcd.clear();

  // --- STEP 2: Drain + Heating ON ---
  digitalWrite(RELAY2, LOW);
  digitalWrite(RELAY3, LOW);
  lcd.setCursor(4, 0);
  lcd.print("DRAINING");
  lcd.setCursor(4, 1);
  lcd.print("HEATING");
  delay(8000);  
  digitalWrite(RELAY2, HIGH);
  lcd.setCursor(3, 0);
  lcd.print("DRAIN STOP");
  delay(2000);
  digitalWrite(RELAY3, HIGH);
  lcd.setCursor(2, 1);
  lcd.print("HEATING OFF");
   // abc
  delay(3000);
  lcd.clear();

  // --- STEP 3: Inlet again ---
  digitalWrite(RELAY1, LOW);
  lcd.setCursor(3, 0);
  lcd.print("HOT WATER");
  lcd.setCursor(4, 1);
  lcd.print("RELEASED");
  delay(8000);
  digitalWrite(RELAY1, HIGH);
  delay(3000);
  lcd.clear();

  // --- STEP 4: Drain ---
  digitalWrite(RELAY2, LOW);
  lcd.setCursor(4, 0);
  lcd.print("DRAINING");
  lcd.setCursor(0, 1);
  delay(8000);
  digitalWrite(RELAY2, HIGH);
  delay(2000);
  lcd.clear();

  // --- STEP 5: Final Process ---
  digitalWrite(RELAY4, LOW);
  lcd.setCursor(4, 0);
  lcd.print("SOLUTION");
  lcd.setCursor(4, 1);
  lcd.print("RELEASED");
  delay(8000);
  digitalWrite(RELAY4, HIGH);
  delay(2000);
  lcd.clear();

 // --- STEP 4: Drain ---
  digitalWrite(RELAY2, LOW);
  lcd.setCursor(4, 0);
  lcd.print("DRAINING");
  lcd.setCursor(0, 1);
  delay(8000);
  digitalWrite(RELAY2, HIGH);
  delay(2000);
  lcd.clear();
  
  // Final beep and stop
  lcd.setCursor(2, 0);
  lcd.print("PROCESS DONE");
  beep(500);
  delay(2000);
  lcd.clear();
}
