#include <Adafruit_Fingerprint.h>
#include <Keypad.h>
#include <EEPROM.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>

// Fingerprint sensor initialization
SoftwareSerial mySerial(10, 12);
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

#define RELAY_PIN       11
#define ACCESS_DELAY    5000 

// LCD initialization
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Variables for password handling
char password[4];
char initial_password[4], new_password[4], confirm_password[4];
int i = 0;
char key_pressed = 0;

// Keypad initialization
const byte rows = 4;
const byte columns = 4;
char hexaKeys[rows][columns] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte row_pins[rows] = {2, 3, 4, 5};
byte column_pins[columns] = {6, 7, 8, 9};
Keypad keypad_key = Keypad(makeKeymap(hexaKeys), row_pins, column_pins, rows, columns);

void setup() {
  // Initialize fingerprint sensor
  finger.begin(9600);
  delay(5);
  if (!finger.verifyPassword()) {
    while (1) { delay(1); } // Stop here if fingerprint sensor is not found
  }

  // Initialize LCD
  lcd.begin(A4,A5);
  lcd.backlight();
  
  // Set relay pin as output
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, HIGH);  // Keep the relay locked initially

  // Display startup message
  lcd.print(" MOUNT DYNAMICS ");
  lcd.setCursor(0, 1);
  lcd.print("Electronic Lock ");
  delay(3000);
  lcd.clear();
  
  // Load the initial password
  lcd.print("Enter Password");
  lcd.setCursor(0, 1);
  initialPassword();
}

void loop() {
  // Check for fingerprint access
  if (getFingerPrint() != -1) {
    grantAccess();
  }

  // Check for keypad input
  key_pressed = keypad_key.getKey();
  if (key_pressed == '#') {
    changePassword();
  }
  if (key_pressed == '*') {
    resetPassword();
  }
  if (key_pressed) {
    password[i++] = key_pressed;
    lcd.print(key_pressed);
  }
  if (i == 4) {
    delay(200);
    checkPassword();
  }

  delay(50); // Add some delay before the next loop iteration
}

void grantAccess() {
  digitalWrite(RELAY_PIN, LOW);  // Unlock
  lcd.clear();
  lcd.print("Pass Accepted ");
  delay(ACCESS_DELAY);
  digitalWrite(RELAY_PIN, HIGH);  // Lock again
  lcd.clear();
  lcd.print("Enter Password:");
  lcd.setCursor(0, 1);
  i = 0;
}

void checkPassword() {
  for (int j = 0; j < 4; j++) {
    initial_password[j] = EEPROM.read(j);
  }
  
  if (!(strncmp(password, initial_password, 4))) {
    grantAccess();
  } else {
    lcd.clear();
    lcd.print("Wrong Password");
    delay(2000);
    lcd.clear();
    lcd.print("Enter Password:");
    lcd.setCursor(0, 1);
    i = 0;
  }
}

int getFingerPrint() {
  int p = finger.getImage();
  if (p != FINGERPRINT_OK) return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK) return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK) return -1;

  // Found a match
  return finger.fingerID;
}

void changePassword() {
  int j = 0;
  lcd.clear();
  lcd.print("Current Password");
  lcd.setCursor(0, 1);
  while (j < 4) {
    char key = keypad_key.getKey();
    if (key) {
      new_password[j++] = key;
      lcd.print(key);
    }
    key = 0;
  }
  delay(500);

  if (strncmp(new_password, initial_password, 4)) {
    lcd.clear();
    lcd.print("Wrong Password");
    lcd.setCursor(0, 1);
    lcd.print("Try Again");
    delay(1000);
  } else {
    j = 0;
    lcd.clear();
    lcd.print("New Password:");
    lcd.setCursor(0, 1);

    while (j < 4) {
      char key = keypad_key.getKey();
      if (key) {
        initial_password[j] = key;
        lcd.print(key);
        EEPROM.write(j, key);
        j++;
      }
    }
    lcd.clear();
    lcd.print("Pass Changed");
    delay(1000);
  }

  lcd.clear();
  lcd.print("Enter Password");
  lcd.setCursor(0, 1);
  key_pressed = 0;
}

void resetPassword() {
  lcd.clear();
  lcd.print("Reset Password");
  delay(2000);
  
  lcd.clear();
  lcd.print("Enter New Pass:");
  lcd.setCursor(0, 1);
  
  int j = 0;
  while (j < 4) {
    char key = keypad_key.getKey();
    if (key) {
      new_password[j++] = key;
      lcd.print(key);
    }
  }

  lcd.clear();
  lcd.print("Confirm Pass:");
  lcd.setCursor(0, 1);
  
  j = 0;
  while (j < 4) {
    char key = keypad_key.getKey();
    if (key) {
      confirm_password[j++] = key;
      lcd.print(key);
    }
  }

  if (!strncmp(new_password, confirm_password, 4)) {
    for (j = 0; j < 4; j++) {
      EEPROM.write(j, new_password[j]);
    }
    lcd.clear();
    lcd.print("Password Reset");
    delay(2000);
  } else {
    lcd.clear();
    lcd.print("Pass Mismatch");
    delay(2000);
  }

  lcd.clear();
  lcd.print("Enter Password:");
  lcd.setCursor(0, 1);
  i = 0;
}

void initialPassword() {
  int j;
  for (j = 0; j < 4; j++) {
    EEPROM.write(j, j + 49); // Write default password ('1', '2', '3', '4')
  }
  for (j = 0; j < 4; j++) {
    initial_password[j] = EEPROM.read(j);
  }
  lcd.clear();
  lcd.print("Enter Password:");
  lcd.setCursor(0,1);
}
