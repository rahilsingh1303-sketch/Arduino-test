const int setButtonPin = 4;
const int setButton2Pin = 5;
const int ledPin = 12;
const int buzzerPin = 11;

int reminderState = 0;

unsigned long phaseStartTime = 0;
unsigned long reminderDuration = 0;
unsigned long lastPrintTime = 0;

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


  if (setPressed && reminderState == 0) {
    reminderMessage = "Homework";
    reminderDuration = 5000;
    reminderState = 1;
    phaseStartTime = currentMillis;
    lastPrintTime = currentMillis;

    digitalWrite(ledPin, HIGH);

    Serial.println("Homework is stored");
    Serial.println("LED turned ON");
    Serial.println();
  }


  if (set2Pressed && reminderState == 0) {
    reminderMessage = "Meeting";
    reminderDuration = 10000;
    reminderState = 1;
    phaseStartTime = currentMillis;
    lastPrintTime = currentMillis;

    digitalWrite(ledPin, HIGH);

    Serial.println("Meeting is stored");
    Serial.println("LED turned ON");
    Serial.println();
  }

  
  if (reminderState != 0 && (currentMillis - lastPrintTime >= 1000)) {
    lastPrintTime = currentMillis;
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
    Serial.println();

    reminderState = 0;

    printReminderInfo();
  }
}