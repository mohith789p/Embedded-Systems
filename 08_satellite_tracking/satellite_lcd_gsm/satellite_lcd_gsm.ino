#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
LiquidCrystal_I2C lcd(0x27, 2, POSITIVE); // 0x3F or 0x20
SoftwareSerial gsmSerial(10, 11);   // RX=10, TX=11 for GSM
SoftwareSerial satelliteSerial(8, 9); // RX=8, TX=9 for Satellite
void setup() {
  Serial.begin(9600);               // Start Serial Monitor
  gsmSerial.begin(9600);              // Start GSM communication
  satelliteSerial.begin(9600);        // Start Satellite communication
  lcd.begin(16, 2, LCD_5x8DOTS);
  lcd.backlight();                    // Turn on the LCD backlight
  lcd.setCursor(0, 0);
  lcd.print("Initializing...");
  delay(1000);
  sendSMS("System started");          // Send initial SMS
}
void loop() {
  String dataToSend = "Data: 1234";  // Data to send (can be replaced with actual data)
  lcd.clear();                        // Clear the LCD
  lcd.setCursor(0, 0);
  lcd.print("Sending data:");
  lcd.setCursor(0, 1);
  lcd.print(dataToSend);
  delay(2000);
  sendSMS(dataToSend);                // Send data via GSM
  sendDataToSatellite(dataToSend);    // Send data via Satellite  
  delay(5000);                        // Wait before the next loop
}

void sendSMS(String message) {
  gsmSerial.println("AT+CMGF=1");    // Set SMS mode to text
  delay(100);
  gsmSerial.println("AT+CMGS=\"+1234567890\""); // Replace with actual phone number
  delay(100);
  gsmSerial.println(message);          // Send the message
  delay(100);
  gsmSerial.write(26);                // Send Ctrl+Z to send SMS
  delay(1000);
  Serial.println("SMS Sent: " + message);
}
void sendDataToSatellite(String message) {
  satelliteSerial.println(message);    // Send data over the satellite link
  Serial.println("Data Sent to Satellite: " + message);
}
