# guitar-hero-project

## Intro
  I don’t have a fancy name for this project, and I likely never will. I got the idea for this project at the end of my junior year in Computer Science at Benson High School. I started work on the project at the beginning of my senior year. Initially, my proposal for the project was for a 5 x 11 board of lights (Figure 1), colored the same way a Guitar Hero 3 fretboard would be. The user would be able to only use the board of lights, and they could play the game by viewing it. The lights would be controlled by a matrix of Silicon Controlled Rectifiers through an Arduino microcontroller, along with a Guitar Hero guitar. The final product was definitely different than imagined, however I love it all the same. It turned into something beautiful.

<img src="images/GuitarLights.png" height="300">

## TIMELINE

Controlling Lights. I decided that I would break the project down into steps, and develop foundations for each major component of it. The first thing I did was make a series of LEDs blink on/off every half-second. I received funding from the school to buy a set of relays online. I used those relays to blink 120v incandescent lights via the Arduino using the same code I did with the LEDs.

Guitar Implementation. I already owned a Playstation 2 Guitar Hero controller, and coupled with a PS2 to USB converter, I could connect it to the PC. My original plan was to intercept the signals from the controller on the PC, and then communicate with the Arduino what lights to blink on/off. I ran into several problems during that process and had to reconsider the direction I was heading. Problems such as: Do I need to recreate an entire game on the Arduino? How could I synchronize the GH3 song database to the Arduino? What kind of mechanical array would I need for the matrix of light bulbs? Most of the questions I needed to answer entailed a much more difficult solution.  I wondered if I could do it the other way around, and instead connect the controller directly to the Arduino for immediate access of the signals. I did some research and I eventually came across a website referencing a code library with everything I needed. A huge thanks to Bill Porter.

That evening I scrapped an old PlayStation 2 I had that was no longer in use, and took the dual female PS2 port. I had to unsolder several connections and actually lost one side of the port. Thankfully I had one intact and that was all that I needed.

Building the Board. I found a sizeable wooden board (about 3’ x 2’) and mounted the Arduino in the bottom right corner. Inside the school I found a giant electrical switch box that made a loud snapping noise upon each movement. I mounted that in the center of the board. In the bottom left is where I mounted the female PS2 port, which has wires running from the switch box to the Arduino. Above the switch box, spaced evenly along the top, are 5 lights that match the standard GH3 color scheme. 120 volts come in through the switch box and power the lights. The lights are controlled by a set of relays inside of the switch box, which are controlled by the Arduino.

Putting it all together. So I’ve connected the controller to the Arduino, and with the PS2X_Library, I can parse the signals from the controller. I also have the ability to control the lights with the controller, mapping the corresponding light to the correct button press. However, I still have no interface between the player and the game. My solution was the godsend that is AutoHotKey, and a giant switch-case for all possible (and practical) button combinations.

I had the Arduino constantly spitting out what state the controller is in, as in what buttons are pressed, with several binary digits going through the Serial COM port. When the Arduino is connected to a PC, it will send it these digits through the COM port. I wrote a program to receive these binary digits, and simulate keyboard presses for the PC version of Guitar Hero 3. The night before the deadline, I was stuck on a problem that a classmate was able to solve, and saved me from even more heartache. Thanks again, Aidan! The problem had to do with a loop that wasn’t working right for the program on the host PC.

I was (and still am) amazed at the end result. A light board that shines on corresponding button presses, that makes playing along with Guitar Hero a million times more awesome. I surprisingly had few issues with latency.

PICTURE

## TECHNICAL SUMMARY

Here are the basics: The guitar being played sends signals directly to the Arduino. The Arduino will turn on the respective light upon button presses. The Arduino (which is connected to a PC) also writes an eight digit string to the COM port (this string identifies which buttons are currently pressed). A program I wrote is designed to read this string of digits from the COM port, and use AutoHotKey (an open source library) to perform keyboard presses. The computer is running the PC version of Guitar Hero 3, which expects keyboard input. My program uses AHK to do just that.

## CONCLUSION
I couldn’t have fulfilled this project without my awesome Computer Science teacher Mr. Beckler. He actively supported me during this project and made sure I had all the resources I needed. I had so much fun doing this project, and I learned so much. It took me almost the entirety of my senior year to finish the project, becoming what it is today. It currently rests at Benson High School.




  After connecting the PlayStation2 guitar controller to the Arduino, the Arduino will send a constant stream of numbers indicating precisely which buttons are currently being pressed, through the COM port. A secondary program on the host PC will listen to that stream of numbers from the COM port, and use AutoHotKey to emulate keyboard/mouse events. This effectively allows the user to play the PC
version of Guitar Hero III through an Arduino. However, that was not the main point of the project.

This setup allows simultaneuous mechanical control of virtually anything. I took advantage of this and setup a row of colored floodlights
to match the color scheme of the game. Behold the birth of the unnamed Guitar Hero Project, a playable light board.
