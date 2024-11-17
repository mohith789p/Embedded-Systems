const int a = 18;
const int b = 19;
const int c = 21;
const int d = 22;
const int e = 23;
const int f = 25;
const int g = 26;

void setup() {
  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(e, OUTPUT);
  pinMode(f, OUTPUT);
  pinMode(g, OUTPUT);
}

void displayDigit(int num) {
  // Turn off all segments
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);

  // Light up segments based on the digit
  if (num == 0) {
    digitalWrite(a, LOW);
    digitalWrite(b, LOW);
    digitalWrite(c, LOW);
    digitalWrite(d, LOW);
    digitalWrite(e, LOW);
    digitalWrite(f, LOW);
  } else if (num == 1) {
    digitalWrite(b, LOW);
    digitalWrite(c, LOW);
  } else if (num == 2) {
    digitalWrite(a, LOW);
    digitalWrite(b, LOW);
    digitalWrite(d, LOW);
    digitalWrite(e, LOW);
    digitalWrite(g, LOW);
  } else if (num == 3) {
    digitalWrite(a, LOW);
    digitalWrite(b, LOW);
    digitalWrite(c, LOW);
    digitalWrite(d, LOW);
    digitalWrite(g, LOW);
  } else if (num == 4) {
    digitalWrite(b, LOW);
    digitalWrite(c, LOW);
    digitalWrite(f, LOW);
    digitalWrite(g, LOW);
  } else if (num == 5) {
    digitalWrite(a, LOW);
    digitalWrite(c, LOW);
    digitalWrite(d, LOW);
    digitalWrite(f, LOW);
    digitalWrite(g, LOW);
  } else if (num == 6) {
    digitalWrite(a, LOW);
    digitalWrite(c, LOW);
    digitalWrite(d, LOW);
    digitalWrite(e, LOW);
    digitalWrite(f, LOW);
    digitalWrite(g, LOW);
  } else if (num == 7) {
    digitalWrite(a, LOW);
    digitalWrite(b, LOW);
    digitalWrite(c, LOW);
  } else if (num == 8) {
    digitalWrite(a, LOW);
    digitalWrite(b, LOW);
    digitalWrite(c, LOW);
    digitalWrite(d, LOW);
    digitalWrite(e, LOW);
    digitalWrite(f, LOW);
    digitalWrite(g, LOW);
  } else if (num == 9) {
    digitalWrite(a, LOW);
    digitalWrite(b, LOW);
    digitalWrite(c, LOW);
    digitalWrite(d, LOW);
    digitalWrite(f, LOW);
    digitalWrite(g, LOW);
  }
}

void loop() {
  for (int i = 0; i < 10; i++) {
    displayDigit(i);
    delay(1000);
  }
}
