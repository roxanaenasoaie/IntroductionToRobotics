#include <LiquidCrystal.h>
#include <EEPROM.h>

const byte rs = 9;
const byte en = 8;
const byte d4 = 7;
const byte d5 = 6;
const byte d6 = 5;
const byte d7 = 4;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int buzzerPin = 13;

const String menuOptions[5] = {
  "Start game",
  "Leaderboard",
  "Settings",
  "How to play",
  "About"
};

const String settingsOptions[4] = {
  "Player name",
  "LCD bright.",

};


String name = "ROXI";
char nameLetters[4] = {
  'R', 'O', 'X', 'I'
};

int namePos = 0;
int menuCurrentItem = 0;

const int pinSW = 2;
const int pinX = A0;
const int pinY = A1;

bool swState = LOW;
bool lastSwState = LOW;
int state = 0;
byte switchState = HIGH;

int xValue = 0;
int yValue = 0;
int subMenuOption = 0;

bool joyX = LOW;
bool joyY = LOW;

int minThreshold = 400;
int maxThreshold = 600;

unsigned long lastDebounceTime = 0;
unsigned int debounceDelay = 50;

unsigned int score = 0;
byte leaderboard = 0;
int leaderboardPos = 0;
byte settings = 0;
int settingsPos = 0;
char* mess = "Roxana Enasoaie. github: @roxanaenasoaie";
const byte moveInterval = 100;
int LCDbrightness = 0;

byte blink = LOW;
unsigned long lastBlinkL = 0;
const int blinkInterval = 250;
unsigned long long lastMoved = 0;

int highscores[5];
String highscoreNames[5] = { "", "", "", "", "" };


void blinking() {

  if (state == 3 && settings == 1 && settingsPos == 0) {
    if (millis() - lastBlinkL > 400) {
      lastBlinkL = millis();
      blink = !blink;
    }

    lcd.setCursor(namePos + 4, 1);

    if (blink == HIGH) {
      lcd.print(nameLetters[namePos]);
    } else {
      lcd.print(" ");
    }
  }
}

void button() {
  if (swState != lastSwState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (swState != switchState) {
      switchState = swState;
      if (switchState == LOW) {
        if (state == 0) {
          state = 1;
          lcd.clear();
          lcd.print("MENU");
          lcd.setCursor(0, 1);
          lcd.print("->");
          lcd.print(menuOptions[menuCurrentItem]);
        } else if (subMenuOption == 1) {
          lcd.clear();
          lcd.print("PLAYER: ");
          lcd.print(name);
          lcd.setCursor(0, 1);
          lcd.print("SCORE: ");
          lcd.print(score);
        } else if (state == 3 && settings == 1 && settingsPos == 0) {
          state = 2;
          lcd.clear();
          lcd.print("SETTINGS");
          lcd.setCursor(0, 1);
          lcd.print("->");
          lcd.print(settingsOptions[settingsPos]);
        }
      }
    }
  }
  lastSwState = swState;
}



// memory layout:
// 2 - LCD brightness
// 3 - First highscore
// 4 -> 9 - First highscore name
// 10 - Second highscore
// 11 -> 16 - Second highscore name
// 17 - Third highscore
// 18 -> 23 - Third highscore name
// 24 - Fourth highscore
// 25 -> 30 - Fourth highscore name
// 31 - Fifth highscore
// 32 -> 37 - Fifth highscore name


void startingHighscore() {
  for (int i = 1; i <= 5; ++i) {
    EEPROM.update(i * 5, 0);
    EEPROM.update(i * 5 + 1, 'X');
    EEPROM.update(i * 5 + 2, 'X');
    EEPROM.update(i * 5 + 3, 'X');
  }
}

void updateHighscore(int newScore, String newName) {

  if (newScore > highscores[0]) {
    EEPROM.update(31, EEPROM.read(24));
    EEPROM.put(32, EEPROM.read(25));

    EEPROM.update(24, EEPROM.read(17));
    EEPROM.put(25, EEPROM.read(18));

    EEPROM.update(17, EEPROM.read(10));
    EEPROM.put(18, EEPROM.read(11));

    EEPROM.update(10, EEPROM.read(3));
    EEPROM.put(11, EEPROM.read(4));

    EEPROM.update(3, newScore);
    EEPROM.put(4, newName);
  } else if (newScore > highscores[1]) {
    EEPROM.update(31, EEPROM.read(24));
    EEPROM.put(32, EEPROM.read(25));

    EEPROM.update(24, EEPROM.read(17));
    EEPROM.put(25, EEPROM.read(18));

    EEPROM.update(17, EEPROM.read(10));
    EEPROM.put(18, EEPROM.read(11));

    EEPROM.update(10, newScore);
    EEPROM.put(11, newName);
  } else if (newScore > highscores[2]) {
    EEPROM.update(31, EEPROM.read(24));
    EEPROM.put(32, EEPROM.read(25));

    EEPROM.update(24, EEPROM.read(17));
    EEPROM.put(25, EEPROM.read(18));

    EEPROM.update(17, newScore);
    EEPROM.put(18, newName);
  } else if (newScore > highscores[3]) {
    EEPROM.update(31, EEPROM.read(24));
    EEPROM.put(32, EEPROM.read(25));

    EEPROM.update(24, newScore);
    EEPROM.put(25, newName);
  } else if (newScore > highscores[4]) {
    EEPROM.update(31, newScore);
    EEPROM.put(32, newName);
  }
}

