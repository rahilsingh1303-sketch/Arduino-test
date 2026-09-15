const int setButtonPin = 4;
const int setButton2Pin = 5;
const int ledPin = 12;
const int buzzerPin = 11;

int reminderState = 0;

unsigned long phaseStartTime = 0;
unsigned long reminderDuration = 0;
unsigned long lastPrintTime = 0;

String reminderMessage = "";

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

    Serial.println("reminder for Homework");
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

    Serial.println("reminder for Meeting");
    Serial.println("LED turned ON");
    Serial.println();
  }

  if (reminderState != 0 && (currentMillis - lastPrintTime >= 1000)) {
    lastPrintTime = currentMillis;
    unsigned long timePassed = currentMillis - phaseStartTime;
    Serial.print("Time passed: ");
    Serial.println(timePassed);
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
  }
}