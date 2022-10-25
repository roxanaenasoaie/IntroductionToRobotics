const int ledPin = 13;
int ledState = LOW; 

unsigned long previousMillis = 0;
const long interval = 200; 

void setup() {
  pinMode(ledPin, OUTPUT);
}

void loop() {
  if (millis() >= previousMillis + interval){
    previousMillis += interval;
    digitalWrite(ledPin, HIGH);
  }

  if (millis() >= previousMillis + interval){
    previousMillis += interval;
    digitalWrite(ledPin, LOW);
  }
}