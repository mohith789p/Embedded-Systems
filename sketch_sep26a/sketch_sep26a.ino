int count = 0;
char card_no[13]; // 12 characters + null terminator

void setup() {
    Serial.begin(9600);
    Serial.println("Scan the Card Now");
}

void loop() {
    if (Serial.available()) {
        count = 0;
        while (Serial.available() && count < 12) {
            card_no[count] = Serial.read();
            count++;
            delay(5); 
        }
        card_no[count] = '\0'; 
        Serial.println(card_no);
    }
}
