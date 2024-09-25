#include <ESP32Servo.h>

Servo myServo;

const int servoPin = 13;

void setup() {
  myServo.attach(servoPin);
  Serial.begin(9600);
  Serial.println("Servo motor control using ESP32");
}

void loop() {
  myServo.write(0);
  Serial.println("Servo at 0 degrees");
  delay(1000);

  myServo.write(90);
  Serial.println("Servo at 90 degrees");
  delay(1000);

  myServo.write(180);
  Serial.println("Servo at 180 degrees");
  delay(1000);
}
