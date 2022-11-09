const int pinA = 4;
const int pinB = 5;
const int pinC = 6;
const int pinD = 7;
const int pinE = 8;
const int pinF = 9;
const int pinG = 10;
const int pinDP = 11;

const int pinX = A0;
const int pinY = A1;
const int pinSw = 2;

const int segSize = 8;
const int noOfMovements = 4;

byte joyX = LOW;
byte joyY1 = LOW;
byte joyY2 = LOW;

int xValue = 0;
int yValue = 0;

int pressTime = 0;
int releaseTime = 0;
int pushedTime = 0;

byte swState = HIGH;
byte lastSwState = HIGH;
byte reading = LOW;
unsigned long lastDebounceTime = 0;
const int debounceDelay = 50;
const int longInterval = 3000;  
const int smallInterval = 25;

int segments[segSize] = {
  pinA, pinB, pinC, pinD, pinE, pinF, pinG, pinDP
};

byte stateA = LOW;
byte stateB = LOW;
byte stateC = LOW;
byte stateD = LOW;
byte stateE = LOW;
byte stateF = LOW;
byte stateG = LOW;
byte stateDP = LOW;

int posA = 0;
int posB = 1;
int posC = 2;
int posD = 3;
int posE = 4;
int posF = 5;
int posG = 6;
int posDP = 7;
int posWrong = 10;

byte blinkState = LOW;
byte currentSegmentState = LOW;
int currentSegmentPos = posDP;
int currentState = 1;

int up = 0;
int down = 1;
int left = 2;
int right = 3;

byte movements[segSize][noOfMovements] = {
  { posWrong, posG, posF, posB },           
  { posA, posG, posF, posWrong },           
  { posG, posD, posE, posDP },               
  { posG, posWrong, posE, posC },           
  { posG, posD, posWrong, posC },           
  { posA, posG, posWrong, posB },           
  { posA, posD, posWrong, posWrong },      
  { posWrong, posWrong, posC, posWrong }  
};

const int minThreshold = 400;
const int maxThreshold = 600;

unsigned long previousMillis = 0;
const unsigned long blinkInterval = 500;  

int buttonPresses = 0;


void setup() {
  pinMode(pinSw, INPUT_PULLUP);

  for (int i = 0; i < segSize; i++) {
    pinMode(segments[i], OUTPUT);
  }
}

void displayLeds() {
  if (currentSegmentPos != posA)
    digitalWrite(pinA, stateA);

  if (currentSegmentPos != posB)
    digitalWrite(pinB, stateB);

  if (currentSegmentPos != posC)
    digitalWrite(pinC, stateC);

  if (currentSegmentPos != posD)
    digitalWrite(pinD, stateD);

  if (currentSegmentPos != posE)
    digitalWrite(pinE, stateE);

  if (currentSegmentPos != posF)
    digitalWrite(pinF, stateF);

  if (currentSegmentPos != posG)
    digitalWrite(pinG, stateG);

  if (currentSegmentPos != posDP)
    digitalWrite(pinDP, stateDP);

  digitalWrite(segments[currentSegmentPos], currentSegmentState);  
}

void resetLeds() {
  stateA = LOW;
  stateB = LOW;
  stateC = LOW;
  stateD = LOW;
  stateE = LOW;
  stateF = LOW;
  stateG = LOW;
  stateDP = LOW;
  currentSegmentPos = posDP;
}

void blink() {
  if (millis() - previousMillis > blinkInterval && blinkState == LOW) {  
    previousMillis = millis();
    currentSegmentState = !currentSegmentState;
  }
}

void pushButton() {
  if (reading != lastSwState) {
    lastDebounceTime = millis();
  }

  if (millis() - lastDebounceTime > debounceDelay) {
    if (reading != swState) {
      swState = reading;
      if (swState == LOW) {
        pressTime = millis();
      } else {
        releaseTime = millis();
      }

      pushedTime = releaseTime - pressTime;
      if (pushedTime > longInterval && currentState == 1) {
        resetLeds();
      } else if (pushedTime > smallInterval) {
        buttonPresses = buttonPresses + 1;
        if (buttonPresses % 2 == 0) {
          blinkState = LOW;
          currentState = 1;
        } else {
          blinkState = HIGH;
          currentState = 2;
        }
      }
    }
  }
  lastSwState = reading;
}

void stateOne() {
  if (currentState == 1) {
    if (xValue < minThreshold && movements[currentSegmentPos][down] != posWrong && joyX == LOW) {
      currentSegmentPos = movements[currentSegmentPos][down];
      joyX = HIGH;
    } else if (xValue > maxThreshold && movements[currentSegmentPos][up] != posWrong && joyX == LOW) {
      currentSegmentPos = movements[currentSegmentPos][up];
      joyX = HIGH;
    } else if (xValue > minThreshold && xValue < maxThreshold && joyX == HIGH) {
      joyX = LOW;
    }

    if (yValue < minThreshold && movements[currentSegmentPos][left] != posWrong && joyY1 == LOW) {
      currentSegmentPos = movements[currentSegmentPos][left];
      joyY1 = HIGH;
    } else if (yValue > maxThreshold && movements[currentSegmentPos][right] != posWrong && joyY1 == LOW) {
      currentSegmentPos = movements[currentSegmentPos][right];
      joyY1 = HIGH;
    } else if (yValue > minThreshold && yValue < maxThreshold && joyY1 == HIGH) {
      joyY1 = LOW;
    }
  }
}

void stateTwo() {
  if (currentState == 2) {
    if (yValue > maxThreshold && joyY2 == LOW) {
      currentSegmentState = LOW;
      if (currentSegmentPos == posA) {
        stateA = LOW;
      } else if (currentSegmentPos == posB) {
        stateB = LOW;
      } else if (currentSegmentPos == posC) {
        stateC = LOW;
      } else if (currentSegmentPos == posD) {
        stateD = LOW;
      } else if (currentSegmentPos == posE) {
        stateE = LOW;
      } else if (currentSegmentPos == posF) {
        stateF = LOW;
      } else if (currentSegmentPos == posG) {
        stateG = LOW;
      } else if (currentSegmentPos == posDP) {
        stateDP = LOW;
      }
      joyY2 = HIGH;
    } else if (yValue < minThreshold && joyY2 == LOW) {
      currentSegmentState = HIGH;
      if (currentSegmentPos == posA) {
        stateA = HIGH;
      } else if (currentSegmentPos == posB) {
        stateB = HIGH;
      } else if (currentSegmentPos == posC) {
        stateC = HIGH;
      } else if (currentSegmentPos == posD) {
        stateD = HIGH;
      } else if (currentSegmentPos == posE) {
        stateE = HIGH;
      } else if (currentSegmentPos == posF) {
        stateF = HIGH;
      } else if (currentSegmentPos == posG) {
        stateG = HIGH;
      } else if (currentSegmentPos == posDP) {
        stateDP = HIGH;
      }
      joyY2 = HIGH;
    } else if (yValue > minThreshold && yValue < maxThreshold && joyY2 == HIGH) {
      joyY2 = LOW;
    }
  }
}
void loop() {
  displayLeds();
  blink();

  xValue = analogRead(pinX);
  yValue = analogRead(pinY);

  stateOne();
  reading = digitalRead(pinSw);
  pushButton();
  stateTwo();
}