/*
By Gabriel Staples
http://electricrcaircraftguy.blogspot.com/
5~13 June 2014
License: GNU GPL V3.0 - http://www.gnu.org/licenses/gpl.html
*/

/*
===================================================================================================
  LICENSE & DISCLAIMER
  Copyright (C) 2014 Gabriel Staples.  All right reserved.
  
  ------------------------------------------------------------------------------------------------
  License: GNU General Public License Version 3 (GPLv3) - https://www.gnu.org/licenses/gpl.html
  ------------------------------------------------------------------------------------------------

  This file is part of the Arduino_cool_Leonardo_class_demo.
  
  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see http://www.gnu.org/licenses/
===================================================================================================
*/

//------------------------------------------------------------------------------------------------------------------------------------------------------------
//make_rainbow()
//-make a rainbow (withOUT delay())
//Color progression: RED --> (YELLOW) --> GREEN --> (CYAN) --> BLUE --> (MAGENTA) --> RED
//------------------------------------------------------------------------------------------------------------------------------------------------------------
void make_rainbow()
{
  //local variables
  static unsigned int delay1 = 10000; //us; delay after each primary color, and principal mixed color (ie: red, green, blue, and yellow, cyan, magenta)
  static boolean set_main_color_pause = true; //a boolean to tell us to enact the above pause
  static unsigned int delay2 = 5000; //us; delay between changing of each PWM value
  static unsigned long t_start = micros(); //us; the start time for a delay
  static unsigned int dt_des = delay1; //us; the desired time delay; either equal to delay1 or delay2
  static byte phase = 0; //the "phase" you are in in the creating of the rainbow
  static int i = 0; //an iteration counter to be used within each phase
  
  switch (phase) 
  {
    //start with full RED, and slowly add in GREEN
    case 0: 
      if (set_main_color_pause) //if 1st iteration in this phase
      {
        analogWrite(red,255); //we are now full RED
        digitalWrite(green,LOW);
        digitalWrite(blue,LOW);
        dt_des = delay1; //allows us to pause at this point briefly to show full RED
        t_start = micros(); //us; grab a time stamp
        set_main_color_pause = false; //update
      }
      else if (micros() - t_start >= dt_des) //if the desired delay has elapsed
      {
        analogWrite(green,i);
        t_start = micros(); //reset delay start time
        dt_des = delay2; //us; delay2 is the delay between changing of each PWM value
        i++; 
        if (i==256) //we are now full YELLOW (RED AND GREEN)
        {
          i = 255; //prepare for next phase
          dt_des = delay1; //us; delay after each primary color, and principal mixed color (ie: red, green, blue, and yellow, cyan, magenta)
          phase = 1; //move to next phase
          set_main_color_pause = true; //udpate
        }
      }
      break;
    
    //As we enter this phase, we are full YELLOW (RED AND GREEN), so we will slowly subtract RED
    case 1:
      if (set_main_color_pause) //if 1st iteration in this phase
      {
        dt_des = delay1; //allows us to pause at this point briefly to show full YELLOW
        t_start = micros(); //us; grab a time stamp
        set_main_color_pause = false; //update
      }
      else if (micros() - t_start >= dt_des) //if the desired delay has elapsed
      {
        analogWrite(red,i);
        t_start = micros(); //reset delay start time
        dt_des = delay2; //us; delay2 is the delay between changing of each PWM value
        i--; 
        if (i==-1) //we are now full GREEN
        {
          i = 0; //prepare for next phase
          dt_des = delay1; //us; delay after each primary color, and principal mixed color (ie: red, green, blue, and yellow, cyan, magenta)
          phase = 2; //move to next phase
          set_main_color_pause = true; //udpate
        }
      }
      break;
      
    //As we enter this phase, we are full GREEN, so we will slowly add in BLUE
    case 2:
      if (set_main_color_pause) //if 1st iteration in this phase
      {
        dt_des = delay1; //allows us to pause at this point briefly to show full YELLOW
        t_start = micros(); //us; grab a time stamp
        set_main_color_pause = false; //update
      }
      else if (micros() - t_start >= dt_des) //if the desired delay has elapsed
      {
        analogWrite(blue,i);
        t_start = micros(); //reset delay start time
        dt_des = delay2; //us; delay2 is the delay between changing of each PWM value
        i++; 
        if (i==256) //we are now full CYAN (GREEN AND BLUE)
        {
          i = 255; //prepare for next phase
          dt_des = delay1; //us; delay after each primary color, and principal mixed color (ie: red, green, blue, and yellow, cyan, magenta)
          phase = 3; //move to next phase
          set_main_color_pause = true; //udpate
        }
      }
      break;
      
    //As we enter this phase, we are full CYAN (GREEN AND BLUE), so we will slowly SUBTRACT GREEN
    case 3:
      if (set_main_color_pause) //if 1st iteration in this phase
      {
        dt_des = delay1; //allows us to pause at this point briefly to show full YELLOW
        t_start = micros(); //us; grab a time stamp
        set_main_color_pause = false; //update
      }
      else if (micros() - t_start >= dt_des) //if the desired delay has elapsed
      {
        analogWrite(green,i);
        t_start = micros(); //reset delay start time
        dt_des = delay2; //us; delay2 is the delay between changing of each PWM value
        i--; 
        if (i==-1) //we are now full BLUE
        {
          i = 0; //prepare for next phase
          dt_des = delay1; //us; delay after each primary color, and principal mixed color (ie: red, green, blue, and yellow, cyan, magenta)
          phase = 4; //move to next phase
          set_main_color_pause = true; //udpate
        }
      }
      break;
      
    //As we enter this phase, we are full BLUE, so we will slowly ADD RED
    case 4:
      if (set_main_color_pause) //if 1st iteration in this phase
      {
        dt_des = delay1; //allows us to pause at this point briefly to show full YELLOW
        t_start = micros(); //us; grab a time stamp
        set_main_color_pause = false; //update
      }
      else if (micros() - t_start >= dt_des) //if the desired delay has elapsed
      {
        analogWrite(red,i);
        t_start = micros(); //reset delay start time
        dt_des = delay2; //us; delay2 is the delay between changing of each PWM value
        i++; 
        if (i==256) //we are now full MAGENTA (BLUE AND RED)
        {
          i = 255; //prepare for next phase
          dt_des = delay1; //us; delay after each primary color, and principal mixed color (ie: red, green, blue, and yellow, cyan, magenta)
          phase = 5; //move to next phase
          set_main_color_pause = true; //udpate
        }
      }
      break;
      
    //As we enter this phase, we are full MAGENTA (BLUE AND RED), so we will slowly SUBTRACT BLUE
    case 5:
      if (set_main_color_pause) //if 1st iteration in this phase
      {
        dt_des = delay1; //allows us to pause at this point briefly to show full YELLOW
        t_start = micros(); //us; grab a time stamp
        set_main_color_pause = false; //update
      }
      else if (micros() - t_start >= dt_des) //if the desired delay has elapsed
      {
        analogWrite(blue,i);
        t_start = micros(); //reset delay start time
        dt_des = delay2; //us; delay2 is the delay between changing of each PWM value
        i--; 
        if (i==-1) //we are now full RED
        {
          i = 0; //prepare for next phase
          dt_des = delay1; //us; delay after each primary color, and principal mixed color (ie: red, green, blue, and yellow, cyan, magenta)
          phase = 0; //start back over at first phase, since we are back to FULL RED
          set_main_color_pause = true; //udpate
        }
      }
      break;
      
  } //end of switch
} //end of make_rainbow()
