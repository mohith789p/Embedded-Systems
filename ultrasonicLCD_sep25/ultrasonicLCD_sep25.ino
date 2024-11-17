#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// LCD setup
LiquidCrystal_I2C lcd(0x27, 2,POSITIVE);

// Ultrasonic sensor setup
const int trigPin = 5;
const int echoPin = 18;   

long duration;             
float distance;           

void setup() {
  // Initialize Serial and LCD
  Serial.begin(9600);     
  lcd.begin(16, 2,LCD_5x8DOTS);       
  lcd.backlight();        
  lcd.setCursor(0, 0);
  lcd.print("I LOVE BUILD CLUB");
  lcd.setCursor(0, 1);
  lcd.print("VISHNU INSTITUTE");

  // Ultrasonic sensor pin modes
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT);  
}

void loop() {
  // Clear the Trigger pin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);   
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Read the duration of the echo pulse
  duration = pulseIn(echoPin, HIGH);
  
  // Calculate the distance (in cm)
  distance = duration * 0.0343 / 2; 
  
  // Print distance to Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  
  // Display distance on the LCD
  lcd.setCursor(0, 1); // Set cursor to second row
  lcd.print("Distance: ");
  lcd.print(distance);
  lcd.print(" cm  "); // Extra spaces to clear old values
  
  // Wait before next measurement
  delay(500);
}
