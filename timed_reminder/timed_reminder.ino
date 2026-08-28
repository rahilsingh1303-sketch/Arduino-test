const int setButtonPin = 4;
const int ledPin = 12;
const int buzzerPin = 11;

bool reminderExists = false;
unsigned long reminderStartTime = 0;
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
    ledOn = true;
    digitalWrite(ledPin, HIGH);
    Serial.println("Reminder Created");
  }

  if (reminderExists && ledOn && (currentMillis - reminderStartTime >= 5000)) {
    buzzerOn = true;
    Serial.println("REMINDER!");
    digitalWrite(buzzerPin, HIGH);
    reminderStartTime = currentMillis; 
    
  }

  if (buzzerOn && ledOn && (currentMillis - reminderStartTime >= 300)) {
    buzzerOn = false;
    digitalWrite(buzzerPin, LOW);
    ledOn = false;
    digitalWrite(ledPin, LOW);
    reminderExists = false;
  }

 
 
}
