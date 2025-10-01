// pin definitions
const int ledPinA     = 4;
const int ledPinB     = 5;
const int ledPinC     = 17;
const int ledPinD     = 18;
const int buttonPin   = 8;     // your pushbutton

// state variables
int  currentLED      = 0;      // 0=A,1=B,2=C,3=D,4=All Off
int  lastButtonState = HIGH;   // for edge detection
int  currentButtonState;

void setup() {
  Serial.begin(115200);

  // configure LEDs as outputs, start them all OFF
  pinMode(ledPinA, OUTPUT);
  pinMode(ledPinB, OUTPUT);
  pinMode(ledPinC, OUTPUT);
  pinMode(ledPinD, OUTPUT);
  digitalWrite(ledPinA, LOW);
  digitalWrite(ledPinB, LOW);
  digitalWrite(ledPinC, LOW);
  digitalWrite(ledPinD, LOW);

  // configure button with internal pull-up
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
  // 1) Read the button
  currentButtonState = digitalRead(buttonPin);

  // 2) Detect falling edge
  if (lastButtonState == HIGH && currentButtonState == LOW) {
    delay(50);  // debounce
    if (digitalRead(buttonPin) == LOW) {
      // increment state
      currentLED = currentLED + 1;

      // wrap without using %
      if (currentLED > 4) {
        currentLED = 0;
      }

      // debug print
      Serial.print("State: ");
      if (currentLED < 4) Serial.println(currentLED);
      else                Serial.println("All Off");
    }
  }
  lastButtonState = currentButtonState;

  // 3) Turn all LEDs OFF
  digitalWrite(ledPinA, LOW);
  digitalWrite(ledPinB, LOW);
  digitalWrite(ledPinC, LOW);
  digitalWrite(ledPinD, LOW);

  // 4) Light only the selected LED (or none if currentLED==4)
  if      (currentLED == 0) digitalWrite(ledPinA, HIGH);
  else if (currentLED == 1) digitalWrite(ledPinB, HIGH);
  else if (currentLED == 2) digitalWrite(ledPinC, HIGH);
  else if (currentLED == 3) digitalWrite(ledPinD, HIGH);
  // else currentLED==4 → leave them all off
}