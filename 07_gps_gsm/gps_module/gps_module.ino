#include <TinyGPS++.h>

TinyGPSPlus gps;

const int rxPin = 4; // RX pin connected to GPS TX
const int txPin = 5; // TX pin connected to GPS RX (not used)

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial.println("GPS Serial started! Waiting for data...");
}

void loop() {
  while (Serial1.available() > 0) {
    char c = Serial1.read();
    gps.encode(c); // Feed GPS data into the TinyGPS++ parser
  }
  
  displayGPSInfo(); // Display GPS info if valid
}

void displayGPSInfo() {
  if (gps.location.isValid()) {
    String gpsData = "Latitude: " + String(gps.location.lat(), 6) +
                     ", Longitude: " + String(gps.location.lng(), 6) +
                     ", Altitude: " + String(gps.altitude.meters()) + "m";

    Serial.println(gpsData); // Print to Serial Monitor
  } else {
    Serial.println("Waiting for GPS signal...");
  } 
}
