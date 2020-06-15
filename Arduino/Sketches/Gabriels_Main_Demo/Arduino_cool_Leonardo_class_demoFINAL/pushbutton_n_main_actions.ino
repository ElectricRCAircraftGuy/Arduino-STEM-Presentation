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

//------------------------------------------------------------------------------------------------------------------------------------------
//wait_for_button_press_and_release()
//returns boolean "stop_code", to indicate we should stop the code if true, or keep going if false
//------------------------------------------------------------------------------------------------------------------------------------------
boolean wait_for_button_press_and_release(int8_t* p_button_action,boolean* p_button_state)
{
  //local variables
  boolean stop_code = false; //initialize to default
  
  //wait for button press and release
  //read button; use the ampersands (&) to pass the address to (pointers to) the variables as input parameters, so that the variables can be updated by the function
  //Details:
    //read the button action, and store it into the button_action variable; and read the button state, & store it into the button_state variable
    //The button state can be 0 or 1, for LOW or HIGH, respectively
    // button action indicates what just happened to the button: 
    //	0 = no-change in true, debounced button state since last time reading the button, or debounceDelay time not yet elapsed
    //	1 = button was just pressed by a human operator (debounceDelay had elapsed)
    //       -1 = button was just released by a human operator (debounceDelay had elapsed)
  button1.readButton(p_button_action,p_button_state);
  while (*p_button_action!=1) //wait for a button press
  {
    button1.readButton(p_button_action,p_button_state);
    if (digitalRead(USB_emulationOn_pin)==HIGH) //stop code early
    {
      stop_code = true;
      return stop_code;
    }
  }
  //a press has occured, light up LED 13
  digitalWrite(ledPin,HIGH);
  while (*p_button_action!=-1) //wait for a button release
  {
    button1.readButton(p_button_action,p_button_state);
    if (digitalRead(USB_emulationOn_pin)==HIGH) //stop code early
    {
      stop_code = true;
      return stop_code;
    }
  }
  
  //a button release has occured, so turn off LED 13
  digitalWrite(ledPin,LOW);
  
  //at this point, as the function exits, the button_action is -1 (button released) and the button_state is 1 (HIGH), which correlates to BUTTON_NOT_PRESSED
  return stop_code; //default is false
}

//------------------------------------------------------------------------------------------------------------------------------------------
//do_this_action_until_button_pressed
//-this function performs the specified action (via the pointer-to-a-function input parameter), until a button PRESS is detected.  Once a PRESS
// is detected, the function will not exit until the button RELEASE is detected as well!
//-returns boolean "stop_code", to indicate we should stop the code if true, or keep going if false
//-requires a pointer to a void void function as an input parameter
//--for more info on Function Pointers, see here: http://www.cplusplus.com/doc/tutorial/pointers/
//--also see here for more detailed help with Function Pointers specifically: http://www.eskimo.com/~scs/cclass/int/sx10a.html
//------------------------------------------------------------------------------------------------------------------------------------------
boolean do_this_action_until_button_pressed_then_wait_for_release(int8_t* p_button_action,boolean* p_button_state,void (*functionToCall)(void))
{
  //local variables
  boolean stop_code = false; //initialize to default
  
  //start the indicated action, and continue until another button press is detected, and so long as the pin to command keyboard/mouse output is still LOW
  while (*p_button_action!=1) //do the following until you get a button PRESS
  {
    if (digitalRead(USB_emulationOn_pin)==HIGH)
    {
      stop_code = true;
      return stop_code;
    }
    (*functionToCall)(); //do this action
    button1.readButton(p_button_action,p_button_state); //read pushbutton
  }
  //button press has now been detected
  digitalWrite(ledPin,HIGH);
  while (*p_button_action!=-1) //wait for a button RELEASE
  {
    if (digitalRead(USB_emulationOn_pin)==HIGH)
    {
      stop_code = true;
      return stop_code;
    }
    button1.readButton(p_button_action,p_button_state); //read pushbutton
  }
  //button release detected
  digitalWrite(ledPin,LOW);
  
  //at this point, as the function exits, the button_action is -1 (button released) and the button_state is 1 (HIGH), which correlates to BUTTON_NOT_PRESSED
  return stop_code; //default is false
}

