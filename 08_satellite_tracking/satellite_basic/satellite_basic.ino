#include <SoftwareSerial.h>
SoftwareSerial satelliteSerial(7, 8); // RX, TX

void setup() {
  // Start the Serial Monitor
  Serial.begin(9600);
  // Start the Software Serial for Satellite
  satelliteSerial.begin(9600);

  // Send an initial AT command to check the satellite module
  satelliteSerial.println("AT");
  delay(1000);
  readResponse();
}

void loop() {
  // Example code to send data via the satellite modem
  sendData("Hello from Satellite!");
  delay(10000);
}

void sendData(String message) {
  satelliteSerial.println("AT+SEND"); // Hypothetical command for sending data
  delay(1000);
  readResponse();

  satelliteSerial.println(message); // Send the actual data message
  delay(1000);
  readResponse();
}

void readResponse() {
  while (satelliteSerial.available()) {
    Serial.write(satelliteSerial.read());
  }
}
