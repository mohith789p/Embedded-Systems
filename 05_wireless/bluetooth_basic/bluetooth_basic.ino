#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

const int ledPin = 23;

void setup() {
  Serial.begin(9600);
  SerialBT.begin("TEAM 01");
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  Serial.println("Bluetooth device is ready to pair");
}

void loop() {
  if (SerialBT.available()) {
    String input = SerialBT.readString();
    input.trim();

    if (input == "1") {
      digitalWrite(ledPin, HIGH);
      SerialBT.println("LED is ON");
    } else if (input == "2") {
      digitalWrite(ledPin, LOW);
      SerialBT.println("LED is OFF");
    } else {
      SerialBT.println("Invalid command! Use 'ON' or 'OFF'.");
    }
  }
}
