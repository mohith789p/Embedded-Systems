#include <SoftwareSerial.h>       // For serial communication with GSM
#include <TinyGPS++.h>            // GPS Library for NEO-6M
#include <LiquidCrystal_I2C.h>    // For LCD display

// Set up SoftwareSerial for GPS module
SoftwareSerial gpsSerial(4, 3); // RX, TX pins for GPS
TinyGPSPlus gps;                  // Create a TinyGPSPlus object

// Set up SoftwareSerial for GSM module
SoftwareSerial gsmSerial(7, 8); // RX, TX pins for GSM
const char* phoneNumber = "+1234567890"; // Replace with your phone number

// Set up the LCD display (address, columns, rows)
LiquidCrystal_I2C lcd(0x27, 16, 2); 

void setup() {
  Serial.begin(9600);            // Start serial communication for debugging
  gpsSerial.begin(9600);         // Start GPS serial communication
  gsmSerial.begin(9600);         // Start GSM serial communication
  lcd.begin(16, 2, LCD_5x8DOTS); // Initialize the LCD
  lcd.backlight();               // Turn on backlight

  // Initialize GSM module
  sendSMS("GPS Tracker Activated");
}

void loop() {
  while (gpsSerial.available() > 0) {
    if (gps.encode(gpsSerial.read())) {
      displayGPSData();
    }
  }
}

// Function to display GPS data on the LCD
void displayGPSData() {
  if (gps.location.isUpdated()) {
    lcd.clear(); // Clear the LCD
    lcd.setCursor(0, 0); // Set cursor to first line
    lcd.print("Lat: "); 
    lcd.print(gps.location.lat(), 6); // Display latitude
    lcd.setCursor(0, 1); // Set cursor to second line
    lcd.print("Lng: "); 
    lcd.print(gps.location.lng(), 6); // Display longitude
    
    // Send alert message with GPS coordinates
    String message = "Alert! Lat: " + String(gps.location.lat(), 6) + ", Lng: " + String(gps.location.lng(), 6);
    sendSMS(message.c_str());
  }
}

// Function to send SMS
void sendSMS(const char* message) {
  gsmSerial.println("AT"); // Check if the module is responding
  delay(100);
  gsmSerial.println("AT+CMGF=1"); // Set SMS mode to text
  delay(100);
  gsmSerial.print("AT+CMGS=\""); // Start SMS command
  gsmSerial.print(phoneNumber);
  gsmSerial.println("\"");
  delay(100);
  gsmSerial.println(message); // The message
  delay(100);
  gsmSerial.write(26); // Send Ctrl+Z to indicate the end of the message
  delay(100);
}