//------------------------------------------------------------------------------------------------------------------------------------------
//take_distance_readings_until_button_pressed()
//-gets distance readings and prints to the screen at a rate of 2 Hz (every 500,000 us)
//-returns boolean "stop_code", to indicate we should stop the code if true, or keep going if false
//-THIS FUNCTION IS MODELED AFTER THE "do_this_action_until_button_pressed_then_wait_for_release" function
//------------------------------------------------------------------------------------------------------------------------------------------
boolean take_distance_readings_until_button_pressed(int8_t* p_button_action,boolean* p_button_state)
{
  //local variables and constants
  boolean stop_code = false; //initialize to default
  unsigned long t_start = 0; //us; start time
  unsigned long t_now = micros(); //us; time stamp now
  const unsigned long dt_des = 500000; //us; desired period between outputs
  
  //start the indicated action, and continue until another button press is detected, and so long as the pin to command keyboard/mouse output is still LOW
  while (*p_button_action!=1) //do the following until you get a button PRESS
  {
    if (digitalRead(USB_emulationOn_pin)==HIGH)
    {
      stop_code = true;
      return stop_code;
    }
    
    //--------------------------------------------------------------------------------------------------------
    //read the ultrasonic rangefinder here
    //local variables
    unsigned int t_ping; //us; the ping time there and back again
    float dist_in, dist_ft; //in; ft; distance measured
    
    t_now = micros(); //us
    if (t_now - t_start >= dt_des) //if it's time to output another sample
    {
      t_start = t_now; //us; update
      getDistance(&t_ping,&dist_in,&dist_ft,9); //get a median-filtered distance sample, from 9 raw samples
      //print the results to the monitor
      move_cursor_to_end(); //press ctrl + end to make sure cursor is at the very end of the document, in case the user moved the cursor duing the pause
      Keyboard.print(F("Ping time (us) = ")); Keyboard.print(t_ping); Keyboard.print(F(", dist (in) = ")); Keyboard.print(dist_in); Keyboard.print(F(", dist (ft) = ")); Keyboard.println(dist_ft);
    }
    //--------------------------------------------------------------------------------------------------------
    button1.readButton(p_button_action,p_button_state); //read pushbutton
  } //end of while loop
  //button press has now been detected
  digitalWrite(ledPin,HIGH);
  while (*p_button_action!=-1) //wait for a button RELEASE
  {
    if (digitalRead(USB_emulationOn_pin)==HIGH)
    {
      stop_code = true;
      return stop_code;
    }
    button1.readButton(p_button_action,p_button_state); //read pushbutton
  }
  //button release detected
  digitalWrite(ledPin,LOW);
  
  //at this point, as the function exits, the button_action is -1 (button released) and the button_state is 1 (HIGH), which correlates to BUTTON_NOT_PRESSED
  return stop_code; //default is false
}

