const int setButtonPin = 4;
const int ledPin = 12;
const int buzzerPin = 11;

bool reminderExists = false;
unsigned long reminderStartTime = 0;
unsigned long buzzerTimer = 0;
bool ledOn = false;
bool buzzerOn = false;

void setup() {
  pinMode(setButtonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);
  digitalWrite(buzzerPin, LOW);
}

void loop() {
  unsigned long currentMillis = millis();
  bool setPressed = (digitalRead(setButtonPin) == LOW);

  if (setPressed && !reminderExists) {
    reminderExists = true;
    reminderStartTime = currentMillis;
    buzzerTimer = currentMillis;
    ledOn = true;
    digitalWrite(ledPin, HIGH);

    Serial.println("Reminder created");
    Serial.print("Start time: ");
    Serial.println(reminderStartTime);
  }

  if (reminderExists && ledOn && (currentMillis - buzzerTimer >= 5000)) {
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