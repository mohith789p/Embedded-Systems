const int analogPin = 34; 

void setup() {
  Serial.begin(9600);
    }

void loop() {
  int analogValue = analogRead(analogPin);
  float voltage = analogValue * (3.3 / 4095.0);
  Serial.print("Analog Value: ");
  Serial.print(analogValue);
  Serial.print(" | Voltage: ");
  Serial.println(voltage, 3); 
  delay(500);
}