//------------------------------------------------------------------------------------------------------------------------------------------
//ultrasonic_alarm_go_until_button_pressed
//-grabs the current distance, and stores it as the "dist_calibrated"; prints "ALARM, INTRUDER ALERT!" if any future distance readings are < (dist_calibrated - 6 in)
//--ends if button is pressed and released
//-returns boolean "stop_code", to indicate we should stop the code if true, or keep going if false
//-THIS FUNCTION IS MODELED AFTER THE "do_this_action_until_button_pressed_then_wait_for_release" function
//------------------------------------------------------------------------------------------------------------------------------------------
boolean ultrasonic_alarm_go_until_button_pressed(int8_t* p_button_action,boolean* p_button_state)
{
  //local variables and constants
  boolean stop_code = false; //initialize to default
  float calibrated_dist_in = 0; //in; calibrated distance in inches; initialize to zero
  unsigned int t_ping; //us; the ping time there and back again
  float dist_in, dist_ft; //in; ft; distance measured
  
  //first, calibrate the alarm to the current distance
  getDistance(&t_ping,&dist_in,&dist_ft,21); //get a median-filtered distance sample, from 21 raw samples
  calibrated_dist_in = dist_in; //in
  
  //print the calibrated value and explain how the alarm works
  move_cursor_to_end(); //press ctrl + end to make sure cursor is at the very end of the document, in case the user moved the cursor duing the pause
  Keyboard.print(F("ALARM ON.  My calibrated alarm distance value is ")); Keyboard.print(calibrated_dist_in); 
  Keyboard.print(F(" inches.  I have been programmed so that if I ever measure a future distance less than my calibrated value, minus 6 inches (in this case, "));
  Keyboard.print(calibrated_dist_in - 6); 
  Keyboard.println(F(" inches or less), it means that there is something blocking my path (ie: a human body), and so I will sound "
                   "an alarm and assume there is an intruder in front of me!  Have people walk in front of me to see me in action!\n"));
  
  //start the indicated action, and continue until another button press is detected, and so long as the pin to command keyboard/mouse output is still LOW
  while (*p_button_action!=1) //do the following until you get a button PRESS
  {
    if (digitalRead(USB_emulationOn_pin)==HIGH)
    {
      stop_code = true;
      return stop_code;
    }
    
    //--------------------------------------------------------------------------------------------------------
    //read the ultrasonic rangefinder to look for intruder
    getDistance(&t_ping,&dist_in,&dist_ft,3); //get a median-filtered distance sample, from 3 raw samples
    if (dist_in <= calibrated_dist_in - 6) //if the distance is decreased by > 6 in, that means there is an intruder there!
    { //INTRUDER!
      #if SKIP_BUZZER_DEMO!=1 //only sound the piezo alarm if the buzzer demo is NOT being skipped by the compiler
        //sound the alarm for 2 seconds (in the background, so the code will continue on meanwhile once it *starts* this action!)
        toneAC(2000,10,2000,true); //Format: toneAC(freq(Hz),volume(0-10),duration(ms),play_in_background(true/false))
      #endif
      //print the alert
      move_cursor_to_end(); //press ctrl + end to make sure cursor is at the very end of the document, in case the user moved the cursor duing the pause
      Keyboard.print(F("ALARM, INTRUDER ALERT! -- distance to intruder (in) = ")); Keyboard.println(dist_in);
    }
    //--------------------------------------------------------------------------------------------------------
    button1.readButton(p_button_action,p_button_state); //read pushbutton
  } //end of while loop
  //button press has now been detected
  digitalWrite(ledPin,HIGH);
  while (*p_button_action!=-1) //wait for a button RELEASE
  {
    if (digitalRead(USB_emulationOn_pin)==HIGH)
    {
      stop_code = true;
      return stop_code;
    }
    button1.readButton(p_button_action,p_button_state); //read pushbutton
  }
  //button release detected
  digitalWrite(ledPin,LOW);
  
  //at this point, as the function exits, the button_action is -1 (button released) and the button_state is 1 (HIGH), which correlates to BUTTON_NOT_PRESSED
  return stop_code; //default is false
}

