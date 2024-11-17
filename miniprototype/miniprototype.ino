#include <TinyGPS++.h>
#include <TinyGsmClient.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Define the modem model
#define MODEM_A7 // Change this to your specific modem model

// Pin definitions
#define BUTTON_PIN 12  // Push button pin
#define BUZZER_PIN 14  // Buzzer pin

// LCD and communication setup
LiquidCrystal_I2C lcd(0x27, 16, 2); // Adjust address if needed
TinyGPSPlus gps;
TinyGsm modem(Serial1); // Assuming GSM module is on Serial1
HardwareSerial SerialGPS(1); // GPS on Serial2

// GSM variables
const char apn[] = ""; // Your network's APN
const char user[] = "";
const char pass[] = "";
const char sms_number[] = "+91XXXXXXXXXX"; // Phone number to send SMS

bool alertSent = false;

void setup() {
  Serial.begin(115200);
  SerialGPS.begin(9600, SERIAL_8N1, 16, 17); // RX, TX for GPS
  Serial1.begin(9600); // RX, TX for GSM

  // Initialize components
  lcd.begin();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("System Starting");

  pinMode(BUTTON_PIN, INPUT_PULLUP); // Button setup
  pinMode(BUZZER_PIN, OUTPUT);

  // Wait for GSM modem to initialize
  lcd.setCursor(0, 1);
  lcd.print("Connecting GSM");
  modem.restart();

  // Connect to network
  if (modem.gprsConnect(apn, user, pass)) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("GSM Connected");
  } else {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("GSM Connection");
    lcd.setCursor(0, 1);
    lcd.print("Failed");
    while (true); // Stop further execution
  }

  lcd.setCursor(0, 0);
  lcd.print("Ready for Alert");
}

void loop() {
  // Read GPS data
  while (SerialGPS.available() > 0) {
    gps.encode(SerialGPS.read());
  }

  // Check for button press
  if (digitalRead(BUTTON_PIN) == LOW) {
    if (!alertSent) {
      sendAlert();
      alertSent = true;
      digitalWrite(BUZZER_PIN, HIGH); // Sound the buzzer
      delay(5000); // Alarm duration
      digitalWrite(BUZZER_PIN, LOW);
    }
  } else {
    alertSent = false; // Reset alert state when button is released
  }

  // Display GPS status on LCD
  lcd.setCursor(0, 0);
  if (gps.location.isValid()) {
    lcd.print("Lat:");
    lcd.print(gps.location.lat(), 6);
    lcd.setCursor(0, 1);
    lcd.print("Lng:");
    lcd.print(gps.location.lng(), 6);
  } else {
    lcd.print("No GPS signal");
    lcd.setCursor(0, 1);
    lcd.print("                "); // Clear previous line
  }

  delay(1000);
}

void sendAlert() {
  if (gps.location.isValid()) {
    String message = "Emergency! Location: ";
    message += "Lat: " + String(gps.location.lat(), 6) + ", ";
    message += "Lng: " + String(gps.location.lng(), 6);

    // Send SMS
    modem.sendSMS(sms_number, message.c_str());

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Alert Sent!");
    lcd.setCursor(0, 1);
    lcd.print("SMS Delivered");
  } else {
    lcd.setCursor(0, 0);
    lcd.print("No GPS location");
  }
}
