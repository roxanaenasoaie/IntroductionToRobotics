# IntroductionToRobotics (2021 - 2022)

Laboratory homework for the Introduction to Robotics course(3rd year @ Faculty of Matchematics and Computer Science, University of Bucharest). Each of the next homeworks will include: requirements, implementation details, code and image files. 

## Homework #1

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

