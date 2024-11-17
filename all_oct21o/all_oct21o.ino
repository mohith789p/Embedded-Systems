#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>

LiquidCrystal_I2C lcd(0x27, 2, POSITIVE); // 0x3F or 0x20
SoftwareSerial gsmSerial(10, 11);   // RX=10, TX=11 for GSM
SoftwareSerial satelliteSerial(8, 9); // RX=8, TX=9 for Satellite
TinyGPSPlus gps;                     // GPS object
SoftwareSerial gpsSerial(4, 3);     // RX=4, TX=3 for GPS

void setup() {
  Serial.begin(9600);               // Start Serial Monitor for debugging
  gsmSerial.begin(9600);              // Start GSM communication
  satelliteSerial.begin(9600);        // Start Satellite communication
  gpsSerial.begin(9600);              // Start GPS communication

  lcd.begin(16, 2, LCD_5x8DOTS);
  lcd.backlight();                    // Turn on the LCD backlight
  lcd.setCursor(0, 0);
  lcd.print("Initializing...");

  delay(2000);                        // Wait for modules to be ready
}

void loop() {
  while (gpsSerial.available() > 0) { // Check for GPS data
    char gpsData = gpsSerial.read();
    if (gps.encode(gpsData)) {
      displayGPSInfo();               // Display GPS info if available
    }
  }
  
  delay(2000);                       // Delay before next loop iteration
}

// Function to display GPS info and send it via GSM and Satellite
void displayGPSInfo() {
  if (gps.location.isValid()) {
    String latitude = String(gps.location.lat(), 6);
    String longitude = String(gps.location.lng(), 6);
    String gpsData = "Lat: " + latitude + " Lon: " + longitude;

    lcd.clear();                     // Clear the LCD
    lcd.setCursor(0, 0);
    lcd.print("GPS Location:");
    lcd.setCursor(0, 1);
    lcd.print("Lat: " + latitude);
    lcd.setCursor(0, 2);
    lcd.print("Lon: " + longitude);

    sendDataViaGSM(gpsData);        // Send GPS data via GSM
    sendDataViaSatellite(gpsData);   // Send GPS data via Satellite
    
    Serial.println("GPS Data: " + gpsData); // Debug output
  } else {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Waiting for GPS");
    Serial.println("Waiting for GPS signal...");
  }
}

// Function to send GPS data via GSM
void sendDataViaGSM(String message) {
  gsmSerial.println("AT+CMGF=1");    // Set SMS mode to text
  delay(100);
  gsmSerial.println("AT+CMGS=\"+1234567890\""); // Replace with actual phone number
  delay(100);
  gsmSerial.println(message);          // The message to send
  delay(100);
  gsmSerial.write(26);                // Send Ctrl+Z to send SMS
  delay(1000);
  Serial.println("SMS Sent: " + message); // Debug output
}

// Function to send GPS data via Satellite
void sendDataViaSatellite(String message) {
  satelliteSerial.println(message);    // Send the message over the satellite link
  Serial.println("Data Sent to Satellite: " + message); // Debug output
}
