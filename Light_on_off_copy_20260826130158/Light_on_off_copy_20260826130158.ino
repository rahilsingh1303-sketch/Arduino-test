const int setButtonPin = 4;
const int checkButtonPin = 5;
const int ledPin = 12;
const int buzzerPin = 11;

bool reminderExists = false;

void setup() {
  pinMode(setButtonPin, INPUT_PULLUP);
  pinMode(checkButtonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);
  digitalWrite(buzzerPin, LOW);
}

void loop() {
  bool setPressed = (digitalRead(setButtonPin) == LOW);
  bool checkPressed = (digitalRead(checkButtonPin) == LOW);

  if (setPressed) {
    reminderExists = true;
    Serial.println("Reminder created");
    delay(300); 
  }

  if (checkPressed) {
    if (reminderExists) {
      Serial.println("Reminder!");
      digitalWrite(ledPin, HIGH); 
      digitalWrite(buzzerPin, HIGH); 
      delay(1000);                
      digitalWrite(ledPin, LOW);  
      digitalWrite(buzzerPin, LOW);  
      reminderExists = false;     
    } else {
      Serial.println("No reminder found");
      digitalWrite(ledPin, LOW);
      digitalWrite(buzzerPin, LOW);
    }
    delay(300); 
  }
}
