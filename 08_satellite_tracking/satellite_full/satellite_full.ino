#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>

TinyGPSPlus gps; // Create instance for TinyGPS++
SoftwareSerial gpsSerial(4, 3);  // RX, TX for GPS module
SoftwareSerial gsmSerial(7, 6);  // RX, TX for GSM module (SIM800L)

LiquidCrystal_I2C lcd(0x27, 2, POSITIVE); // 0x3F or 0x20

void setup() {
  Serial.begin(9600); // Initialize Serial Monitor

  gpsSerial.begin(9600); // Initialize GPS Serial communication
  Serial.println("GPS Module Started");

  gsmSerial.begin(9600); // Initialize GSM Serial communication
  Serial.println("GSM Module Started");

  lcd.begin(16, 2, LCD_5x8DOTS);
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Waiting for GPS");

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
    sendGSM(gpsData); // Send GPS data via GSM
  }
}

String prepareGPSData() { // Prepare GPS data for displaying and sending
  String data = "Lat: " + String(gps.location.lat(), 6) + 
                ", Lon: " + String(gps.location.lng(), 6);
  return data;
}

void displayGPSInfo() { // Display GPS data on LCD
  if (gps.location.isValid()) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Lat: ");
    lcd.print(gps.location.lat(), 6);
    lcd.setCursor(0, 1);
    lcd.print("Lon: ");
    lcd.print(gps.location.lng(), 6);
    delay(2000);
  } else {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Waiting for GPS");
  }
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
