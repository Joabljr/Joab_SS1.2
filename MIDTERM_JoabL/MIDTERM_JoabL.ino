const int potPin     = 4;  
const int buttonPin  = 14;  
const int pwmLedPin  = 18;   
const int buzzerPin  = 10;  
const int ledPin     = 8;    

int potValue = 0;
int buttonState = 0;
int ledBrightness = 0;
unsigned long prevMillis = 0;
const long interval = 1000;
int potHistory[5];

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

  // Store scaled values in array
  for (int i = 0; i < 5; i++) {
    potHistory[i] = potValue / (i + 1);
  }

  // Map ADC to 8-bit PWM range
  ledBrightness = map(potValue, 0, 4095, 0, 255);

  // Button + brightness condition
  if (buttonState == LOW && ledBrightness > 128) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }

  // PWM outputs using analogWrite()
  analogWrite(pwmLedPin, ledBrightness);
  analogWrite(buzzerPin, ledBrightness / 2);

  // Timed serial output
  unsigned long currentMillis = millis();
  if (currentMillis - prevMillis >= interval) {
    prevMillis = currentMillis;
    Serial.print("Pot history: ");
    for (int i = 0; i < 5; i++) {
      Serial.print(potHistory[i]);
      Serial.print(" ");
    }
    Serial.println();
  }
}