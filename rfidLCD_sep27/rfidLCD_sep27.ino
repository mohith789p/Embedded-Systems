#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>


#define SS_PIN 21
#define RST_PIN 22

MFRC522 rfid(SS_PIN, RST_PIN);

LiquidCrystal_I2C lcd(0x27, 2, POSITIVE);

void setup() {
  
  Serial.begin(9600);
  
  
 
  SPI.begin();
  rfid.PCD_Init();
  Serial.println("Scan an RFID card or tag");
  Serial.println("Bluetooth device is ready to pair");

  
  Wire.begin();
  lcd.begin(16, 2,  LCD_5x8DOTS); 
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("FROM");
  lcd.setCursor(0, 1);
  lcd.print("VISHNU INSTITUTE");

  
  delay(2000);
  lcd.clear();
}

void loop() {
  
  if (!rfid.PICC_IsNewCardPresent()) {
    return;
  }

  
  if (!rfid.PICC_ReadCardSerial()) {
    return;
  }

 
  Serial.print("Card UID: ");
  String uidStr = "";
  for (byte i = 0; i < rfid.uid.size; i++) {
    Serial.print(rfid.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(rfid.uid.uidByte[i], HEX);
    uidStr += String(rfid.uid.uidByte[i], HEX);
  }
  Serial.println();


  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Card UID:");
  lcd.setCursor(0, 1);
  lcd.print(uidStr);

 
  rfid.PICC_HaltA();

  delay(3000); 
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Scan another card");
}
