const int a1 = 18;
const int b1 = 19;
const int c1 = 21;
const int d1 = 22;
const int e1 = 23;
const int f1 = 25;
const int g1 = 26;

const int a2 = 5;
const int b2 = 32;
const int c2 = 33;
const int d2 = 17;
const int e2 = 14;
const int f2 = 12;
const int g2 = 13;

const int ledPin = 2;

void setup() {
  pinMode(a1, OUTPUT);
  pinMode(b1, OUTPUT);
  pinMode(c1, OUTPUT);
  pinMode(d1, OUTPUT);
  pinMode(e1, OUTPUT);
  pinMode(f1, OUTPUT);
  pinMode(g1, OUTPUT);
  
  pinMode(a2, OUTPUT);
  pinMode(b2, OUTPUT);
  pinMode(c2, OUTPUT);
  pinMode(d2, OUTPUT);
  pinMode(e2, OUTPUT);
  pinMode(f2, OUTPUT);
  pinMode(g2, OUTPUT);
  pinMode(ledPin, OUTPUT);
  
}

void displayDigit(int num) {
  // Turn off all segments
  digitalWrite(a1, HIGH);
  digitalWrite(b1, HIGH);
  digitalWrite(c1, HIGH);
  digitalWrite(d1, HIGH);
  digitalWrite(e1, HIGH);
  digitalWrite(f1, HIGH);
  digitalWrite(g1, HIGH);
  digitalWrite(ledPin, HIGH);

  // Light up segments based on the digit
  if (num == 0) {
    digitalWrite(a1, LOW);
    digitalWrite(b1, LOW);
    digitalWrite(c1, LOW);
    digitalWrite(d1, LOW);
    digitalWrite(e1, LOW);
    digitalWrite(f1, LOW);
  } else if (num == 1) {
    digitalWrite(b1, LOW);
    digitalWrite(c1, LOW);
  } else if (num == 2) {
    digitalWrite(a1, LOW);
    digitalWrite(b1, LOW);
    digitalWrite(d1, LOW);
    digitalWrite(e1, LOW);
    digitalWrite(g1, LOW);
  } else if (num == 3) {
    digitalWrite(a1, LOW);
    digitalWrite(b1, LOW);
    digitalWrite(c1, LOW);
    digitalWrite(d1, LOW);
    digitalWrite(g1, LOW);
  } else if (num == 4) {
    digitalWrite(b1, LOW);
    digitalWrite(c1, LOW);
    digitalWrite(f1, LOW);
    digitalWrite(g1, LOW);
  } else if (num == 5) {
    digitalWrite(a1, LOW);
    digitalWrite(c1, LOW);
    digitalWrite(d1, LOW);
    digitalWrite(f1, LOW);
    digitalWrite(g1, LOW);
    digitalWrite(ledPin, LOW);
  } else if (num == 6) {
    digitalWrite(a1, LOW);
    digitalWrite(c1, LOW);
    digitalWrite(d1, LOW);
    digitalWrite(e1, LOW);
    digitalWrite(f1, LOW);
    digitalWrite(g1, LOW);
  } else if (num == 7) {
    digitalWrite(a1, LOW);
    digitalWrite(b1, LOW);
    digitalWrite(c1, LOW);
  } else if (num == 8) {
    digitalWrite(a1, LOW);
    digitalWrite(b1, LOW);
    digitalWrite(c1, LOW);
    digitalWrite(d1, LOW);
    digitalWrite(e1, LOW);
    digitalWrite(f1, LOW);
    digitalWrite(g1, LOW);
  } else if (num == 9) {
    digitalWrite(a1, LOW);
    digitalWrite(b1, LOW);
    digitalWrite(c1, LOW);
    digitalWrite(d1, LOW);
    digitalWrite(f1, LOW);
    digitalWrite(g1, LOW);
  }
}

void displayDigit1(int num) {
  // Turn off all segments
   digitalWrite(a2, HIGH);
  digitalWrite(b2, HIGH);
  digitalWrite(c2, HIGH);
  digitalWrite(d2, HIGH);
  digitalWrite(e2, HIGH);
  digitalWrite(f2, HIGH);
  digitalWrite(g2, HIGH);
//  digitalWrite(ledPin, HIGH);

  // Light up segments based on the digit
  if (num == 0) {
    digitalWrite(a2, LOW);
    digitalWrite(b2, LOW);
    digitalWrite(c2, LOW);
    digitalWrite(d2, LOW);
    digitalWrite(e2, LOW);
    digitalWrite(f2, LOW);
  } else if (num == 1) {
    digitalWrite(b2, LOW);
    digitalWrite(c2, LOW);
  } else if (num == 2) {
    digitalWrite(a2, LOW);
    digitalWrite(b2, LOW);
    digitalWrite(d2, LOW);
    digitalWrite(e2, LOW);
    digitalWrite(g2, LOW);
  } else if (num == 3) {
    digitalWrite(a2, LOW);
    digitalWrite(b2, LOW);
    digitalWrite(c2, LOW);
    digitalWrite(d2, LOW);
    digitalWrite(g2, LOW);
  } else if (num == 4) {
    digitalWrite(b2, LOW);
    digitalWrite(c2, LOW);
    digitalWrite(f2, LOW);
    digitalWrite(g2, LOW);
  } else if (num == 5) {
    digitalWrite(a2, LOW);
    digitalWrite(c2, LOW);
    digitalWrite(d2, LOW);
    digitalWrite(f2, LOW);
    digitalWrite(g2, LOW);
  } else if (num == 6) {
    digitalWrite(a2, LOW);
    digitalWrite(c2, LOW);
    digitalWrite(d2, LOW);
    digitalWrite(e2, LOW);
    digitalWrite(f2, LOW);
    digitalWrite(g2, LOW);
  } else if (num == 7) {
    digitalWrite(a2, LOW);
    digitalWrite(b2, LOW);
    digitalWrite(c2, LOW);
  } else if (num == 8) {
    digitalWrite(a2, LOW);
    digitalWrite(b2, LOW);
    digitalWrite(c2, LOW);
    digitalWrite(d2, LOW);
    digitalWrite(e2, LOW);
    digitalWrite(f2, LOW);
    digitalWrite(g2, LOW);
  } else if (num == 9) {
    digitalWrite(a2, LOW);
    digitalWrite(b2, LOW);
    digitalWrite(c2, LOW);
    digitalWrite(d2, LOW);
    digitalWrite(f2, LOW);
    digitalWrite(g2, LOW);
  }
}

void loop() {
  for (int i = 0; i < 6; i++) {
    displayDigit(i);
    delay(10000);
     for (int j = 0; j < 10; j++) {
    displayDigit1(j);
     delay(1000);  
    if(i == 5 && j ==9){
      break;
    }
  }
 }
  
  
 
}
