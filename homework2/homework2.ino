const int buttonPin = 2;
const int buzzerPin = 11;

const int redLedCars = 7;
const int yellowLedCars = 6;
const int greenLedCars = 5;

const int redLedPeople = 9;
const int greenLedPeople = 8;

unsigned long timer = 0;
const int timeState1 = 8000;
const int timeState2 = 3000;
const int timeState3 = 8000;
const int timeState4 = 4000;

const int buzzerTone = 1000;
const int buzzerInterval = 250;
const int buzzerInterval2 = 150;
unsigned long lastBuzzer = 0;

const int blinkTime = 250;
unsigned long lastBlink = 0;
byte blink = LOW;

bool state1 = true;
bool state2 = false;
bool state3 = false;
bool state4 = false;

byte reading = 0;
byte buttonState = LOW;
byte buttonPushed = 0;
byte lastButtonState = LOW;
unsigned int lastDebounceTime = 0;
unsigned int debounceDelay = 50;

void setup() {
  pinMode(redLedCars,OUTPUT);
  pinMode(yellowLedCars,OUTPUT);
  pinMode(greenLedCars,OUTPUT);

  pinMode(redLedPeople,OUTPUT);
  pinMode(greenLedPeople,OUTPUT);

  pinMode(buzzerPin, OUTPUT);

  pinMode(buttonPin,INPUT);
  
}

void pushedButton() {
  reading = digitalRead(buttonPin);

  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if (millis() - lastDebounceTime > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;
      if (buttonState == LOW && state1) {
        if (buttonPushed == 0) {
          buttonPushed = 1;
          timer = millis();
        } 
      }
    }
  }
  lastButtonState = reading;
}

void stateOne() {
  digitalWrite(redLedCars, 0);
  digitalWrite(yellowLedCars, 0);
  digitalWrite(greenLedCars, 1);

  digitalWrite(redLedPeople, 1);
  digitalWrite(greenLedPeople, 0);

  noTone(buzzerPin);
  if (buttonPushed && millis() - timer > timeState1) {
    buttonPushed = 0;
    state1 = false;
    state2 = true;
    timer = millis();
  }   
}

void stateTwo() {
  digitalWrite(redLedCars, 0);
  digitalWrite(yellowLedCars, 1);
  digitalWrite(greenLedCars, 0);

  digitalWrite(redLedPeople, 1);
  digitalWrite(greenLedPeople, 0);

  noTone(buzzerPin);

  if (millis() - timer > timeState2) {
    state2 = false;
    state3 = true;
    timer = millis();
  }
}

void stateThree() {
  digitalWrite(redLedCars, 1);
  digitalWrite(yellowLedCars, 0);
  digitalWrite(greenLedCars, 0);

  digitalWrite(redLedPeople, 0);
  digitalWrite(greenLedPeople, 1);

  if (millis() - lastBuzzer > buzzerInterval) {
    noTone(buzzerPin);
  }
  if (millis() - lastBuzzer > 2 * buzzerInterval){
    tone(buzzerPin, buzzerTone);
    lastBuzzer = millis();
  }  

  if (millis() - timer > timeState3) {
    state3 = false;
    state4 = true;
    timer = millis();
  }
}

void stateFour() {
  digitalWrite(redLedCars, 1);
  digitalWrite(yellowLedCars, 0);
  digitalWrite(greenLedCars, 0);

  digitalWrite(redLedPeople, 0);
  
  if (millis() - lastBlink > blinkTime) {
    blink = !blink;
    digitalWrite(greenLedPeople, blink);
    lastBlink = millis();
  }

  digitalWrite(greenLedPeople, blink);

  if (millis() - lastBuzzer > buzzerInterval2) {
    noTone(buzzerPin);
  }

  if (millis() - lastBuzzer > 2 * buzzerInterval2){
    tone(buzzerPin, buzzerTone);
    lastBuzzer = millis();
  } 

  if (millis() - timer > timeState4) {
    state4 = false;
    state1 = true;
    timer = millis(); 
  }
}

void loop(){
  pushedButton();

  if (state1){
    stateOne();
    } 
      else if (state2) {
        stateTwo();
        } 
          else if (state3) {
            stateThree();
            } 
              else if (state4) {
                stateFour();
                }
}