void getData() {
  LCDbrightness = EEPROM.read(2);

  for (int i = 1; i <= 5; ++i) {
    highscores[i - 1] = EEPROM.read(7 * i - 4);
    String name;
    int addr = 7 * i - 3;
    EEPROM.get(addr, name);
    highscoreNames[i - 1] = name;
    Serial.print(highscores[i - 1]);
    Serial.print(" - ");
    Serial.println(highscoreNames[i - 1]);
  }
}

void upDown() {
  if (yValue > maxThreshold && joyY == LOW && state == 1) {
    state = 2;
    if (menuCurrentItem == 0) {
      subMenuOption = 1;
      lcd.clear();
      lcd.print("START GAME");
      lcd.setCursor(0, 1);
      lcd.print("Press to start");
    } else if (menuCurrentItem == 1) {
      lcd.clear();
      lcd.print("LEADERBOARD");
      lcd.setCursor(0, 1);
      lcd.print("                ");
      lcd.setCursor(0, 1);
      lcd.print(leaderboardPos + 1);
      lcd.print(".");
      lcd.print(highscoreNames[leaderboardPos]);
      lcd.print(" - ");
      lcd.print(highscores[leaderboardPos]);
      lcd.print(" pct");
      leaderboard = 1;
    } else if (menuCurrentItem == 2) {
      lcd.clear();
      lcd.print("SETTINGS");
      settings = 1;
      lcd.setCursor(0, 1);
      lcd.print("                ");
      lcd.setCursor(0, 1);
      lcd.print("->");
      lcd.print(settingsOptions[settingsPos]);
    } else if (menuCurrentItem == 3) {
      lcd.clear();
      lcd.print("HOW TO PLAY");
    } else if (menuCurrentItem == 4) {
      lcd.clear();
      lcd.print("ABOUT");
      lcd.setCursor(1, 1);
      lcd.print(mess);

      for (int PositionCount = 0; PositionCount < 13; PositionCount++) {
        lcd.scrollDisplayLeft();
        delay(150);

        for (int PositionCount = 0; PositionCount < 29; PositionCount++) {
          lcd.scrollDisplayRight();
          delay(150);
        }
        for (int PositionCount = 0; PositionCount < 16; PositionCount++) {
          lcd.scrollDisplayLeft();
          delay(150);
        }
      }
      joyY = HIGH;
    } else if (yValue < minThreshold && joyY == LOW && state == 2) {
      state = 1;
      leaderboardPos = 0;
      subMenuOption = 0;
      leaderboard = 0;
      settingsPos = 0;
      settings = 0;
      lcd.clear();
      lcd.print("MENU ");
      lcd.setCursor(0, 1);
      lcd.print("->");
      lcd.print(menuOptions[menuCurrentItem]);
      joyY = HIGH;
    } else if (yValue > maxThreshold && joyY == LOW && state == 2 && settings == 1) {
      state = 3;
      lcd.clear();
      if (settingsPos == 0) {
        lcd.print("NAME  Press to");
        lcd.setCursor(0, 1);
        lcd.print("    ");
        lcd.print(name);
        lcd.print("     SAVE");
      } else if (settingsPos == 1) {
        lcd.print("LCD BRIGHT.");
        lcd.setCursor(0, 1);
        lcd.print("Level: ");
        lcd.print(LCDbrightness);
      }
      joyY = HIGH;
    } else if (yValue < minThreshold && joyY == LOW && state == 3 && settings == 1 and settingsPos != 0) {
      state = 2;
      lcd.clear();
      lcd.print("SETTINGS");
      lcd.setCursor(0, 1);
      lcd.print("->");
      lcd.print(settingsOptions[settingsPos]);

      joyY = HIGH;
    } else if (yValue < minThreshold && joyY == LOW && state == 3 && settings == 1 and settingsPos == 0) {
      if (namePos > 0) {
        lcd.setCursor(namePos + 4, 1);
        lcd.print(nameLetters[namePos]);
        namePos--;
      }
      joyY = HIGH;
    } else if (yValue > maxThreshold && joyY == LOW && state == 3 && settings == 1 and settingsPos == 0) {
      if (namePos < 2) {
        lcd.setCursor(namePos + 4, 1);
        lcd.print(nameLetters[namePos]);
        namePos++;
      }
      joyY = HIGH;
    } else if (joyY == HIGH && yValue < maxThreshold && yValue > minThreshold) {
      joyY = LOW;
    }
  }
}
void leftRight() {
  if (xValue < minThreshold && joyX == LOW && state == 1 && leaderboard == 0) {
    if (menuCurrentItem < 4) {
      menuCurrentItem++;
      lcd.setCursor(0, 1);
      lcd.print("                ");
      lcd.setCursor(0, 1);
      lcd.print("->");
      lcd.print(menuOptions[menuCurrentItem]);
    }
    joyX = HIGH;
  } else if (xValue > maxThreshold && joyX == LOW && state == 1 && leaderboard == 0) {
    if (menuCurrentItem > 0) {
      menuCurrentItem--;
      lcd.setCursor(0, 1);
      lcd.print("   ");
      lcd.setCursor(0, 1);
      lcd.print("->");
      lcd.print(menuOptions[menuCurrentItem]);
    }
    joyX = HIGH;
  } else if (xValue < minThreshold && joyX == LOW && state == 2 && leaderboard == 1) {
    if (leaderboardPos < 4) {
      leaderboardPos++;
      lcd.setCursor(0, 1);
      lcd.print("    ");
      lcd.setCursor(0, 1);
      lcd.print(leaderboardPos + 1);
      lcd.print(".");
      lcd.print(highscoreNames[leaderboardPos]);
      lcd.print(" - ");
      lcd.print(highscores[leaderboardPos]);
      lcd.print(" pct");
    }
    joyX = HIGH;
  } else if (xValue > maxThreshold && joyX == LOW && state == 2 && leaderboard == 1) {
    if (leaderboardPos > 0) {
      leaderboardPos--;
      lcd.setCursor(0, 1);
      lcd.print("   ");
      lcd.setCursor(0, 1);
      lcd.print(leaderboardPos + 1);
      lcd.print(".");
      lcd.print(highscoreNames[leaderboardPos]);
      lcd.print(" - ");
      lcd.print(highscores[leaderboardPos]);
      lcd.print(" pct");
    }
    joyX = HIGH;
  } else if (xValue < minThreshold && joyX == LOW && state == 2 && settings == 1) {
    if (settingsPos < 4) {
      settingsPos++;
      lcd.setCursor(0, 1);
      lcd.print("  ");
      lcd.setCursor(0, 1);
      lcd.print("->");
      lcd.print(settingsOptions[settingsPos]);
    }
    joyX = HIGH;
  } else if (xValue > maxThreshold && joyX == LOW && state == 2 && settings == 1) {
    if (settingsPos > 0) {
      settingsPos--;
      lcd.setCursor(0, 1);
      lcd.print("  ");
      lcd.setCursor(0, 1);
      lcd.print("->");
      lcd.print(settingsOptions[settingsPos]);
    }
    joyX = HIGH;
  } else if (xValue < minThreshold && joyX == LOW && state == 3 && settings == 1) {
    if (settingsPos == 0) {
      if (nameLetters[namePos] > 'A') {
        nameLetters[namePos]--;
        lcd.setCursor(namePos + 4, 1);
        lcd.print(nameLetters[namePos]);
      }
    } else if (settingsPos == 1) {
      if (LCDbrightness > 1) {
        LCDbrightness--;
        lcd.setCursor(0, 1);
        lcd.print("  ");
        lcd.setCursor(0, 1);
        lcd.print("Level: ");
        lcd.print(LCDbrightness);
        analogWrite(3, LCDbrightness * 51);
        EEPROM.update(1, LCDbrightness);
      }
    }
    joyX = HIGH;
  } else if (xValue > maxThreshold && joyX == LOW && state == 3 && settings == 1) {
    if (settingsPos == 0) {
      if (nameLetters[namePos] < 'Z') {
        nameLetters[namePos]++;
        lcd.setCursor(namePos + 4, 1);
        lcd.print(nameLetters[namePos]);
      }
    }
  } else if (settingsPos == 1) {
    if (LCDbrightness < 5) {
      LCDbrightness++;
      lcd.setCursor(0, 1);
      lcd.print("  ");
      lcd.setCursor(0, 1);
      lcd.print("Level: ");
      lcd.print(LCDbrightness);
      analogWrite(3, LCDbrightness * 51);
      EEPROM.update(1, LCDbrightness);
    }
  } else if (joyX == HIGH && xValue < maxThreshold && xValue > minThreshold) {
    joyX = LOW;
  }
}


void setup() {
  startingHighscore();

  LCDbrightness = EEPROM.read(1);

  analogWrite(3, LCDbrightness * 51);
  pinMode(pinSW, INPUT_PULLUP);

  lcd.begin(16, 2);
  lcd.print("minigame wannabe");
  lcd.setCursor(0, 1);
  lcd.print("Press to begin");
  getData();
}

void loop() {
  blinking();

  swState = digitalRead(pinSW);
  xValue = analogRead(pinX);
  yValue = analogRead(pinY);

  button();
  upDown();
  leftRight();
}