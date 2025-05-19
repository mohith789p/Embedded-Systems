#define RELAY1 5   // Channel 1 - Inlet Solenoid Valve
#define RELAY2 18  // Channel 2 - Drain Solenoid Valve
#define RELAY3 19  // Channel 3 - Heating Element
#define RELAY4 21  // Channel 4 - Final Process (e.g., Cooling or another step)

void setup() {
  pinMode(RELAY1, OUTPUT);
  pinMode(RELAY2, OUTPUT);
  pinMode(RELAY3, OUTPUT);
  pinMode(RELAY4, OUTPUT);

  // All relays off initially
  digitalWrite(RELAY1, HIGH);
  digitalWrite(RELAY2, HIGH);
  digitalWrite(RELAY3, HIGH);
  digitalWrite(RELAY4, HIGH);
}

void loop() {
  // STEP 1: Inlet Solenoid ON - Channel 1
  digitalWrite(RELAY1, LOW);
  delay(8000);
  digitalWrite(RELAY1, HIGH);
  delay(2000);

  // STEP 2: Drain Solenoid ON - Channel 2
  digitalWrite(RELAY2, LOW);
  digitalWrite(RELAY3, LOW);   // Parallel: Heating Element ON - Channel 3
  delay(8000); 
  digitalWrite(RELAY2, HIGH); 
  digitalWrite(RELAY3, HIGH);
  delay(2000);

  // STEP 3: Inlet Solenoid ON again - Channel 1
  digitalWrite(RELAY1, LOW);
  delay(8000);
  digitalWrite(RELAY1, HIGH);
  delay(2000);
  
   // STEP 4: Drain Solenoid ON - Channel 2
 digitalWrite(RELAY2, LOW);
  delay(8000);
  digitalWrite(RELAY2, HIGH);
  delay(2000);
  
  // STEP 5: Final Process - Channel 4
  digitalWrite(RELAY4, LOW);
  delay(8000);
  digitalWrite(RELAY4, HIGH);
  delay(2000);
}
