const int redPotentiometerPin = A0;
const int greenPotentiometerPin = A1;
const int bluePotentiometerPin = A2;

const int redLedPin = 11;
const int greenLedPin = 10;
const int blueLedPin = 9;

int redPotentiometerValue = 0;
int greenPotentiometerValue = 0;
int bluePotentiometerValue = 0;

int redLedValue = 0;
int greenLedValue = 0;
int blueLedValue = 0;

void setup() {
  pinMode(redPotentiometerPin, INPUT);
  // pinMode(greenPotentiometerPin, INPUT);
  pinMode(bluePotentiometerPin, INPUT);

  pinMode(redLedPin, OUTPUT);
  // pinMode(greenLedPin, OUTPUT);
  pinMode(blueLedPin, OUTPUT);
}

void loop() {
  redPotentiometerValue = analogRead(redPotentiometerPin);
  redPotentiometerValue = map(redPotentiometerValue, 0, 1023, 0, 255);
  redLedValue = redPotentiometerValue;

  // greenPotentiometerValue = analogRead(greenPotentiometerPin);
  // greenPotentiometerValue = map(greenPotentiometerValue, 0, 1023, 0, 255);
  // greenLedValue = greenPotentiometerValue;
  

  bluePotentiometerValue = analogRead(bluePotentiometerPin);
  bluePotentiometerValue = map(bluePotentiometerValue, 0, 1023, 0, 255);
  blueLedValue = bluePotentiometerValue;
 

  setColor(redLedValue, greenLedValue, blueLedValue);
}

void setColor(int redValue, int greenValue, int blueValue){
  analogWrite(redLedPin, redValue);
  // analogWrite(greenLedPin, greenValue);
  analogWrite(blueLedPin, blueValue);
}
