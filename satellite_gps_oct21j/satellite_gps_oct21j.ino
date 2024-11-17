#include <TinyGPS++.h>
#include <SoftwareSerial.h>

TinyGPSPlus gps; // Create an instance of the TinyGPS++ library

SoftwareSerial gpsSerial(4, 3);  // RX, TX for GPS module
SoftwareSerial satSerial(7, 6);  // RX, TX for satellite modem

void setup() {
  Serial.begin(9600); // Start Serial Monitor for debugging

  gpsSerial.begin(9600); // Initialize GPS module serial communication
  Serial.println("GPS Module Started");

  satSerial.begin(9600); // Initialize satellite modem serial communication
  Serial.println("Satellite Modem Started");
}

void loop() {
  while (gpsSerial.available() > 0) { // Read GPS data
    char c = gpsSerial.read();
    if (gps.encode(c)) {
      displayGPSInfo();
    }
  }
  
  if (gps.location.isValid()) { // Send GPS data to satellite modem if valid
    String gpsData = prepareGPSData();
    sendSatelliteData(gpsData);
  }
}

String prepareGPSData() { // Prepare GPS data string
  String data = "Latitude: " + String(gps.location.lat(), 6) + 
                ", Longitude: " + String(gps.location.lng(), 6) + 
                ", Altitude: " + String(gps.altitude.meters()) + " m";
  return data;
}

void displayGPSInfo() { // Display GPS data on Serial Monitor
  Serial.println(prepareGPSData());
}

void sendSatelliteData(String data) { // Send GPS data through satellite modem
  Serial.println("Sending GPS data via satellite...");
  satSerial.println(data); // Send data to satellite modem
  delay(1000); // Wait for response or transmission to complete
}
