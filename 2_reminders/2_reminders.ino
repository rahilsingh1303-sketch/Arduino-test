const int setButtonPin = 4;
const int setButton2Pin = 5;
const int ledPin = 12;
const int buzzerPin = 11;

bool reminderExists = false;
unsigned long reminderStartTime = 0;
unsigned long reminderDuration = 0;
unsigned long buzzerTimer = 0;
unsigned long lastPrintTime = 0;
bool ledOn = false;
bool buzzerOn = false;

void setup() {
  pinMode(setButtonPin, INPUT_PULLUP);
  pinMode(setButton2Pin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);
  digitalWrite(buzzerPin, LOW);
}

void loop() {
  unsigned long currentMillis = millis();
  bool setPressed = (digitalRead(setButtonPin) == LOW);
  bool set2Pressed = (digitalRead(setButton2Pin) == LOW);

  if (setPressed && !reminderExists) {
    reminderExists = true;
    reminderStartTime = currentMillis;
    reminderDuration = 5000;
    buzzerTimer = currentMillis;
    lastPrintTime = currentMillis;
    ledOn = true;
    digitalWrite(ledPin, HIGH);

    Serial.println("5-second reminder created");
    Serial.print("Start time: ");
    Serial.println(reminderStartTime);
    Serial.println();
  }

  if (set2Pressed && !reminderExists) {
    reminderExists = true;
    reminderStartTime = currentMillis;
    reminderDuration = 10000;
    buzzerTimer = currentMillis;
    lastPrintTime = currentMillis;
    ledOn = true;
    digitalWrite(ledPin, HIGH);

    Serial.println("10-second reminder created");
    Serial.print("Start time: ");
    Serial.println(reminderStartTime);
    Serial.println();
  }

  if (reminderExists && (currentMillis - lastPrintTime >= 1000)) {
    lastPrintTime = currentMillis;
    unsigned long timePassed = currentMillis - reminderStartTime;
    Serial.print("Time passed: ");
    Serial.println(timePassed);
  }

  if (reminderExists && ledOn && (currentMillis - buzzerTimer >= reminderDuration)) {
    buzzerOn = true;
    Serial.println("REMINDER!");
    digitalWrite(buzzerPin, HIGH);
    buzzerTimer = currentMillis;
  }

  if (buzzerOn && ledOn && (currentMillis - buzzerTimer >= 300)) {
    buzzerOn = false;
    digitalWrite(buzzerPin, LOW);
    ledOn = false;
    digitalWrite(ledPin, LOW);
    reminderExists = false;
  }
}