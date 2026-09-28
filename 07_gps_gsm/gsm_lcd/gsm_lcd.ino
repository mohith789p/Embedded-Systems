#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>

SoftwareSerial gsmSerial(7, 8); // RX, TX for GSM module
LiquidCrystal_I2C lcd(0x27, 2, POSITIVE); // Initialize the LCD

void setup() {
  Serial.begin(9600); // Start Serial Monitor
  gsmSerial.begin(9600); // Start GSM serial communication
  
  lcd.begin(16, 2, LCD_5x8DOTS); // Initialize the LCD
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("GSM Ready...");

  gsmSerial.println("AT"); // Check GSM module
  delay(1000);
  readGSMResponse();
}

void loop() {
  if (gsmSerial.available()) { // Check for incoming SMS
    String sms = readSMS();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("SMS Received:");
    lcd.setCursor(0, 1);
    lcd.print(sms);
    delay(2000); // Show SMS for 2 seconds
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

String readSMS() {
  String smsContent = "";
  gsmSerial.println("AT+CMGL=\"ALL\""); // Read all SMS
  delay(1000);
  
  while (gsmSerial.available()) {
    smsContent += (char)gsmSerial.read();
  }
  
  return smsContent; // Return SMS content
}

void readGSMResponse() {
  while (gsmSerial.available()) {
    Serial.write(gsmSerial.read()); // Print GSM response
  }
}
