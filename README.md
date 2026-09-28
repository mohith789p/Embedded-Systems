# EMBEDDED SYSTEMS

A collection of Arduino / ESP32 sketches covering IoT fundamentals — from LED control to GPS+GSM satellite tracking and complete multi-sensor embedded systems. Each folder is a self-contained sketch that can be opened directly in the Arduino IDE.

---

## Repository Structure

```
Embedded-Systems/
├── 01_basics/               # Entry-level GPIO and ADC
│   ├── led_blink/
│   ├── led_switch/
│   ├── led_multi_blink/
│   ├── binary_counter/
│   └── adc_read/
│
├── 02_sensors/              # DHT, ultrasonic, and soil moisture
│   ├── dht_sensor/
│   ├── dht_lcd/
│   ├── ultrasonic_sensor/
│   ├── ultrasonic_lcd/
│   └── soil_moisture/
│
├── 03_displays/             # LCD and 7-segment output
│   ├── lcd_basic/
│   ├── seven_segment/
│   └── seven_segment_v2/
│
├── 04_motors/               # Motor and servo control
│   └── servo_motor/
│
├── 05_wireless/             # WiFi and Bluetooth sketches
│   ├── wifi_web_server/
│   └── bluetooth_basic/
│
├── 06_rfid/                 # RFID reader (with and without LCD)
│   ├── rfid_basic/
│   └── rfid_lcd/
│
├── 07_gps_gsm/              # Standalone GPS and GSM experiments
│   ├── gps_basic/
│   ├── gps_nmea/
│   ├── gps_module/
│   ├── gsm_basic/
│   ├── gps_gsm/
│   ├── gps_lcd/
│   ├── gsm_lcd/
│   └── gsm_gps_lcd/
│
├── 08_satellite_tracking/   # Progressive build of the full satellite tracker
│   ├── satellite_basic/
│   ├── satellite_lcd/
│   ├── satellite_gsm/
│   ├── satellite_gps/
│   ├── satellite_gps_gsm/
│   ├── satellite_full/
│   ├── satellite_lcd_gps/
│   ├── satellite_lcd_gsm/
│   └── satellite_all/
│
├── 09_smart_home/           # Alexa / SinricPro relay control
│   └── sinricpro_alexa/
│
├── 10_projects/             # Complete embedded applications (versioned)
│   ├── autoclean/           # Automated multi-stage cleaning system
│   │   ├── autoclean_v1/    # Relays only
│   │   ├── autoclean_v2/    # LCD simulation only
│   │   ├── autoclean_v3/    # Relays + LCD
│   │   ├── autoclean_v4/    # Relays + LCD + Buzzer (AutoOne)
│   │   └── autoclean_v5/    # 5 Valves + Vacuum + Buzzer + LCD (Auto CleanX)
│   │
│   ├── doorlock/            # Electronic biometric & passcode door lock
│   │   ├── doorlock_v1/     # Keypad + EEPROM
│   │   ├── doorlock_v2/     # Keypad + EEPROM (extended splash delay)
│   │   ├── doorlock_v3/     # Keypad + EEPROM + Fingerprint sensor
│   │   ├── doorlock_v4/     # Keypad + EEPROM + Fingerprint (pins 2, 3)
│   │   ├── doorlock_v5/     # Keypad + Fingerprint + PIN reset & change
│   │   ├── doorlock_v6/     # Mount Dynamics full release
│   │   └── doorlock_v7/     # Mount Dynamics revision
│   │
│   ├── gps_tracker/         # GPS + GSM location tracker & emergency alert
│   │   ├── gps_tracker_v1/  # Live GPS location to LCD + SMS alert
│   │   └── gps_tracker_v2/  # SOS button + Buzzer alarm + GPS SMS dispatch
│   │
│   ├── smart_vehicle/       # Smart vehicle safety system
│   │   └── smart_vehicle_v1/# MQ-3 alcohol detect + ignition key + engine lock + GPS SMS + DHT11
│   │
│   └── rfid_reader/         # Standalone RFID card reading
│       └── rfid_reader_v1/  # 12-character UART RFID tag reader via Serial
│
└── LIBRARIES.md             # Required libraries with exact names & Git URLs
```

---

## Technologies & Components

| Technology | Purpose |
|---|---|
| **ESP32 / Arduino** | Core microcontrollers |
| **DHT Sensors** | Temperature & humidity monitoring |
| **Ultrasonic Sensors** | Distance measurement |
| **Soil Moisture Sensor** | Agricultural / plant monitoring |
| **MQ-3 Gas Sensor** | Alcohol detection for vehicle safety |
| **LCD Displays** | Visual feedback and data display (I2C / PCF8574) |
| **7-Segment Displays** | Numeric output |
| **Servo Motor** | Mechanical control |
| **WiFi** | IoT connectivity & HTTP web server |
| **Bluetooth** | Short-range wireless communication |
| **RFID & Fingerprint** | Identification, biometric and access control |
| **Keypad (4x4)** | Passcode / PIN authentication |
| **GPS Module** | Location tracking (NEO-6M / NMEA) |
| **GSM Module (SIM800/TinyGSM)** | SMS and cellular data communication |
| **SinricPro / Alexa** | Smart home voice control |
| **Relays & Valves** | High-voltage and actuator switching |

---

## Getting Started

1. Open any sketch folder in the **Arduino IDE** — each folder is a standalone `.ino` project.
2. Install required libraries as listed in [**LIBRARIES.md**](file:///d:/workspace/Embedded-Systems/LIBRARIES.md) via the Arduino Library Manager or Git clone.
3. Select your board (**ESP32** or **Arduino**) and the correct COM port.
4. Upload and test.

---

## Progression Path

For learners, follow the numbered categories in order:

> `01_basics` → `02_sensors` → `03_displays` → `04_motors` → `05_wireless` → `06_rfid` → `07_gps_gsm` → `08_satellite_tracking` → `09_smart_home` → `10_projects`

Each stage builds directly on concepts from the previous one.
