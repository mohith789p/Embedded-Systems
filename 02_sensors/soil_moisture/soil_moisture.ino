// Define the GPIO pin where the soil sensor is connected
const int soilPin = 34; // GPIO 34 (Analog pin)

void setup() {
  // Initialize Serial Monitor
  Serial.begin(9600);
  // Configure the analog pin as input
  pinMode(soilPin, INPUT);
}

void loop() {
  // Read the analog value from the soil moisture sensor
  int soilValue = analogRead(soilPin);
  
  // Map the analog reading to a percentage (0-100%)
  int moisturePercent = map(soilValue, 4095, 0, 0, 100);

  // Print the sensor value and percentage
  Serial.print("Soil Moisture Value: ");
  Serial.print(soilValue);
  Serial.print(" | Moisture Percentage: ");
  Serial.print(moisturePercent);
  Serial.println("%");
  
  // Delay for 1 second before taking the next reading
  delay(1000);
}
