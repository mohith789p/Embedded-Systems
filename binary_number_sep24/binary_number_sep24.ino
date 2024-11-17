void setup() {
  pinMode(2, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  Serial.begin(9600);
  Serial.println("Enter a number (1-7): ");
}

void loop() {
  if (Serial.available() > 0) {
    int number = Serial.parseInt();
    
    // Clear the input buffer
    while (Serial.available() > 0) {
      Serial.read();
    }
    
    Serial.println(number);
    
    digitalWrite(2, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);

    switch (number) {
      case 1:
        digitalWrite(5, HIGH);
        break;
      case 2:
        digitalWrite(4, HIGH);
        break;
      case 3:
        digitalWrite(5, HIGH);
        digitalWrite(4, HIGH);
        break;
      case 4:
        digitalWrite(2, HIGH);
        break;
      case 5:
        digitalWrite(2, HIGH);
        digitalWrite(5, HIGH);
        break;
      case 6:
        digitalWrite(2, HIGH);
        digitalWrite(4, HIGH);
        break;
      case 7:
        digitalWrite(2, HIGH);
        digitalWrite(4, HIGH);
        digitalWrite(5, HIGH);
        break;
      default:
        Serial.println("Invalid number! Please enter a number between 1 and 7.");
        break;
    }
  }
}
