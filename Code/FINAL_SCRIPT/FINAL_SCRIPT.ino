// C++ code

//backrest
const int fsrPin1 = A2;
const int fsrPin2 = A3;
const int fsrPin3 = A0;
const int fsrPin4 = A1;
const int fsrPin5 = A4;
const int fsrPin6 = A5;

//sitting
const int fsrPin7 = 3;
const int fsrPin8 = 4;

const int ledPin2 = 12;
const int ledPin1 = 13;

const int trigPin1 = 10;
const int echoPin1 = 11;

// Motor
const int motorPin1 = 7;
const int motorPin2 = 2;
unsigned long badPostureStartTime = 0;
bool isBadPosture = false;

const unsigned long delayDuration = 1000;  // 1 second in milliseconds

long duration1;
float distance1;

const int fsrThreshold = 100;  // Adjust this based on testing
const float distanceThreshold = 10.0; // in cm

void setup() {
  Serial.begin(9600);

  pinMode(fsrPin1, INPUT);
  pinMode(fsrPin2, INPUT);
  pinMode(fsrPin3, INPUT);
  pinMode(fsrPin4, INPUT);
  pinMode(fsrPin5, INPUT);
  pinMode(fsrPin6, INPUT);
  
  pinMode(fsrPin7, INPUT);
  pinMode(fsrPin8, INPUT);

  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);

  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);

  pinMode(motorPin1, OUTPUT);
  digitalWrite(motorPin1, LOW);

  pinMode(motorPin2, OUTPUT);
  digitalWrite(motorPin2, LOW);
 
}

void loop() {
  int fsrState1 = digitalRead(fsrPin7);
  int fsrState2 = digitalRead(fsrPin8);
  
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  duration1 = pulseIn(echoPin1, HIGH);
  distance1 = duration1 * 0.034 / 2;  

  if (fsrState1 == LOW && fsrState2 == LOW) {  // Sitting
    digitalWrite(ledPin1, HIGH);

    int fsrState3 = analogRead(fsrPin1);
    int fsrState4 = analogRead(fsrPin2);
    int fsrState5 = analogRead(fsrPin3);
    int fsrState6 = analogRead(fsrPin4);
    int fsrState7 = analogRead(fsrPin5);
    int fsrState8 = analogRead(fsrPin6);

    if (fsrState3 > fsrThreshold && fsrState4 > fsrThreshold && fsrState5 > fsrThreshold && fsrState6 > fsrThreshold && fsrState7 > fsrThreshold && fsrState8 > fsrThreshold) {
      digitalWrite(ledPin2, LOW);
      digitalWrite(motorPin1, LOW);
      digitalWrite(motorPin2, LOW);
      badPostureStartTime = 0;
      isBadPosture = false;
    } 
    else if (fsrState3 < fsrThreshold && fsrState4 < fsrThreshold && fsrState5 > fsrThreshold && fsrState6 > fsrThreshold && fsrState7 > fsrThreshold && fsrState8 > fsrThreshold && distance1 < distanceThreshold) {
      digitalWrite(ledPin2, LOW);
      digitalWrite(motorPin1, LOW);
      digitalWrite(motorPin2, LOW);
      badPostureStartTime = 0;
      isBadPosture = false;
    } 
    else {
      digitalWrite(ledPin2, HIGH);

      if (!isBadPosture) {
        badPostureStartTime = millis();
        isBadPosture = true;
      } else {
        if (millis() - badPostureStartTime >= delayDuration) {
          if ((millis() / 1000) % 2 == 0) {
            digitalWrite(motorPin1, HIGH);
            digitalWrite(motorPin2, HIGH);
          } else {
            digitalWrite(motorPin1, LOW);
            digitalWrite(motorPin2, LOW);
          }
        }
      }
    }
  } 
  else {
    digitalWrite(ledPin1, LOW);
    digitalWrite(ledPin2, LOW);
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, LOW);
    badPostureStartTime = 0;
    isBadPosture = false;
  }

  delay(100);  // Give sensors time to settle
}




