const int ledPinA   = 4;
const int ledPinB   = 5;
const int ledPinC   = 17;
const int ledPinD   = 18;
const int msDelay1   = 250;
const int msDelay2   = 500;
const int msDelay3   = 750;
const int msDelay4   = 1000;

void setup() {
  Serial.begin(115200);
  pinMode(ledPinA, OUTPUT);
  pinMode(ledPinB, OUTPUT);
  pinMode(ledPinC, OUTPUT);
  pinMode(ledPinD, OUTPUT);
}

void loop() {
  digitalWrite(ledPinA, HIGH);
  digitalWrite(ledPinB, LOW);
  delay(msDelay1);

  digitalWrite(ledPinA, LOW);
  digitalWrite(ledPinB, HIGH);
  delay(msDelay2);

  if (digitalRead(ledPinA) == HIGH) {
    digitalWrite(ledPinB, LOW);
  }

  digitalWrite(ledPinC, HIGH);
  digitalWrite(ledPinD, LOW);
  delay(msDelay3);

  digitalWrite(ledPinC, LOW);
  digitalWrite(ledPinD, HIGH);
  delay(msDelay4);

  if (digitalRead(ledPinC) == HIGH) {
    digitalWrite(ledPinD, LOW);
  }
}
