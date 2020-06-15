//Gabriel Staples
//12 June 2014

const byte red = 3;
const byte green = 5;//9;
const byte blue = 6;//10;

void setup()
{
  Serial.begin(115200);
  pinMode(red,OUTPUT);
  pinMode(green,OUTPUT);
  pinMode(blue,OUTPUT);
}

void loop()
{
//  //test each color w/digitalWrite
//  digitalWrite(red,HIGH);
//  delay(500);
//  digitalWrite(red,LOW);
//  
//  digitalWrite(green,HIGH);
//  delay(500);
//  digitalWrite(green,LOW);
//  
//  digitalWrite(blue,HIGH);
//  delay(500);
//  digitalWrite(blue,LOW);

//  //test each color w/analogWrite
//  //going up
//  for (int i=0; i<256; i++)
//  {
//    analogWrite(red,i);
//    delay(5);
//  }
//  //going down
//  for (int i=255; i>=0; i--)
//  {
//    analogWrite(red,i);
//    delay(5);
//  }
//  
//  //going up
//  for (int i=0; i<256; i++)
//  {
//    analogWrite(green,i);
//    delay(5);
//  }
//  //going down
//  for (int i=255; i>=0; i--)
//  {
//    analogWrite(green,i);
//    delay(5);
//  }
//  
//  //going up
//  for (int i=0; i<256; i++)
//  {
//    analogWrite(blue,i);
//    delay(5);
//  }
//  //going down
//  for (int i=255; i>=0; i--)
//  {
//    analogWrite(blue,i);
//    delay(5);
//  }

//  //make a rainbow (USING DELAY)
//  //local variables
//  unsigned int short_delay = 5; //ms; delay between changing of each PWM value
//  unsigned int long_delay = 1; //ms; delay after each primary color, and principal mixed color (ie: red, green, blue, and yellow, cyan, magenta)
//
//  //start with full red, and slowly add in green
//  analogWrite(red,255);
//  //here it is red
//  delay(long_delay); //pause here to briefly show full red
//  for (int i=0; i<256; i++)
//  {
//    analogWrite(green,i);
//    delay(short_delay);
//  }
//  //once green is all added in, slowly subtract red
//  //here it is yellow (red and green are full on)
//  delay(long_delay); //pause here to briefly show full yellow
//  //going down
//  for (int i=255; i>=0; i--)
//  {
//    analogWrite(red,i);
//    delay(short_delay);
//  }
//  //once red is all out, slowly add in blue
//  //here it is green
//  delay(long_delay); //pause here to briefly show full green
//  //going up
//  for (int i=0; i<256; i++)
//  {
//    analogWrite(blue,i);
//    delay(short_delay);
//  }
//  //once blue is all in, slowly subtract green
//  //here it is cyan (green and blue are full on)
//  delay(long_delay); //pause here to briefly show full cyan
//  //going down
//  for (int i=255; i>=0; i--)
//  {
//    analogWrite(green,i);
//    delay(short_delay);
//  }
//  //once green is all out, slowly add in red  
//  //here it is blue
//  delay(long_delay); //pause here to briefly show full blue
//  //going up
//  for (int i=0; i<256; i++)
//  {
//    analogWrite(red,i);
//    delay(short_delay);
//  }
//  //once red is all in, slowly subtract blue
//  //here it is magenta (blue and red are full on)
//  delay(long_delay); //pause here to briefly show full magenta
//  //going down
//  for (int i=255; i>=0; i--)
//  {
//    analogWrite(blue,i);
//    delay(short_delay);
//  }
//  //now, you are left with just red, so start back over

  make_rainbow();
  
//  digitalWrite(red,HIGH);
 
} //end of loop()


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
