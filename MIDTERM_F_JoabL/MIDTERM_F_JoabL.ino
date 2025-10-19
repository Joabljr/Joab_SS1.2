const int potPin     = 4; 
const int buttonPin  = 14;
const int pwmLedPin  = 18;
const int buzzerPin  = 11;
const int ledPin     = 8;
int potValue = 0;
int buttonState = 0;
int ledBrightness = 0;
unsigned long prevMillis = 0;
const long interval = 1000;
int potHistory[5];
int toneFreq = 0;

bool toneMode = false;
bool lastButtonState = HIGH;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  pinMode(pwmLedPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  Serial.begin(115200);
}

void loop() {
  potValue = analogRead(potPin);     
  buttonState = digitalRead(buttonPin);

  
  if (lastButtonState == HIGH && buttonState == LOW) {
    toneMode = !toneMode;
    delay(50);
  }
  lastButtonState = buttonState;

  // Store scaled values in array
  for (int i = 0; i < 5; i++) {
    potHistory[i] = potValue / (i + 1);
  }

  
  ledBrightness = map(potValue, 0, 4095, 0, 255);

  
  analogWrite(pwmLedPin, ledBrightness);

  // Map pot to tone frequency based on mode
  if (toneMode) {
    toneFreq = map(potValue, 0, 4095, 1000, 3000);  // Alternate range
  } else {
    toneFreq = map(potValue, 0, 4095, 200, 1000);   // Normal range
  }

  // LED responds to toneFreq
  if (toneFreq > 1000) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }

  // Manual tone generation
  for (int i = 0; i < 50; i++) {
    digitalWrite(buzzerPin, HIGH);
    delayMicroseconds(500000 / toneFreq);
    digitalWrite(buzzerPin, LOW);
    delayMicroseconds(500000 / toneFreq);
  }

  // Timed serial output
  unsigned long currentMillis = millis();
  if (currentMillis - prevMillis >= interval) {
    prevMillis = currentMillis;
    Serial.print("Pot history: ");
    for (int i = 0; i < 5; i++) {
      Serial.print(potHistory[i]);
      Serial.print(" ");
    }
    Serial.print(" | Brightness: ");
    Serial.print(ledBrightness);
    Serial.print(" | Tone: ");
    Serial.println(toneFreq);
  }
}