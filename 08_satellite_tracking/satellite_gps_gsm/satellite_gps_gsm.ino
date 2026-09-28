#include <TinyGPS++.h>
#include <SoftwareSerial.h>

TinyGPSPlus gps; // Create instances of TinyGPS++

SoftwareSerial gpsSerial(4, 3);  // RX, TX for GPS module
SoftwareSerial gsmSerial(7, 6);  // RX, TX for GSM module (SIM800L)
SoftwareSerial satSerial(9, 8);  // RX, TX for Satellite modem (Globalstar STX3)

void setup() {
  Serial.begin(9600); // Start Serial Monitor for debugging

  gpsSerial.begin(9600); // Initialize GPS module serial communication
  Serial.println("GPS Module Started");

  gsmSerial.begin(9600); // Initialize GSM module serial communication
  Serial.println("GSM Module Started");

  satSerial.begin(9600); // Initialize Satellite modem serial communication
  Serial.println("Satellite Modem Started");

  gsmSerial.println("AT"); // Optional: Check GSM module communication
  delay(1000); // Wait for response
}

void loop() {
  while (gpsSerial.available() > 0) { // Read GPS data
    char c = gpsSerial.read();
    if (gps.encode(c)) {
      displayGPSInfo();
    }
  }

  if (gps.location.isValid()) { // If valid GPS data is available
    String gpsData = prepareGPSData();

    sendGSM(gpsData); // Optionally, send GPS data via GSM first
    sendSatellite(gpsData); // Then send via satellite
  }
}

String prepareGPSData() { // Prepare GPS data for sending
  String data = "Latitude: " + String(gps.location.lat(), 6) + 
                ", Longitude: " + String(gps.location.lng(), 6) + 
                ", Altitude: " + String(gps.altitude.meters()) + " m";
  return data;
}

void displayGPSInfo() { // Display GPS data on Serial Monitor
  Serial.println(prepareGPSData());
}

void sendGSM(String data) { // Send GPS data via GSM (e.g., SMS)
  Serial.println("Sending GPS data via GSM...");
  gsmSerial.println("AT+CMGF=1");  // Set SMS text mode
  delay(1000);

  gsmSerial.println("AT+CMGS=\"+1234567890\"");  // Replace with recipient's number
  delay(1000);
  
  gsmSerial.println(data);  // Send the GPS data as SMS
  delay(1000);
  
  gsmSerial.write(26);  // Send Ctrl+Z to terminate the message
  delay(5000);  // Wait for SMS to send
}

void sendSatellite(String data) { // Send GPS data via Satellite modem
  Serial.println("Sending GPS data via Satellite...");
  satSerial.println(data);  // Send data to the satellite modem
  delay(1000);  // Wait for response or transmission to complete
}
