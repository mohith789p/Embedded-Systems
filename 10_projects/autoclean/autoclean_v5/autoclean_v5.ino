#include <Wire.h>
#include <LiquidCrystal_PCF8574.h>

// Component control pins
#define INLET_VALVE_PIN     2
#define DRAIN_VALVE_PIN     4
#define HEATING_ELEMENT_PIN 5
#define SOLUTION_VALVE_PIN  18
#define VACUUM_VALVE_PIN    23
#define BUZZER              15

LiquidCrystal_PCF8574 lcd(0x27);

void beep(int duration = 200) {
  digitalWrite(BUZZER, HIGH);
  delay(duration);
  digitalWrite(BUZZER, LOW);
}

void setup() {
  // Output pin setup
  pinMode(INLET_VALVE_PIN, OUTPUT);
  pinMode(DRAIN_VALVE_PIN, OUTPUT);
  pinMode(HEATING_ELEMENT_PIN, OUTPUT);
  pinMode(SOLUTION_VALVE_PIN, OUTPUT);
  pinMode(VACUUM_VALVE_PIN, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  // Set default states (active-low relays: HIGH = OFF)
  digitalWrite(BUZZER, LOW);
  digitalWrite(INLET_VALVE_PIN, HIGH);
  digitalWrite(DRAIN_VALVE_PIN, HIGH);
  digitalWrite(HEATING_ELEMENT_PIN, HIGH);
  digitalWrite(SOLUTION_VALVE_PIN, HIGH);
  digitalWrite(VACUUM_VALVE_PIN, HIGH);

  // Initialize LCD
  Wire.begin();
  lcd.begin(16, 2);
  lcd.setBacklight(255);

  lcd.setCursor(2, 0);
  lcd.print("AUTO CLEANX");
  lcd.setCursor(5, 1);
  lcd.print("START");
  beep(300);
  delay(3000);
  lcd.clear();
}

void loop() {
  // --- Phase 1: Normal Water Release ---
  digitalWrite(INLET_VALVE_PIN, LOW);
  lcd.setCursor(2, 0);
  lcd.print("NORMAL WATER");
  lcd.setCursor(4, 1);
  lcd.print("RELEASED");
  delay(8000);
  digitalWrite(INLET_VALVE_PIN, HIGH);
  delay(3000);
  lcd.clear();

  // --- Phase 2: Drain & Heat ---
  digitalWrite(DRAIN_VALVE_PIN, LOW);
  digitalWrite(HEATING_ELEMENT_PIN, LOW);
  lcd.setCursor(4, 0);
  lcd.print("DRAINING");
  lcd.setCursor(4, 1);
  lcd.print("HEATING");
  delay(8000);
  digitalWrite(DRAIN_VALVE_PIN, HIGH);
  lcd.setCursor(3, 0);
  lcd.print("DRAIN STOP");
  delay(2000);
  digitalWrite(HEATING_ELEMENT_PIN, HIGH);
  lcd.setCursor(2, 1);
  lcd.print("HEATING OFF");
  delay(3000);
  lcd.clear();

  // --- Phase 3: Hot Water Release ---
  digitalWrite(INLET_VALVE_PIN, LOW);
  lcd.setCursor(3, 0);
  lcd.print("HOT WATER");
  lcd.setCursor(4, 1);
  lcd.print("RELEASED");
  delay(8000);
  digitalWrite(INLET_VALVE_PIN, HIGH);
  delay(3000);
  lcd.clear();

  // --- Phase 4: Drain ---
  digitalWrite(DRAIN_VALVE_PIN, LOW);
  lcd.setCursor(4, 0);
  lcd.print("DRAINING");
  delay(8000);
  digitalWrite(DRAIN_VALVE_PIN, HIGH);
  delay(2000);
  lcd.clear();

  // --- Phase 5: Solution Release ---
  digitalWrite(SOLUTION_VALVE_PIN, LOW);
  lcd.setCursor(4, 0);
  lcd.print("SOLUTION");
  lcd.setCursor(4, 1);
  lcd.print("RELEASED");
  delay(8000);
  digitalWrite(SOLUTION_VALVE_PIN, HIGH);
  delay(2000);
  lcd.clear();

  // --- Phase 6: Drain & Heat ---
  digitalWrite(DRAIN_VALVE_PIN, LOW);
  digitalWrite(HEATING_ELEMENT_PIN, LOW);
  lcd.setCursor(4, 0);
  lcd.print("HEATING");
  lcd.setCursor(4, 1);
  lcd.print("DRAINING");
  delay(8000);
  digitalWrite(DRAIN_VALVE_PIN, HIGH);
  digitalWrite(HEATING_ELEMENT_PIN, HIGH);
  lcd.clear();

  // --- Phase 7: Vacuum ---
  digitalWrite(VACUUM_VALVE_PIN, LOW);
  lcd.setCursor(4, 0);
  lcd.print("VACUUM ON");
  delay(8000);
  digitalWrite(VACUUM_VALVE_PIN, HIGH);
  lcd.clear();

  // --- Phase 8: Final Drain ---
  digitalWrite(DRAIN_VALVE_PIN, LOW);
  lcd.setCursor(4, 0);
  lcd.print("DRAINING");
  delay(8000);
  digitalWrite(DRAIN_VALVE_PIN, HIGH);
  delay(2000);
  lcd.clear();

  // --- Process Done ---
  lcd.setCursor(2, 0);  
  lcd.print("PROCESS DONE");
  beep(500);
  delay(2000);
  lcd.clear();

  delay(2000);
}
