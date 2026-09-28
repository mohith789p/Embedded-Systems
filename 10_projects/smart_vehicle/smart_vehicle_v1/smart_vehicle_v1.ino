#include <SoftwareSerial.h>       // For serial communication with GSM
#include <TinyGPS++.h>            // GPS Library for NEO-6M
#include <LiquidCrystal_I2C.h>    // For LCD display
#include <DHT.h>                  // For DHT sensor

// Pin Assignments
int mq3Pin = A0;       // Alcohol Sensor
int relayPin = 7;      // Relay to control engine lock
int buzzerPin = 8;     // Optional Buzzer for alert
int ignitionKeyPin = 6;// Ignition Key Pin (simulating the key ON/OFF state)
float alcoholThreshold = 300; // Threshold value for alcohol detection

// GSM and GPS Pins
SoftwareSerial gsmSerial(9, 10); // RX, TX for GSM
SoftwareSerial gpsSerial(4, 3);  // RX, TX for GPS
TinyGPSPlus gps; // Create GPS object

// LCD object (assuming the address is 0x27 for a 16x2 LCD)
LiquidCrystal_I2C lcd(0x27, 16, 2);

// DHT sensor
#define DHTTYPE DHT11  // or DHT22, depending on the sensor used
const int DHTPin = 2; // DHT sensor pin (changed to D2)
DHT dht(DHTPin, DHTTYPE);

void setup() {
  pinMode(mq3Pin, INPUT);
  pinMode(relayPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(ignitionKeyPin, INPUT_PULLUP); // Ignition key switch with internal pull-up

  Serial.begin(9600); // For monitoring
  gpsSerial.begin(9600); // Start GPS
  gsmSerial.begin(9600); // Start GSM

  lcd.begin(A4,A5 ); // Initialize LCD with correct dimensions
  lcd.backlight(); // Turn on backlight
  lcd.clear();

  dht.begin(); // Initialize the DHT sensor

  digitalWrite(relayPin, HIGH); // Engine ON by default
  digitalWrite(buzzerPin, LOW); // Buzzer OFF by default

  lcd.setCursor(0, 0);
  lcd.print("System Init");
  lcd.setCursor(0, 1);
  lcd.print("Awaiting Key");

  // Initialize GSM Module (SIM900/800)
  sendSMS("System Initialized!");
}

void loop() {
  if (gpsSerial.available() > 0) {
    gps.encode(gpsSerial.read()); // Get GPS Data
  }

  int alcoholValue = analogRead(mq3Pin); // Read alcohol sensor data
  bool ignitionKeyStatus = digitalRead(ignitionKeyPin) == LOW; // Check if ignition key is ON (LOW because of pull-up)

  // DHT sensor readings
  float tempC = dht.readTemperature(); // Temperature in Celsius
  float humidity = dht.readHumidity(); // Humidity

  // Check if DHT sensor readings are valid
  if (isnan(tempC) || isnan(humidity)) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("DHT Error!");
    delay(2000); // Display error message for a while
    return;
  }

  // Display alcohol sensor, ignition key, temperature, and humidity
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Alc: ");
  lcd.print(alcoholValue);
  lcd.setCursor(8, 0);
  lcd.print("T: ");
  lcd.print(tempC);
  lcd.setCursor(0, 1);
  lcd.print("H: ");
  lcd.print(humidity);
  lcd.print("%");

  if (ignitionKeyStatus) {
    lcd.setCursor(8, 1);
    lcd.print("Key: ON");

    if (alcoholValue > alcoholThreshold) {
      lockEngine(); // Lock the engine when alcohol is detected
      sendSMS("Alcohol detected! Engine locked.");
      triggerBuzzer();
      displayLocation();
    } else {
      unlockEngine(); // Keep the engine running when alcohol is not detected
    }
  } else {
    lockEngine(); // Engine off if key is not turned on
    lcd.setCursor(8, 1);
    lcd.print("Key: OFF");
  }

  delay(2000); // Delay between sensor readings
}

void lockEngine() {
  digitalWrite(relayPin, LOW); // Turn off engine
  lcd.setCursor(0, 1);
  lcd.print("Engine: Locked");
}

void unlockEngine() {
  digitalWrite(relayPin, HIGH); // Turn on engine
  lcd.setCursor(0, 1);
  lcd.print("Engine: ON");
}

void triggerBuzzer() {
  digitalWrite(buzzerPin, HIGH); // Turn on buzzer
  delay(1000);
  digitalWrite(buzzerPin, LOW);  // Turn off buzzer
}

void sendSMS(String message) {
  gsmSerial.println("AT+CMGF=1"); // Set SMS mode
  delay(500); // Increased delay for GSM response
  gsmSerial.println("AT+CMGS=\"+1234567890\""); // Replace with recipient's phone number
  delay(500); // Increased delay for GSM response
  gsmSerial.print(message);
  delay(500); // Wait for message input
  gsmSerial.write(26); // ASCII code for Ctrl+Z
  delay(5000); // Wait for SMS sending process
}

void displayLocation() {
  if (gps.location.isValid()) {
    Serial.print("Lat: ");
    Serial.println(gps.location.lat(), 6);
    Serial.print("Lon: ");
    Serial.println(gps.location.lng(), 6);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Lat: ");
    lcd.setCursor(5, 0);
    lcd.print(gps.location.lat(), 6);
    lcd.setCursor(0, 1);
    lcd.print("Lon: ");
    lcd.setCursor(5, 1);
    lcd.print(gps.location.lng(), 6);

    sendSMS("Location: " + String(gps.location.lat(), 6) + ", " + String(gps.location.lng(), 6));
  } else {
    Serial.println("Location not available");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Loc not available");
  }
}
