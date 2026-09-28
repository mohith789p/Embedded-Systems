#include <TinyGPS++.h>
#include <HardwareSerial.h>
#include "BluetoothSerial.h"

// Create GPS and Bluetooth instances
TinyGPSPlus gps;
BluetoothSerial BTSerial;

// Initialize serial port for GPS (HardwareSerial)
HardwareSerial GPSSerial(1);

void setup() {
  // Start the Serial Monitor for debugging
  Serial.begin(115200);
  
  // Start the GPS serial connection
  GPSSerial.begin(9600, SERIAL_8N1, 16, 17); // RX=16, TX=17 for ESP32
  
  // Start Bluetooth Serial with a name for the ESP32 Bluetooth
  BTSerial.begin("ESP32_GPS");
  Serial.println("Bluetooth started! Waiting for connections...");
}

void loop() {
  // Check if there is data coming from the GPS module
  while (GPSSerial.available() > 0) {
    char c = GPSSerial.read();
    if (gps.encode(c)) { 
      displayGPSInfo();
    }
  }
}

// Function to display GPS info and send it over Bluetooth
void displayGPSInfo() {
  if (gps.location.isValid()) {
    // Prepare the data to be sent
    String gpsData = "Latitude: " + String(gps.location.lat(), 6) +
                     ", Longitude: " + String(gps.location.lng(), 6) +
                     ", Altitude: " + String(gps.altitude.meters()) + "m";

    // Print to Serial Monitor
    Serial.println(gpsData);

    // Send over Bluetooth
    BTSerial.println(gpsData);
  } else {
    Serial.println("Waiting for GPS signal...");
    BTSerial.println("Waiting for GPS signal...");
  } 
}
