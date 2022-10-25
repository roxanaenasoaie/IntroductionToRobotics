const int potPin = A0;
const int ledPin = 9;

int potValue = 0;
int ledValue = 0;

void setup() {
  pinMode(potPin, INPUT);
  pinMode(ledPin, OUTPUT);
}
void loop() {
  potValue = analogRead(potPin);
  ledValue = potValue;
  analogWrite(ledPin, ledValue);
}