//------------------------------------------------------------------------------------------------------------------------------------------
//take_light_sensor_readings_until_button_pressed()
//-gets light sensor readings and prints to the screen at a rate of 2 Hz (every 500,000 us)
//-returns boolean "stop_code", to indicate we should stop the code if true, or keep going if false
//-THIS FUNCTION IS MODELED AFTER THE "do_this_action_until_button_pressed_then_wait_for_release" function
//------------------------------------------------------------------------------------------------------------------------------------------
boolean take_light_sensor_readings_until_button_pressed(int8_t* p_button_action,boolean* p_button_state,unsigned int dark_to_dim,unsigned int dim_to_bright)
{
  //local variables and constants
  boolean stop_code = false; //initialize to default
  unsigned long t_start = 0; //us; start time
  unsigned long t_now = micros(); //us; time stamp now
  const unsigned long dt_des = 500000; //us; desired period between outputs
  
  //start the indicated action, and continue until another button press is detected, and so long as the pin to command keyboard/mouse output is still LOW
  while (*p_button_action!=1) //do the following until you get a button PRESS
  {
    if (digitalRead(USB_emulationOn_pin)==HIGH)
    {
      stop_code = true;
      return stop_code;
    }
    
    //--------------------------------------------------------------------------------------------------------
    //read the light sensor here, and print the results
    //local variables
    unsigned int reading = analogRead(photoPin);
    move_cursor_to_end(); //press ctrl + end to make sure cursor is at the very end of the document, in case the user moved the cursor duing the pause
    Keyboard.print(F("light reading = ")); Keyboard.print(reading); 
    //evaluate the reading
    if (reading < dark_to_dim) //it is pitch black
    {
      Keyboard.println(F(". It is pitch black in here."));    
    }
    else if (reading > dim_to_bright) //it is bright
    {
      Keyboard.println(F(". It is bright in here."));   
    }
    else //it is in the middle
    {
      Keyboard.println(F(". It is dim in here."));   
    }
    //--------------------------------------------------------------------------------------------------------
    button1.readButton(p_button_action,p_button_state); //read pushbutton
  } //end of while loop
  //button press has now been detected
  digitalWrite(ledPin,HIGH);
  while (*p_button_action!=-1) //wait for a button RELEASE
  {
    if (digitalRead(USB_emulationOn_pin)==HIGH)
    {
      stop_code = true;
      return stop_code;
    }
    button1.readButton(p_button_action,p_button_state); //read pushbutton
  }
  //button release detected
  digitalWrite(ledPin,LOW);
  
  //at this point, as the function exits, the button_action is -1 (button released) and the button_state is 1 (HIGH), which correlates to BUTTON_NOT_PRESSED
  return stop_code; //default is false
}

//------------------------------------------------------------------------------------------------------------------------------------------
//read_user_input_via_number_of_button_presses
//-makes the input parameter boolean "true" if user does 2 presses, and "false" if user does 1 press, within a limited time period
//------------------------------------------------------------------------------------------------------------------------------------------
void read_user_input_via_number_of_button_presses(int8_t* p_button_action,boolean* p_button_state,boolean* p_keep_going1)
{
  //local variables
  byte press_count = 0; //initialize to zero each time we enter this function, in order to start from scratch and be ready to go!
  unsigned long t_last_press; //ms; last button press time stamp
  
  //read-button while loop
  boolean keep_going2 = true;
  while (keep_going2==true)
  {
    button1.readButton(p_button_action,p_button_state); //read pushbutton
    if (*p_button_action==1) //if button was pressed
    {
      t_last_press = millis(); //ms
      press_count++;
      move_cursor_to_end(); //press ctrl + end to make sure cursor is at the very end of the document, in case the user moved the cursor duing the pause
      Keyboard.print(F("button press count = ")); Keyboard.println(press_count);
    }
    if (press_count==1)
    {
      if (millis() - t_last_press >= 3000) //if only one press was registered, and the time has elapsed
      {
        //the user does NOT want to repeat the alarm demo
        keep_going2 = false; //exit this while loop
        *p_keep_going1 = false; //exit the alarm demo while loop
      }
    }
    else if (press_count==2)
    {
      //the user DOES want to repeat the alarm demo
      keep_going2 = false; //exit this while loop
      *p_keep_going1 = true; //repeat the alarm demo
    }
  } //end of read button while loop
}
