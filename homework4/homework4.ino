const int latchPin = 11;  
const int clockPin = 10; 
const int dataPin = 12;  

const int segD1 = 7;
const int segD2 = 6;
const int segD3 = 5;
const int segD4 = 4;

const byte regSize = 8;

const int displayCount = 4;
int displayDigits[displayCount] = {
  segD1, segD2, segD3, segD4
};

const int encodingsNumber = 16;
int byteEncodings[encodingsNumber] = {
  //A B C D E F G DP
  B11111100,  // 0
  B01100000,  // 1
  B11011010,  // 2
  B11110010,  // 3
  B01100110,  // 4
  B10110110,  // 5
  B10111110,  // 6
  B11100000,  // 7
  B11111110,  // 8
  B11110110,  // 9
  B11101110,  // A
  B00111110,  // b
  B10011100,  // C
  B01111010,  // d
  B10011110,  // E
  B10001110   // F
};

const int pinX = A0;
const int pinY = A1;
const int pinSw = 2;

int xValue = 0;
int yValue = 0;

const int minThreshold = 400;
const int maxThreshold = 600;

int pressTime = 0;
int releaseTime = 0;
int pushedTime = 0;

byte joyX = LOW;
byte joyY = LOW;

byte swState = HIGH;
byte lastSwState = HIGH;
byte reading = LOW;
unsigned long lastDebounceTime = 0;
const int debounceDelay = 50;
const int longInterval = 3000;
const int smallInterval = 25;

unsigned long previousMillis = 0;
const unsigned long firstInterval = 400;
const unsigned long secondInterval = 1000;

int digitsOfDesplay[displayCount] = {
  0, 0, 0, 0
};

int buttonPresses = 0;

int currentState = 1;
int currentDisplay = 0;

void setup() {
  pinMode(pinX, INPUT);
  pinMode(pinY, INPUT);
  pinMode(pinSw, INPUT_PULLUP);

  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

  for (int i = 0; i < displayCount; i++) {
    pinMode(displayDigits[i], OUTPUT);
    digitalWrite(displayDigits[i], LOW);
  }
}

void reset() {
  digitsOfDesplay[0] = 0;
  digitsOfDesplay[1] = 0;
  digitsOfDesplay[2] = 0;
  digitsOfDesplay[3] = 0;
  currentDisplay = 0;
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
        reset();
      } else if (pushedTime > smallInterval) {
        buttonPresses = buttonPresses + 1;
        if (buttonPresses % 2 == 0) {
          currentState = 1;
        } else {
          currentState = 2;
        }
      }
    }
  }
  lastSwState = reading;
}

void writeReg(int encoding) {
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, encoding);
  digitalWrite(latchPin, HIGH);
}

void activateDisplay(int displayNumber) {
  for (int i = 0; i < displayCount; i++) {
    digitalWrite(displayDigits[i], HIGH);
  }
  digitalWrite(displayDigits[displayNumber], LOW);
}

void stateOne() {
  if (currentState == 1) {
    if (yValue > maxThreshold && joyY == LOW) {
      joyY = HIGH;
      if (currentDisplay > 0) {
        currentDisplay = currentDisplay - 1;
      }
    } else if (yValue < minThreshold && joyY == LOW) {
      joyY = HIGH;
      if (currentDisplay < displayCount - 1) {
        currentDisplay = currentDisplay + 1;
      }
    } else if (yValue >= minThreshold && yValue <= maxThreshold && joyY == HIGH) {
      joyY = LOW;
    }
  }
}

void stateTwo() {
  if (currentState == 2) {
    if (xValue > maxThreshold && joyX == LOW) {
      joyX = HIGH;
      if (digitsOfDesplay[currentDisplay] < encodingsNumber - 1) {
        digitsOfDesplay[currentDisplay]++;
      }
    } else if (xValue < minThreshold && joyX == LOW) {
      joyX = HIGH;
      if (digitsOfDesplay[currentDisplay] > 0) {
        digitsOfDesplay[currentDisplay]--;
      }
    } else if (xValue >= minThreshold && xValue <= maxThreshold && joyX == HIGH) {
      joyX = LOW;
    }
  }
}

void writeDigits(int currentDisplay) {
  for (int i = 0; i < displayCount; i++) {
    int digit = 0;

    if (i == currentDisplay) {
      if (currentState == 2) {
        digit = byteEncodings[digitsOfDesplay[i]] + 1;
      } else if (currentState == 1) {
        digit = byteEncodings[digitsOfDesplay[i]];
        if (millis() - previousMillis > firstInterval) {
          digit = byteEncodings[digitsOfDesplay[i]] + 1;
        }
        if (millis() - previousMillis > secondInterval) {
          previousMillis = millis();
          digit = byteEncodings[digitsOfDesplay[i]];
        }
      }
    } else {
      digit = byteEncodings[digitsOfDesplay[i]];
    }

    writeReg(digit);
    activateDisplay(i);
    delay(5); // run out of electricity
  }
}


void loop() {
  xValue = analogRead(pinX);
  yValue = analogRead(pinY);
  reading = digitalRead(pinSw);

  pushButton();
  stateOne();
  stateTwo();

  writeDigits(currentDisplay);
}