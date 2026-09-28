#include <SoftwareSerial.h>
#include <TinyGPS++.h>

SoftwareSerial gsmSerial(7, 8); // RX, TX for GSM module
SoftwareSerial gpsSerial(4, 3); // RX, TX for GPS module

TinyGPSPlus gps;

void setup() {
  Serial.begin(9600); // Start Serial Monitor
  gsmSerial.begin(9600);
  gpsSerial.begin(9600);

  gsmSerial.println("AT"); // Check GSM module
  delay(1000);
  readGSMResponse();
}

void loop() {
  while (gpsSerial.available() > 0) {
    char c = gpsSerial.read();
    gps.encode(c);

    if (gps.location.isUpdated()) { // If a valid location is available
      String message = "Latitude: " + String(gps.location.lat(), 6) +
                       ", Longitude: " + String(gps.location.lng(), 6) +
                       ", Altitude: " + String(gps.altitude.meters()) + "m";

      sendSMS("recipient_number", message); // Replace with the actual recipient number
    }
  }
}

void sendSMS(String number, String message) {
  gsmSerial.print("AT+CMGF=1\r"); // Set SMS to text mode
  delay(1000);
  readGSMResponse();

  gsmSerial.print("AT+CMGS=\"");
  gsmSerial.print(number);
  gsmSerial.print("\"\r");
  delay(1000);
  readGSMResponse();

  gsmSerial.print(message);
  gsmSerial.write(26); // Send Ctrl+Z to send the message
  delay(1000);
  readGSMResponse();
}

void readGSMResponse() {
  while (gsmSerial.available()) {
    Serial.write(gsmSerial.read()); // Print GSM response
  }
}
