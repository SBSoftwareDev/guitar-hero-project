/*
 * For any problems, visit www.billporter.info
 * See readme to enable debug.
 */

#include <PS2X_lib.h>

#define Light1 1
#define Light2 2
#define Light3 3
#define Light4 4
#define Light5 5

PS2X ps2x;

int error = 0; 
byte colors = 0;
char result[11];

void setup(){
  Serial.begin(9600);

  for(int i = 2; i < 7; i++) pinMode(i, OUTPUT);

  error = ps2x.config_gamepad(13,11,10,12);   //Clock, Command, Attention, Data.

  //Q means NO CONTROLLER FOUND
  if(error == 1)
    Serial.println("Q");

  //W means Controller found but not accepting commands.
  else if(error == 2)
    Serial.println("W");

  //Serial.print(ps2x.Analog(1), HEX);

  int type = 2;
   
  switch(type) {
  case 0:
    Serial.println("Unknown Controller type");
    break;
  case 2:
    //R means GuitarHero Controller Found
    Serial.println("R");
    break;
  }
}

void loop(){
  if(error != 0) //skip loop if no controller found
    return;

  else
  {
    ps2x.read_gamepad();  //read controller 

    if(ps2x.Button(GREEN_FRET))
    {
      result[2] = '1';
      bitSet(colors, Light1);
    }
    else
    {
      result[2] = '0';
      bitClear(colors, Light1);
    }

    if(ps2x.Button(RED_FRET))
    {
      result[3] = '1';
      bitSet(colors, Light2);
    }
    else
    {
      result[3] = '0';
      bitClear(colors, Light2);
    }

    if(ps2x.Button(YELLOW_FRET))
    {
      result[4] = '1';
      bitSet(colors, Light3);
    }
    else
    {
      result[4] = '0';
      bitClear(colors, Light3);
    }

    if(ps2x.Button(BLUE_FRET))
    {
      result[5] = '1';
      bitSet(colors, Light4);
    }
    else
    {
      result[5] = '0';
      bitClear(colors, Light4);
    }

    if(ps2x.Button(ORANGE_FRET))
    {
      result[6] = '1';
      bitSet(colors, Light5);
    }
    else
    {
      result[6] = '0';
      bitClear(colors, Light5);
    }

    if(ps2x.Button(UP_STRUM))
    {
      result[1] = '1';
      //bitSet(colors, 6);
    }
    else
    {
      result[1] = '0';
      //bitClear(colors, 6);
    }
    
    if(ps2x.Button(DOWN_STRUM))
    {
      result[0] = '1';
      //bitSet(colors, 7);
    }
    else
    {
      result[0] = '0';
      //bitClear(colors, 7);
    }

    if(ps2x.Button(PSB_SELECT))
    {
      result[7] = '1';
      //bitSet(colors, 7);
    }
    else
    {
      result[7] = '0';
      //bitClear(colors, 7);
    }

    if(ps2x.Button(PSB_START))
    {
      result[8] = '1';
      //bitSet(colors, 7);
    }
    else
    {
      result[8] = '0';
      //bitClear(colors, 7);
    }

    if(ps2x.ButtonPressed(STAR_POWER))
    {
      result[9] = '1';
      //bitSet(colors, 7);
    }
    else
    {
      result[9] = '0';
      //bitClear(colors, 7);
    }
    
//    //I think it freezes up here
//    if(map(ps2x.Analog(WHAMMY_BAR), 0, 127, 0, 9) != 0)
//    {
//      result[10] = map(ps2x.Analog(WHAMMY_BAR), 0, 127, 0, 9);
//      //bitSet(colors, 7);
//    }
//    else
//    {
//      result[10] = '0';
//      //bitClear(colors, 7);
//    }
  }

if (ps2x.Analog(WHAMMY_BAR) > 71) {
  result[10] = '0';
} else if (ps2x.Analog(WHAMMY_BAR) < 70) {
  result[10] = '1';
}
  //Serial.println(ps2x.Analog(WHAMMY_BAR));
  Serial.println(result);
  //Serial.println(map(ps2x.Analog(WHAMMY_BAR), 0, 127, 0, 9));

  //We want the lights to turn off and then back on, upon a new strum.
  //Create a function to do that?
  
  for(int i = 1; i <= 6; i++)
  {
    if(bitRead(colors, i-1)) 
    {
      digitalWrite(i, HIGH);
    }
    else digitalWrite(i, LOW);

    bitClear(colors, i-1); 
  }
  
  delay(20);
}



