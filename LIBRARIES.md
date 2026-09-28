# Required Arduino & ESP32 Libraries

To keep this repository lightweight and maintainable, library source code is not bundled directly. Instead, install the required libraries via the **Arduino IDE Library Manager** (recommended) or clone them from their official Git repositories into your Arduino `libraries/` folder.

---

## Library Reference Table

| Exact Arduino Library Name | Author / Maintainer | Git Repository URL | Usage in this Repository |
|---|---|---|---|
| **Adafruit Fingerprint Sensor Library** | Adafruit | [github.com/adafruit/Adafruit-Fingerprint-Sensor-Library](https://github.com/adafruit/Adafruit-Fingerprint-Sensor-Library) | Biometric fingerprint door lock projects (`10_projects`, `11_misc`) |
| **Adafruit Unified Sensor** | Adafruit | [github.com/adafruit/Adafruit_Sensor](https://github.com/adafruit/Adafruit_Sensor) | Base sensor abstraction layer (dependency for DHT) |
| **DHT sensor library** | Adafruit | [github.com/adafruit/DHT-sensor-library](https://github.com/adafruit/DHT-sensor-library) | DHT11 / DHT22 temperature and humidity sensing (`02_sensors`, `11_misc`) |
| **BluetoothSerial** | Henry Abrahamsen / Espressif | [github.com/hen1227/bluetooth-serial](https://github.com/hen1227/bluetooth-serial) | ESP32 Bluetooth SPP serial communication (`05_wireless`) |
| **ESP32Servo** | Kevin Harrington, John K. Bennett | [github.com/madhephaestus/ESP32Servo](https://github.com/madhephaestus/ESP32Servo) | PWM servo control on ESP32 |
| **EspSoftwareSerial** | Dirk Kaar, Peter Lerup | [github.com/plerup/espsoftwareserial](https://github.com/plerup/espsoftwareserial) | Software serial emulation on ESP8266 / ESP32 |
| **Keypad** | Mark Stanley, Alexander Brevig | [github.com/Chris--A/Keypad](https://github.com/Chris--A/Keypad) | 4×4 matrix keypad matrix scanning (`10_projects`, `11_misc`) |
| **LiquidCrystal I2C** | Frank de Brabander | [github.com/marcoschwartz/LiquidCrystal_I2C](https://github.com/marcoschwartz/LiquidCrystal_I2C) | 16×2 and 20×4 I2C LCD character displays (`02_sensors`, `07_gps_gsm`, `08_satellite_tracking`, `10_projects`) |
| **LiquidCrystal_PCF8574** | Matthias Hertel | [github.com/mathertel/LiquidCrystal_PCF8574](https://github.com/mathertel/LiquidCrystal_PCF8574) | PCF8574 I2C LCD driver for automated cleaning projects (`10_projects`) |
| **MFRC522** | GithubCommunity / Miguel Balboa | [github.com/miguelbalboa/rfid](https://github.com/miguelbalboa/rfid) | 13.56 MHz RFID RC522 card reader/writer (`06_rfid`) |
| **New-LiquidCrystal** | F Malpartida | [github.com/fmalpartida/New-LiquidCrystal](https://github.com/fmalpartida/New-LiquidCrystal) | High-speed, extensible LCD library supporting I2C, SR, and 4-bit parallel |
| **Servo** | Michael Margolis, Arduino | [github.com/arduino-libraries/Servo](https://github.com/arduino-libraries/Servo) | Standard Arduino servo motor control (`04_motors`) |
| **SinricPro** | Boris Jaeger | [github.com/sinricpro/esp8266-esp32-sdk](https://github.com/sinricpro/esp8266-esp32-sdk) | Alexa and Google Home smart relay integration (`09_smart_home`) |
| **TinyGPSPlus** | Mikal Hart | [github.com/mikalhart/TinyGPSPlus](https://github.com/mikalhart/TinyGPSPlus) | NMEA GPS parsing for NEO-6M / GPS modules (`07_gps_gsm`, `08_satellite_tracking`, `10_projects`, `11_misc`) |
| **TinyGSM** | Volodymyr Shymanskyy | [github.com/vshymanskyy/TinyGSM](https://github.com/vshymanskyy/TinyGSM) | Cellular modem driver for SIM800, SIM900, SIM7000, A7, etc. (`07_gps_gsm`, `08_satellite_tracking`, `10_projects`) |

---

## Installation Methods

### Method 1: Via Arduino IDE Library Manager (Recommended)
1. Open the Arduino IDE.
2. Go to **Sketch** &rarr; **Include Library** &rarr; **Manage Libraries...** (or press `Ctrl+Shift+I`).
3. Search for the **Exact Library Name** from the table above (e.g. `TinyGPSPlus`, `LiquidCrystal I2C`, `TinyGSM`).
4. Click **Install**.

### Method 2: Via Git Clone
Clone the repositories directly into your local Arduino libraries directory:

**Windows PowerShell:**
```powershell
Set-Location "$HOME\Documents\Arduino\libraries"

git clone https://github.com/adafruit/Adafruit-Fingerprint-Sensor-Library.git
git clone https://github.com/adafruit/Adafruit_Sensor.git
git clone https://github.com/adafruit/DHT-sensor-library.git
git clone https://github.com/madhephaestus/ESP32Servo.git
git clone https://github.com/plerup/espsoftwareserial.git
git clone https://github.com/Chris--A/Keypad.git
git clone https://github.com/marcoschwartz/LiquidCrystal_I2C.git
git clone https://github.com/mathertel/LiquidCrystal_PCF8574.git
git clone https://github.com/miguelbalboa/rfid.git
git clone https://github.com/fmalpartida/New-LiquidCrystal.git
git clone https://github.com/arduino-libraries/Servo.git
git clone https://github.com/sinricpro/esp8266-esp32-sdk.git
git clone https://github.com/mikalhart/TinyGPSPlus.git
git clone https://github.com/vshymanskyy/TinyGSM.git
```
