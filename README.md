# IntroductionToRobotics (2022 - 2023)

Laboratory homework for the Introduction to Robotics course(3rd year @ Faculty of Matchematics and Computer Science, University of Bucharest). Each of the next homeworks will include: requirements, implementation details, code and image files. 

## Homework #1

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

## Homework #2
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