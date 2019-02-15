# guitar-hero-project
Light board for Guitar Hero III. 

After connecting the PS2 guitar controller to the Arduino, the Arduino will send a constant stream of numbers indicating precisely
which buttons are currently being pressed, through the COM port. A secondary program on the host PC will listen to that stream of
numbers from the COM port, and use AutoHotKey to emulate keyboard/mouse events. This effectively allows the user to play the PC
version of Guitar Hero III through an Arduino. However, that was not the main point of the project.

This setup allows simultaneuous mechanical control of virtually anything. I took advantage of this and setup a row of colored floodlights
to match the color scheme of the game. Behold the birth of the unnamed Guitar Hero Project, a playable light board.
