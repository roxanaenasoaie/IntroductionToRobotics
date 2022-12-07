# IntroductionToRobotics (2022 - 2023)

Laboratory homework for the Introduction to Robotics course(3rd year @ Faculty of Matchematics and Computer Science, University of Bucharest). Each of the next homeworks will include: requirements, implementation details, code and image files. 

<details>

<summary>Homework #1</summary>

Assignment
---
**Task:** Use a separate potentiometer in controlling each of the
color of the RGB led (Red, Green and Blue). The control must be done
with digital electronics.

**How?** We're gonna connect each of the 3 potentiometers to 3 pins (I chose A0, A1, A2) and each of the RGB colors to 3 pins (I chose 11, 10, 9).
Using Arduino, we read the value of each potentiometer and pass it to the corresponding color in the RGB Led.

**What I did**

[![Setup Picture](https://i.postimg.cc/J01bPrgy/assignment.jpg)](https://postimg.cc/KkHkY2mF)

[Functionality Video](https://youtube.com/shorts/4djHFnrXhTU?feature=share)



Exercise 1
---
**Task:** Make a blinking LED *without using* delay() function.

**Why?**
The delay() function pauses the program for the amount of time specified as a parameter.
While it is easy to create a blinking LED with the delay() function and many sketches use
short delays for such tasks as switch debouncing, the use of delay() in a sketch has
significant drawbacks. No other reading of sensors, mathematical calculations, or pin
manipulation can go on during the delay function, so in effect, it brings most other activity to
a halt. More knowledgeable programmers usually avoid the use of delay() for timing of
events longer than 10’s of milliseconds unless the Arduino sketch is very simple.

**How?**
Best way is to use **millis()**. This function returns the number of milliseconds passed since the Arduino board began running the current program.
There's 2 main advantages with millis() compared to delay(). Firstly, the timing is accurate.  With millis() we can ensure that the loop runs as often as we want, regardless of the execution time (obviously as long as the execution time is less time the desired period). With delay() this is not possible since we do not know how long the loop execution time is.
The other advantage with millis() is that it won’t prevent us from running code while “waiting”.

**Example**

With delay():

```
delay(1000);
digitalWrite(ledPin, LOW);
```

With millis():

```
if (millis() >= previousMillis + interval){
    previousMillis += interval;
    digitalWrite(ledPin, LOW);
  }
```

**What I did**

[![Setup Picture](https://i.postimg.cc/zGJx63Fz/hw1-1.jpg)](https://postimg.cc/vcN76YKk)

[Functionality Video](https://youtu.be/Mvy08pWvHFI)


Exercise 2
---

**Task:** Fading a LED with the potentiometer.

**What I did**

[![Setup Picture](https://i.postimg.cc/kG8d1wPh/hw1-2.jpg)](https://postimg.cc/4HJMn6dz)

[Functionality Video](https://youtube.com/shorts/yT9gC4pJmiY?feature=share)

</details>


<details>

<summary>Homework #2</summary>

---

**Task**: Building the traffic lights for a crosswalk. To use: 2 LEDs to represent the traffic lights for people (red and green)and 3 LEDs to represent the traffic lights for cars (red, yellow and green).
The system has the following states:
1. State 1(default, reinstated after state 4 ends): green light for cars, red light for people,no sounds. Duration: indefinite, changed bypressing the button.
2. State 2(initiated by counting down 8 seconds after a button press): the light should be yellow for cars, red for people and no sounds. Duration: 3 seconds.
3. State 3(initiated after state 2 ends): red for cars, green for people and a beeping sound from the buzzer at a constant interval. Duration: 8 seconds.
4. State 4(initiated after state 3 ends): red for cars, blinking green for people and a beeping sound from the buzzer,  at a constant interval, faster than the beeping in state 3. This state should last 4 seconds.

**What I did**

[![Setup Picture](https://i.postimg.cc/QxxZPGjS/hw2.jpg)](https://postimg.cc/hhwYzYz7)

[Functionality Video](https://youtu.be/-LcT8adIUzk)

</details>

<details>

<summary>Homework #3</summary>

---

**Task**: Use the joystick to control the position of the segment and ”draw” on the display.The system has the following states:
1. State 1(default, but also initiated after a button press in State 2): Current position blinking. Can use the joystick to move from one position to neighbors. Short pressing the button toggles state 2. Long pressing the button in state 1 resets the entire display byturning all the segments OFF and moving the current position to the decimal point.
2. State 2(initiated after a button press in State 1): The current segment stops blinking, adopting the state of the segment before selection(ON or OFF). Toggling the Y axis should change the segment state from ON to OFF or from OFF to ON. Clicking the joystick should save the segment state and exit back to state 1.

**What I did**

[![Setup Picture](https://i.postimg.cc/bJnXwpG3/hw3.jpg)](https://postimg.cc/BLJ7hWBK)

[Functionality Video](https://youtu.be/44QTKkxa96s)

</details>

<details>

<summary>Homework #4</summary>

---

**Task:** Use the joystick to move through the 4 digit 7-segment displays digits, press the button to lock in on the current digit
and use the other axis to increment or decrement the number. Keep the button pressed to reset all the digit values and the current position to the
first digit in the first state.

The system has the following states:
1. First state: use a joystick axis to cycle through the 4 digits;
using the other axis does nothing. A blinking decimal point shows
the current digit position. When pressing the button, lock in on
the selected digit and enter the second state.
2. Second state: in this state, the decimal point stays always on, no
longer blinking and you can no longer use the axis to cycle through
the 4 digits. Instead, using the other axis, you can increment on
decrement the number on the current digit IN HEX. Pressing the button again returns to the
previous state. 
3. Reset: toggled by long pressing the button only in the first state.
When resetting, all the digits go back to 0 and the current position
is set to the first (rightmost) digit, in the first state.

**What I did**

[![Setup Picture](https://i.postimg.cc/d1yjbm29/hw4.jpg)](https://postimg.cc/R6vtftb3)

[Functionality Video](https://youtube.com/shorts/fYbnFPj7W4k?feature=share)

</details>

<details>

<summary>Homework #5</summary>

---

**Task:** Create a menu for a game. It should scroll on the LCD with the joystick. The menu should include the following functionality:
1.  When powering up a game, a greeting message should be shown fora few moments.
2.  Should contain roughly the following categories:
(a)Start game, starts the initial level of your game
(b)Highscore: Initially, we have 0. –Update  it  when  the  game  is  done. 
(c)Settings:–Enter name. The name should be shown in highscore.

**How to navigate**: Up and down move with joystick to move through the menu options. Move the joystick to the right to enter a submenu, move to the left to return.
**What I did**

[![Setup](https://i.postimg.cc/mrNF8bmg/hw5.jpg)](https://postimg.cc/t1JTgH0K)

[Functionality Video](https://youtube.com/shorts/IHthmePmfMM?feature=share)

</details>