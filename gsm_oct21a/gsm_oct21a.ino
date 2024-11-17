#include <SoftwareSerial.h>

const int rxPin = 7; // RX pin for GSM module
const int txPin = 8; // TX pin for GSM module

SoftwareSerial gsmSerial(rxPin, txPin);

void setup() {
    Serial.begin(9600);
    gsmSerial.begin(9600);
    delay(1000);
    Serial.println("GSM module initialized.");
}

void loop() {
    sendSMS("Your phone number here", "Hello from Arduino!"); // Send SMS
    delay(10000);
}

void sendSMS(const char* phoneNumber, const char* message) {
    Serial.println("Sending SMS...");
    gsmSerial.println("AT");
    delay(100);
    gsmSerial.println("AT+CMGF=1"); // Set SMS to text mode
    delay(100);
    gsmSerial.print("AT+CMGS=\"");
    gsmSerial.print(phoneNumber);
    gsmSerial.println("\"");
    delay(100);
    gsmSerial.println(message);
    delay(100);
    gsmSerial.write(26); // End of message
    delay(100);
    while (gsmSerial.available()) {
        Serial.write(gsmSerial.read()); // Print response
    }
    Serial.println("SMS sent.");
}
