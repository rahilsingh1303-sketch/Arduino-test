const int setButtonPin = 4;
const int setButton2Pin = 5;
const int setButton3Pin = 6;
const int ledPin = 12;
const int buzzerPin = 11;

int reminderState = 0;

unsigned long phaseStartTime = 0;
unsigned long reminderDuration = 0;

String reminderMessage = "";

void printReminderInfo() {
  Serial.println("REMINDER INFORMATION");
  Serial.println();

  if (reminderState != 0) {
    Serial.println("Active: true");
    Serial.print("Message: ");
    Serial.println(reminderMessage);
    Serial.print("Start time: ");
    Serial.println(phaseStartTime);
    Serial.print("Delay: ");
    Serial.println(reminderDuration);
  } else {
    Serial.println("Active: false");
  }

  Serial.println();
}

void setup() {
  pinMode(setButtonPin, INPUT_PULLUP);
  pinMode(setButton2Pin, INPUT_PULLUP);
  pinMode(setButton3Pin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);
  digitalWrite(buzzerPin, LOW);
  digitalWrite(ledPin, LOW);
}

void loop() {
  unsigned long currentMillis = millis();
  bool setPressed = (digitalRead(setButtonPin) == LOW);
  bool set2Pressed = (digitalRead(setButton2Pin) == LOW);
  bool set3Pressed = (digitalRead(setButton3Pin) == LOW);


  if (setPressed) {
    if (reminderState != 0) {
      Serial.println("Old reminder replaced");
    }

    reminderMessage = "Homework";
    reminderDuration = 5000;
    reminderState = 1;
    phaseStartTime = currentMillis;

    digitalWrite(buzzerPin, LOW);
    digitalWrite(ledPin, HIGH);

    Serial.println("Homework is stored");
    Serial.println("LED ON");
    printReminderInfo();
  }


  if (set2Pressed) {
    if (reminderState != 0) {
      Serial.println("Old reminder replaced");
    }

    reminderMessage = "Meeting";
    reminderDuration = 10000;
    reminderState = 1;
    phaseStartTime = currentMillis;

    digitalWrite(buzzerPin, LOW);
    digitalWrite(ledPin, HIGH);

    Serial.println("Meeting is stored");
    Serial.println("LED ON");
    printReminderInfo();
  }

  if (set3Pressed) {
    if (reminderState != 0) {
      Serial.println("Old reminder replaced");
    }

    reminderMessage = "Lunch";
    reminderDuration = 7000;
    reminderState = 1;
    phaseStartTime = currentMillis;

    digitalWrite(buzzerPin, LOW);
    digitalWrite(ledPin, HIGH);

    Serial.println("Reminder created");
    Serial.print("Message: ");
    Serial.println(reminderMessage);
    Serial.print("Time: ");
    Serial.println(reminderDuration);
    printReminderInfo();
  }


  if (reminderState == 1 && (currentMillis - phaseStartTime >= reminderDuration)) {
    digitalWrite(buzzerPin, HIGH);
    Serial.println("Buzzer sounds");

    reminderState = 2;
    phaseStartTime = currentMillis;
  }

  if (reminderState == 2 && (currentMillis - phaseStartTime >= reminderDuration)) {
    digitalWrite(buzzerPin, LOW);
    digitalWrite(ledPin, LOW);

    Serial.print("reminder: ");
    Serial.println(reminderMessage);

    reminderState = 0;

    printReminderInfo();
  }
}