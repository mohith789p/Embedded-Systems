#include <SoftwareSerial.h>

SoftwareSerial satSerial(4, 3); // RX, TX for satellite modem
SoftwareSerial gsmSerial(7, 6); // RX, TX for GSM module (SIM800L)

void setup() {
  Serial.begin(115200); // Start Serial Monitor for debugging
  
  satSerial.begin(9600);
  Serial.println("Satellite Modem Started");

  gsmSerial.begin(9600);
  Serial.println("GSM Module Started");
  
  gsmSerial.println("AT"); // Optionally send an AT command to check GSM module
  delay(1000);
}

void loop() {
  if (satSerial.available()) { // Check for data from satellite modem
    String satData = satSerial.readStringUntil('\n');
    Serial.println("Satellite Data: " + satData);

    sendSMS(satData); // Send satellite data via SMS
  }

  if (gsmSerial.available()) { // Check for data from GSM module
    String gsmData = gsmSerial.readStringUntil('\n');
    Serial.println("GSM Data: " + gsmData);
  }
}

void sendSMS(String message) {
  gsmSerial.println("AT+CMGF=1");  // Set SMS text mode
  delay(1000);
  
  gsmSerial.println("AT+CMGS=\"+1234567890\"");
  delay(1000);
  
  gsmSerial.println(message);  // Message to send
  delay(1000);
  
  gsmSerial.write(26);  // Ctrl+Z to send the message
  delay(5000);
}
