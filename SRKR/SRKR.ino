#include <Wire.h>
#include <LiquidCrystal_PCF8574.h>

#define I2C_SDA 21
#define I2C_SCL 22

#define INLET_VALVE_PIN 2
#define DRAIN_VALVE_PIN 4
#define HEATING_ELEMENT_PIN 5
#define SOLUTION_VALVE_PIN 18
#define VACUUM_VALVE_PIN 23

#define BUZZER 15
#define FLOAT_PIN 4

#define MOTOR1_PIN 16
#define MOTOR2_PIN 17

LiquidCrystal_PCF8574 lcd(0x27);

void beep(int duration = 200) {
  digitalWrite(BUZZER, HIGH);
  delay(duration);
  digitalWrite(BUZZER, LOW);
}

void setup() {
  // Initialize output pins
  pinMode(INLET_VALVE_PIN, OUTPUT);
  pinMode(DRAIN_VALVE_PIN, OUTPUT);
  pinMode(HEATING_ELEMENT_PIN, OUTPUT);
  pinMode(SOLUTION_VALVE_PIN, OUTPUT);
  pinMode(VACUUM_VALVE_PIN, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(FLOAT_PIN, INPUT_PULLUP);

  pinMode(MOTOR1_PIN, OUTPUT);
  pinMode(MOTOR2_PIN, OUTPUT);

  // Set default states (relays off: HIGH = OFF for active-low relays)
  digitalWrite(BUZZER, LOW);
  digitalWrite(INLET_VALVE_PIN, HIGH);
  digitalWrite(DRAIN_VALVE_PIN, HIGH);
  digitalWrite(HEATING_ELEMENT_PIN, HIGH);
  digitalWrite(SOLUTION_VALVE_PIN, HIGH);
  digitalWrite(VACUUM_VALVE_PIN, HIGH);
  digitalWrite(MOTOR1_PIN, HIGH);
  digitalWrite(MOTOR2_PIN, HIGH);

  // LCD setup
  Wire.begin(I2C_SDA, I2C_SCL);
  lcd.begin(16, 2);
  lcd.setBacklight(255);

  lcd.setCursor(1, 0);
  lcd.print("AutoCleanX PROCESS");
  lcd.setCursor(5, 1);
  lcd.print("START");
  beep(300);
  delay(3000);
  lcd.clear();
}

void loop() {
  // Water level check
  bool waterDetected = (digitalRead(FLOAT_PIN) == LOW);

  lcd.setCursor(0, 0);
  lcd.print("Water Level:");

  if (!waterDetected) {
    lcd.setCursor(2, 1);
    lcd.print("NOT PRESENT");
    beep(500);
    delay(2000);
    lcd.clear();
    return;
  }

  lcd.setCursor(4, 1);
  lcd.print("PRESENT");
  delay(1000);
  lcd.clear();

  // --- Phase 1: Normal Water Release ---
  digitalWrite(INLET_VALVE_PIN, LOW);
  digitalWrite(MOTOR1_PIN, LOW);
  lcd.setCursor(2, 0);
  lcd.print("NORMAL WATER");
  lcd.setCursor(4, 1);
  lcd.print("RELEASED");
  delay(8000);
  digitalWrite(INLET_VALVE_PIN, HIGH);
  digitalWrite(MOTOR1_PIN, HIGH);
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
  digitalWrite(MOTOR1_PIN, LOW);
  digitalWrite(INLET_VALVE_PIN, LOW);
  lcd.setCursor(3, 0);
  lcd.print("HOT WATER");
  lcd.setCursor(4, 1);
  lcd.print("RELEASED");
  delay(8000);
  digitalWrite(MOTOR1_PIN, HIGH);
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
  digitalWrite(MOTOR2_PIN, LOW);
  digitalWrite(SOLUTION_VALVE_PIN, LOW);
  lcd.setCursor(4, 0);
  lcd.print("SOLUTION");
  lcd.setCursor(4, 1);
  lcd.print("RELEASED");
  delay(8000);
  digitalWrite(MOTOR2_PIN, HIGH);
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
