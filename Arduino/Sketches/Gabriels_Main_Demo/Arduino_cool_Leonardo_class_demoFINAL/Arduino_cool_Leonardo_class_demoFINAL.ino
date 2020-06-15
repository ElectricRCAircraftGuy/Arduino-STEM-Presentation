/*
arduino_cool_Leonardo_class_demo.ino
-a demo that will automatically open up MS Word on a PC it is plugged into, and begin doing cool stuff!
By Gabriel Staples
http://electricrcaircraftguy.blogspot.com/
5~14 June 2014

License: GNU GPL V3.0 - http://www.gnu.org/licenses/gpl.html

Microsoft Word Shortcuts: http://office.microsoft.com/en-us/word-help/keyboard-shortcuts-for-word-HP005186664.aspx

Instructions:
-plug the ATmega32U4-based Arduino, running this code (ex: Leonardo, Micro, Pro Micro) into any Windows-based PC, and watch the magic happen!
 Note: this code was tested on a Windows PC running Windows 7 Professional, and with Microsoft Word 2007
-NOTE: Microsoft Word must be *closed* before letting the Arduino run its code, or else the setFontColor() function may not work correctly since it will not be on the correct tab when 
 it goes into the settings, and then it will hit the arrow key when it shouldn't, etc etc.  <---I'm not totally sure this is correct, but I saw something that indicated this might be true,
 during preliminary testing; TODO: CHECK THIS COMMENT TO VERIFY VALIDITY.
-If you ever need to stop the program early, and prevent further mouse or keyboard manipulation by the program, remove the "USB_emulationOn_pin" pin from GND
 (thereby allowing this pin to go HIGH), and press the "reset" button on the Leonardo.
-The entirety of the demo codes is too large to fit on one Arduino Leonardo (ATmega32U4 microcontroller), so I will use the below defines to 
 ELIMINATE some code so that the demo get small enough to be uploaded to the device.  This will now require uploading and running the Demo twice: once for 
 the first set of demos, and a second time to run the demos that were skipped during the first time.  Use the DEMO_NUMBER define below to set
 which demo you'd like to run: 1 or 2!

Circuit - connect sensors as follows
For the Arduino Leonardo:
Ultrasonic Rangefinder:
  Pin    Arduino Pin
  VCC    5V
  Trig   12
  Echo   11
  GND    GND
Pushbutton:
  -one leg to GND
  -other leg to 2
Potentiometer:
  -one outer leg to +5V
  -other outer leg to GND
  -wiper (middle leg) to A2
TMP36 Temperature Sensor (viewed with FLAT side facing towards you, and legs pointed downwards)
  Left leg to +5V
  Middle leg to A0
  Right leg to GND
Piezo buzzer
  One leg to 10
  Other leg to 9
Photoresistor (light sensor)
  One leg on photoresistor to +5V
  Other leg on photoresistor to 10K resistor
  Other leg on 10K resistor to GND
  Read the voltage across the 10K resistor by connecting the junction of the 10K resistor, with the photoresistor leg, to A1
  Diagram as follows:
    +5V --> photoresistor --[*]--> 10k resistor --> GND
                            [*] pin A1 is connected here meaning it is reading the voltage drop across the 10K resistor, to GND 
RGB LED (common cathode [negative leg])
  red leg (anode, +) --> 330 Ohm resistor --> 3 (PWM-capable pin)
  green leg (anode, +) --> 330 Ohm resistor --> 5 (PWM-capable pin)
  blue leg (anode, +) --> 330 Ohm resistor --> 6 (PWM-capable pin)
Servo
  brown wire (-) to GND
  red wire (+) to +5V
  yellow wire* (signal) to 4
  *Note: sometimes the signal wire is white instead of yellow
Activation "switch"
  Connect a wire from 7 to GND to activate the demo code; leave 7 open to disable the demo code
  Once 7 is connected go GND, press the Ardino's reset button and then just wait for the demo to begin (takes 5~10 seconds from power-on to open up MSWord, then another 
   5 sec to begin typing)
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
//Choose your Demo Version Here!
//First, upload and do Demo1, then, upload and do Demo2!
//-due to memory constraints, all of this code could not be done as a single demo :(, so these defines help choose which code to compile and load, and 
// which code to ignore.
//------------------------------------------------------------------------------------------------------------------------------------------
//Choose which code to compile and load
#define DEMO_NUMBER (1) //set to 1 for Demo1, or set to 2 for Demo2   //<--------USER-SETTABLE PARAMETER!!!!  CHOOSE YOUR DEMO # HERE!!!

//For the demo, to make it spooky when I plug the Leonardo into their computer (put their name here)
const char persons_name[] = "Alexa"; //<--INSERT PARTICIPANT'S NAME HERE, JUST BEFORE UPLOADING THE CODE AND BEGINNING THE DEMO WITH THEM

#if DEMO_NUMBER==1
  #define SKIP_MOUSE_DEMO (1) //1 for Skip, 0 for do NOT skip
  #define SKIP_RANGEFINDER_DEMO (0) //1 for Skip, 0 for do NOT skip //NB: IF YOU WANT THE RANGEFINDER ALARM DEMO TO BE ABLE TO SOUND THE PIEZO ALARM,
                                                                    //YOU MUST HAVE THE BUZZER DEMO ENABLED TOO! 
  #define SKIP_LIGHTSENSOR_DEMO (0) //1 for Skip, 0 for do NOT skip
  #define SKIP_RGBLED_DEMO (0) //1 for Skip, 0 for do NOT skip
  #define SKIP_TEMPSENSOR_DEMO (0) //1 for Skip, 0 for do NOT skip
  #define SKIP_SERVO_DEMO (1) //1 for Skip, 0 for do NOT skip
  #define SKIP_BUZZER_DEMO (0) //1 for Skip, 0 for do NOT skip
#elif DEMO_NUMBER==2
  #define SKIP_MOUSE_DEMO (0) //1 for Skip, 0 for do NOT skip
  #define SKIP_RANGEFINDER_DEMO (1) //1 for Skip, 0 for do NOT skip  //NB: IF YOU WANT THE RANGEFINDER ALARM DEMO TO BE ABLE TO SOUND THE PIEZO ALARM,
                                                                     //YOU MUST HAVE THE BUZZER DEMO ENABLED TOO! 
  #define SKIP_LIGHTSENSOR_DEMO (1) //1 for Skip, 0 for do NOT skip
  #define SKIP_RGBLED_DEMO (1) //1 for Skip, 0 for do NOT skip  
  #define SKIP_TEMPSENSOR_DEMO (1) //1 for Skip, 0 for do NOT skip
  #define SKIP_SERVO_DEMO (0) //1 for Skip, 0 for do NOT skip
  #define SKIP_BUZZER_DEMO (1) //1 for Skip, 0 for do NOT skip
#endif
  
//------------------------------------------------------------------------------------------------------------------------------------------
//More Defines (Compiler Directives)
//------------------------------------------------------------------------------------------------------------------------------------------
#define SKIP_THIS_CODE_DURING_TESTING (1) //a compiler directive I am using to skip portions of the code during testing and debugging, so that I can just run the part of the demo I am
                                          //interested in, during development, rather than having to go through the whole thing just to test my latest addition at the end
                                          
//------------------------------------------------------------------------------------------------------------------------------------------
//Libraries to include
//------------------------------------------------------------------------------------------------------------------------------------------
#include <eRCaGuy_ButtonReader.h> //used to debounce and read the pushbutton
#if SKIP_RANGEFINDER_DEMO!=1
  #include <NewPing.h> //for ultrasonic rangefinder; note: this library uses the ATmega328 Timer2, thereby disabling Arduino PWM outputs on Pins 3 & 11 when NewPing is in use
#endif
//#include <Servo.h> //uses Timer1 also, so conflicts with toneAC; therefore, I think I'll try bit-banging the servo instead; update: bit-banging worked but was very jittery,
                     //so I have instead modified the Arduino Servo library to use Timer3 on the Leonardo
#if SKIP_SERVO_DEMO!=1 //a Compiler Directive used to disable portions of code to save memory
 #include <Servo_32U4_Timer3.h> //This is a modified version of the main Arduino "Servo" library.  I have simply made a few minor changes to force
                               //the library to use the Leonardo's/(any board w/a 32U4 microcontroller)'s Timer3 instead of Timer1. 
			       //I got the idea from the instructions found here: http://www.pololu.com/docs/0J57/8.b
			       //~Gabriel Staples, http://electricrcaircraftguy.blogspot.com/
#endif

#if SKIP_BUZZER_DEMO!=1
  #include <toneAC.h> //connect buzzer to pins 9 & 10
                      //uses the ATmega328's/Leonardo's (I think too) Timer 1, so PWM will no longer work on pins 9 & 10!
  #include "pitches.h"
  #include "mario_songs.h"
#endif

//Externally-defined functions (the below lines are ABSOLUTELY MANDATORY it seems, in order to use Function Pointers in Arduino! ~GS)
//See here for help with pointers: http://www.cplusplus.com/doc/tutorial/pointers/
//And see here for detailed help with Function Pointers specifically (though the above link discusses them some too): http://www.eskimo.com/~scs/cclass/int/sx10a.html
extern boolean do_this_action_until_button_pressed_then_wait_for_release(int8_t* p_button_action,boolean* p_button_state,void (*functionToCall)(void));

//------------------------------------------------------------------------------------------------------------------------------------------
//Global Constants and Variables
//------------------------------------------------------------------------------------------------------------------------------------------

//Mouse & Keyboard
//Pin to activate the Leonardo as a USB keyboard/mouse device
byte USB_emulationOn_pin = 7; //don't do any mouse or keyboard emulation unless this pin is LOW (ie: tied to GND); 
                  //this prevents locking up your Arduino & causing problems when you are trying to reprogram it

//Strings repeatedly used
char press_to_continue_str[] = "(Press my pushbutton to continue)\n";
char press_to_continue_press_to_stop_str[] = "(Press my pushbutton to continue; press it again to stop)\n";
char press_to_continue_press_and_HOLD_to_stop_str[] = "(Press my pushbutton to continue; press and HOLD it to stop)\n";

//For the pushbutton
const byte buttonPin = 2; //the number of the pushbutton pin
const byte ledPin = 13; // the number of the LED pin
//Define Button States:
const boolean BUTTON_PRESSED = LOW; //if using a pull-up resistor (ex: INPUT_PULLUP) on your button, the buttonPin will be LOW when the button is pressed; 
const boolean BUTTON_NOT_PRESSED = HIGH; //if using a pull-up resistor (ex: INPUT_PULLUP) on your button, the buttonPin will be HIGH when the button is NOT pressed

//For the Ultrasonic Rangefiner
const byte ping_triggerPin = 12; //Arduino pin tied to trigger pin on the ultrasonic sensor.
const byte ping_echoPin = 11; //Arduino pin tied to echo pin on the ultrasonic sensor.
const unsigned int max_distance = 500; //cm; Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
const float MICROSECONDS_PER_INCH = 74.6422; //us per inch; sound traveling through air at sea level standard day ~GS

//for the photoresistor (light sensor)                                                                                                        
const byte photoPin = A1; //this measures the voltage across the resistor, which is in series w/the photoresistor:  +5V --> photoresistor --[*]--> 10k resistor --> GND
                          //[*] pin A1 is connected here meaning it is reading the voltage drop across the 10K resistor, to GND 

//for the RGB LED
//connect the red LED to pin 3, green to pin 5, blue to pin 6
const byte red = 3; 
const byte green = 5;
const byte blue = 6;

//for the TMP36 analog temperature sensor!
const byte tempPin = A0;

//For the servo
const byte potPin = A2; //the pin that reads the potentiometer to control the servo
const byte servoPin = 4; //pin to control the servo (this connects to the signal wire going *into* the servo)

//For the Piezo buzzer & Mario Music
const byte volume = 10; //choose from 0 to 10, with 10 being the loudest

//------------------------------------------------------------------------------------------------------------------------------------------
//Class Object Instantiations
//------------------------------------------------------------------------------------------------------------------------------------------

//instantiate an object of this library class; call it "button1"
//if not explicitly stated, debounceDelay defaults to 50ms, and the _BUTTON_PRESSED value in the library defaults to LOW; see .h file for details
eRCaGuy_ButtonReader button1 = eRCaGuy_ButtonReader(buttonPin); 
//alternatively, the object instantiation could be explicit, as follows:
//eRCaGuy_ButtonReader button1 = eRCaGuy_ButtonReader(buttonPin,50,BUTTON_PRESSED);

#if SKIP_RANGEFINDER_DEMO!=1
  NewPing sonar(ping_triggerPin,ping_echoPin,max_distance); //NewPing setup of pins and maximum distance.
#endif

#if SKIP_SERVO_DEMO != 1 //a Compiler Directive used to disable portions of code to save memory
  Servo_32U4_Timer3 myservo; //create servo object to control a servo 
#endif


//------------------------------------------------------------------------------------------------------------------------------------------
//setup()
//------------------------------------------------------------------------------------------------------------------------------------------
void setup()
{
  //local variables
  boolean stop_code = false; //used to stop the code if the USB_emulationOn_pin is not longer connected to GND; initialize to false
  
  delay(7500); //wait 7.5 sec from the time the board is powered, to the time we start doing stuff,
               //in order to allow the computer to recognize the device and begin receiving commands
               //from it.  
               //NB: IN MY TESTING, THIS DELAY IS ***ABSOLUTELY*** NECESSARY. IF YOU DON'T USE IT, FOR WHATEVER REASON, THE KEYBOARD.PRINT()
               //COMMANDS WILL OUTPUT RANDOM, GARBLED GARBAGE instead of what you put into them.
  
  Serial.begin(115200);
  Keyboard.begin();
  
  //local variables
  int8_t button_action; //see details below
  boolean button_state; //see details below
  
  //pin setup
  pinMode(USB_emulationOn_pin,INPUT_PULLUP);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  pinMode(red,OUTPUT);
  pinMode(green,OUTPUT);
  pinMode(blue,OUTPUT);
  
//  //servo
//  myservo.attach(servoPin); //<--DO *NOT* DO THIS HERE, AFTERALL, AS IT AFFECTS Timer3, which seems to be controlling PWM outputs on one or more of pins 3, 5, & 6 on a Leonardo
                              //(used by this code for the RGB LED)
  
  //only simulate a USB device (keyboard/mouse) if the specified pin is LOW (tied to GND)
  if (digitalRead(USB_emulationOn_pin)!=LOW)
  {
    return; //leave the entire setup() function
  }
  //otherwise, continue on...
  
  //START OF CODE PORTION I AM MARKING TO *NOT* EXECTUTE
  #if SKIP_THIS_CODE_DURING_TESTING != 1 //a Compiler Directive used to disable portions of code during development ~GS
  #endif //END OF CODE PORTION I AM MARKING TO *NOT* EXECTUTE, during testing & debugging

  open_and_configure_MSWord();
  
  //begin the interaction!
  Keyboard.print(F("Hello ")); Keyboard.print(persons_name); Keyboard.print(F("!  How are you doing???\n\n"));
  //increase the size of the font by pressing ctrl + a to select what we just wrote, then ctrl + shift + b to make it bold,
  //then "ctrl + shift + >" 8 times to increase the font size
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press('a');
  delay(100);
  Keyboard.releaseAll();
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press('b');
  delay(100);
  for (byte i=0; i<8; i++)
  {
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press(KEY_LEFT_SHIFT);
    Keyboard.press('.'); //. is the > key
    delay(100);
    Keyboard.releaseAll();
    delay(1500);
  }
  //press right arrow to unhighlight the text
  Keyboard.press(KEY_RIGHT_ARROW);
  delay(100);
  Keyboard.releaseAll();
  
  static char text1[] = "I'm watching you.";
  Keyboard.println(text1);
  //set Microsoft Word font to red
  setFontColor(255,0,0);
  Keyboard.println(F("That's right."));
  //print "I'm watching you." again, slowly, letter by letter
  printString(text1,sizeof(text1)-1,500); //the -1 is so we don't print the null terminator at the end of the string, causing an extra pause
  printString("..",2,500); //add two extra dots at the end of the phrase

  //add two new lines and set the font back to normal (black) before continuing
  Keyboard.print(F("\n\nI am in your computer :) \n"
                 "I can change your font.\n"));
  delay(2000);
  setFontColor(0,0,0);
  Keyboard.println(F("I am black font."));
  delay(1000);
  setFontColor(0,255,0);
  Keyboard.println(F("I am green."));
  delay(1000);
  setFontColor(0,0,255);
  Keyboard.println(F("I am blue."));
  delay(1000);
  //reset font settings back to normal
  setDefaultFontSettings();
  //bold off (ctrl + b)
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press('b');
  delay(100);
  Keyboard.releaseAll();
  //back to black font
  setFontColor(0,0,0);
  Keyboard.println(F("I am back to normal\n"));
  //at this point, my font is back to size 12
  //let's use "ctrl + shift + >" 2 times in order to continue on with Font Size 16, so the audience can see better
  for (byte i=0; i<2; i++)
  {
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press(KEY_LEFT_SHIFT);
    Keyboard.press('.'); //. is the > key
    delay(100);
    Keyboard.releaseAll();
    delay(100);
  }
  delay(1000);
  
  //------------------------------------------------------------------------------------------------------------------------------------------
  //Begin the games!
  //------------------------------------------------------------------------------------------------------------------------------------------
  Keyboard.println(F("Would you like to play a game?\n"));
  delay(500);
  Keyboard.println(F("Before you say \"yes,\" have the instructor point out the various parts (sensors, electronics, components, etc), connected to me, and "
                     "ask him what they do.\n"));
  delay(1000);
  Keyboard.println(F("Can you identify the following?\n"
                     "1. Arduino Leonardo\n" //begin numbering
                     "breadboard\n" //MS Word will take over with autonumbering from here
                     "jumper cables\n"
                     "ultrasonic rangefinder (\"ping\" sensor)\n"
                     "TMP36 analog temperature sensor (ie: a thermometer)\n"
                     "photoresistor (light sensor)\n"
                     "tri-color LED (RGB LED), and resistors\n"
                     "piezo buzzer\n"
                     "potentiometer (ie: a variable resistor, or user input knob)\n"
                     "servo motor/acutator\n"
                     "pushbutton\n"));
  delay(500);
  Keyboard.println(F("\n(When ready, press the button connected to the Arduino Leonardo to continue.)\n"));
  stop_code = wait_for_button_press_and_release(&button_action,&button_state);
  if (stop_code==true){return;} //if stop_code==true; leave the entire setup() function
  move_cursor_to_end(); //press ctrl + end to make sure cursor is at the very end of the document, in case the user moved the cursor duing the pause
  
  //continue the games
  Keyboard.println(F("I have a whole bunch of cool sensors and things I can do, and I'd like to show you throughout a series of interactive demonstrations!\n"));
  delay(1000);
  
  Keyboard.print("[FYI: The code I am running contains Demo #"); Keyboard.print(DEMO_NUMBER); 
  Keyboard.println(".  To change the Demo #, you will have to recompile and upload new code to me.]\n");

//  #endif //END OF CODE PORTION I AM MARKING TO *NOT* EXECTUTE, during testing & debugging

  #if SKIP_MOUSE_DEMO != 1 //a Compiler Directive used to disable portions of code due to memory restrictions
    //------------------------------------------------------------------------------------------------------------------------------------------
    //mouse demos
    //------------------------------------------------------------------------------------------------------------------------------------------
    move_cursor_to_end(); //press ctrl + end to make sure cursor is at the very end of the document, in case the user moved the cursor duing the pause
    Keyboard.println(F("First, let me show you how I can move your mouse.  You've seen me use your keyboard, so now watch this!\n"));
    delay(500);
    Keyboard.println(F("During the following mouse activities, feel free to try and move the mouse around during these events, "
                     "to see how much control you still have over the mouse.  During some of the events, you can still guide the mouse around.\n"));
                     
    //random_mouse_slide_around
    Keyboard.println(F("We will start with what I call \"random_mouse_slide_around\".  Again, feel free to try and move the mouse around during these activities, "
                       "to see how much control you still have over the mouse."));
    Keyboard.println(press_to_continue_press_and_HOLD_to_stop_str);
    
    //Wait for first button press
    stop_code = wait_for_button_press_and_release(&button_action,&button_state); 
    if (stop_code==true){return;} //if stop_code==true; leave the entire setup() function
    //Perform action until button is pressed again
    stop_code = do_this_action_until_button_pressed_then_wait_for_release(&button_action,&button_state,random_mouse_slide_around);
    if (stop_code==true){return;} //if stop_code==true; leave the entire setup() function
    move_cursor_to_end(); //press ctrl + end to make sure cursor is at the very end of the document, in case the user moved the cursor duing the pause
    
    //random_mouse_jump_around
    Keyboard.println(F("Pretty cool, huh!? Next mouse action: \"random_mouse_jump_around\"."));
    Keyboard.println(press_to_continue_press_to_stop_str);
    
    //Wait for first button press
    stop_code = wait_for_button_press_and_release(&button_action,&button_state); 
    if (stop_code==true){return;} //if stop_code==true; leave the entire setup() function
    //Perform action until button is pressed again
    stop_code = do_this_action_until_button_pressed_then_wait_for_release(&button_action,&button_state,random_mouse_jump_around);
    if (stop_code==true){return;} //if stop_code==true; leave the entire setup() function
    move_cursor_to_end(); //press ctrl + end to make sure cursor is at the very end of the document, in case the user moved the cursor duing the pause
    
    //random_mouse_buzz_around
    Keyboard.println(F("Next mouse action: \"random_mouse_buzz_around\"."));
    Keyboard.println(press_to_continue_press_to_stop_str);
    
    //Wait for first button press
    stop_code = wait_for_button_press_and_release(&button_action,&button_state); 
    if (stop_code==true){return;} //if stop_code==true; leave the entire setup() function
    //Perform action until button is pressed again
    stop_code = do_this_action_until_button_pressed_then_wait_for_release(&button_action,&button_state,random_mouse_buzz_around);
    if (stop_code==true){return;} //if stop_code==true; leave the entire setup() function
    move_cursor_to_end(); //press ctrl + end to make sure cursor is at the very end of the document, in case the user moved the cursor duing the pause
    
    //draw_squares_with_mouse_movements
    Keyboard.println(F("Next mouse action: \"draw_squares_with_mouse_movements\"."));
    Keyboard.println(press_to_continue_press_and_HOLD_to_stop_str);
    
    //Wait for first button press
    stop_code = wait_for_button_press_and_release(&button_action,&button_state); 
    if (stop_code==true){return;} //if stop_code==true; leave the entire setup() function
    //Perform action until button is pressed again
    stop_code = do_this_action_until_button_pressed_then_wait_for_release(&button_action,&button_state,draw_squares_with_mouse_movements);
    if (stop_code==true){return;} //if stop_code==true; leave the entire setup() function
    move_cursor_to_end(); //press ctrl + end to make sure cursor is at the very end of the document, in case the user moved the cursor duing the pause
    
    //mouse_move_to_lower_left_of_screen
    Keyboard.println(F("Next mouse action: \"mouse_move_to_lower_left_of_screen\".  During this demo, be sure to try and keep the mouse cursor in the center of the screen!"));
    printString(press_to_continue_press_to_stop_str,sizeof(press_to_continue_press_to_stop_str),0);
  
    //Wait for first button press
    stop_code = wait_for_button_press_and_release(&button_action,&button_state); 
    if (stop_code==true){return;} //if stop_code==true; leave the entire setup() function
    //Perform action until button is pressed again
    stop_code = do_this_action_until_button_pressed_then_wait_for_release(&button_action,&button_state,mouse_move_to_lower_left_of_screen);
    if (stop_code==true){return;} //if stop_code==true; leave the entire setup() function
    move_cursor_to_end(); //press ctrl + end to make sure cursor is at the very end of the document, in case the user moved the cursor duing the pause
  #elif SKIP_MOUSE_DEMO == 1
    Keyboard.println(F("Skipping really cool mouse control demos since there are too many demos to fit on the Arduino all at one time.  Compile & run the "
                       "other main demo code to see any skipped demos!\n"));
  #endif //END OF CODE PORTION I AM MARKING TO *NOT* EXECTUTE
  
  //move on to the sensors!
  Keyboard.println(F("Now, let's read some of my sensors!  I think these are pretty neat too!"));
  
  boolean keep_going1; //for a couple of the demos below
  
  #if SKIP_RANGEFINDER_DEMO!=1 //a Compiler Directive used to disable portions of code due to memory restrictions
    //------------------------------------------------------------------------------------------------------------------------------------------
    //Ultrasonic Rangefinder Demos
    //------------------------------------------------------------------------------------------------------------------------------------------
    Keyboard.println(F("Let's start with my ultrasonic rangefinder, shall we?  It has a maximum range of 4~5 meters, or 12~16 ft.\n"
                       "In order to demonstrate another neat thing I can do, for the following paragraph, I'm going to type out the letters one-by-one, slowly, as if I was a human "
                       "typing at your keyboard.\n"
                       "(Press my pushbutton to continue.)\n"));
    stop_code = wait_for_button_press_and_release(&button_action,&button_state); 
    if (stop_code==true){return;} //if stop_code==true; leave the entire setup() function
    move_cursor_to_end(); //press ctrl + end to make sure cursor is at the very end of the document, in case the user moved the cursor duing the pause
                       
    //For the fun of it, let's do something unique here.  I will store a long string in PROGMEM, and write a loop to slowly type
    //it out, as if a person was typing
    //note: on the below use of PROGMEM, the "static" keyword is mandatory, and "const" is encouraged; see here: http://forum.arduino.cc/index.php?topic=245480.0 
    PROGMEM static const char text2[] = "Press the button for me to begin taking distance readings every 1 second.  Aim the ultrasonic rangefinder around the room to measure the "
                                        "distance to various objects.  When you are done, press the button again (you may have to HOLD THE BUTTON DOWN FOR A SECOND to get it to register this \"stop command\" press).  "
                                        "Be sure to try this too: hold the sensor high, up to your head, and aim it downwards at the floor, to measure your height, before pressing "
                                        "the button to move on!  Give others a chance too if they would like.  Again, press the button on my board to begin, and long-press "
                                        "it when you are done using this sensor.  I will output data 2x per second (ie: at 2 Hz).\n\n";
    //print out text2 one char at a time, for a cool "human-like" typing effect
    for (unsigned int i=0; i<sizeof(text2); i++)
    {
      Keyboard.print(char(pgm_read_byte(&(text2[i]))));
      delay(40);
    }
    Keyboard.println(press_to_continue_press_and_HOLD_to_stop_str);
  
    stop_code = wait_for_button_press_and_release(&button_action,&button_state); 
    if (stop_code==true){return;} //if stop_code==true; leave the entire setup() function
    move_cursor_to_end(); //press ctrl + end to make sure cursor is at the very end of the document, in case the user moved the cursor duing the pause
    
    //begin taking sensor data and printing to screen at 2Hz (ie: every 500,000 us)
    stop_code = take_distance_readings_until_button_pressed(&button_action,&button_state);
    if (stop_code==true){return;} //if stop_code==true; leave the entire setup() function
    move_cursor_to_end(); //press ctrl + end to make sure cursor is at the very end of the document, in case the user moved the cursor duing the pause
    Keyboard.print(F("\n"));
    
    //-----------------------------------------------------------------------
    //ultrasonic rangefinder alarm
    move_cursor_to_end(); //press ctrl + end to make sure cursor is at the very end of the document, in case the user moved the cursor duing the pause
    Keyboard.println(F("Ok, now it's time for me to demonstrate how I could be used to make a house alarm. Aim me right where you want me to look, "
                       "at any surface *less than* ~10 ft away, then make sure I am well-secured, that no one is in front of me, and that I do not move. For this "
                       "demo, you *will* get another chance to try it out in case you do a bad distance calibration. So, if it doesn't seem to work right, "
                       "press the button to end, and I'll give you instructions to start it over again."));
  
    //Alarm demo while loop (to allow repeats of this demo)
    keep_going1 = true;
    while (keep_going1==true)
    {
      Keyboard.println(F("\n(When ready to calibrate and activate the alarm, press my pushbutton to continue, and then press it again to end my \"alarm\" mode, when done.)\n"));
      stop_code = wait_for_button_press_and_release(&button_action,&button_state); 
      if (stop_code==true){return;} //if stop_code==true; leave the entire setup() function 
      stop_code = ultrasonic_alarm_go_until_button_pressed(&button_action,&button_state);
      if (stop_code==true){return;} //if stop_code==true; leave the entire setup() function
      move_cursor_to_end(); //press ctrl + end to make sure cursor is at the very end of the document, in case the user moved the cursor duing the pause
      Keyboard.println(F("\nALARM OFF."));
      delay(1000);
      //should we repeat the demo?
      move_cursor_to_end(); //press ctrl + end to make sure cursor is at the very end of the document, in case the user moved the cursor duing the pause
      Keyboard.println(F("\nWould you like to redo the alarm calibration and repeat this demonstration? If so, press the pushbutton TWICE in a row (the 2nd press "
                         "must occur within 3 seconds of the 1st press). Otherwise, press the button only once, then wait 3 seconds.\n"));
      
      //read the user's answer (YES or NO) via their button presses
      read_user_input_via_number_of_button_presses(&button_action,&button_state,&keep_going1); //makes the input parameter boolean "true" if user does 2 presses, and "false" if user does 1 press, within a limited time period
    }//end of Alarm demo while loop
    
    Keyboard.println(F("\nMoving on...\n"
                       "If you'd like to learn how to use this ultrasonic rangefinder (\"ping\" sensor) truly as a home alarm system, "
                       "see the \"Additional Demo Info - Gabriel.docx\" file that came with this demo.  This stuff really is powerful!\n"
                       "(Press the pushbutton to continue.)\n"));
    
    stop_code = wait_for_button_press_and_release(&button_action,&button_state); 
    if (stop_code==true){return;} //if stop_code==true; leave the entire setup() function  
  #elif SKIP_RANGEFINDER_DEMO==1
    Keyboard.println(F("\nSkipping really cool ultrasonic rangefinder (\"ping\" sensor) demos since there are too many demos to fit on the Arduino all at one time.  Compile & run the other main demo code to see any skipped demos!\n"));
  #endif

  #if SKIP_LIGHTSENSOR_DEMO!=1
    //------------------------------------------------------------------------------------------------------------------------------------------
    //TMP36 Light Sensor Demo
    //------------------------------------------------------------------------------------------------------------------------------------------
    move_cursor_to_end(); //press ctrl + end to make sure cursor is at the very end of the document, in case the user moved the cursor duing the pause
    Keyboard.println(F("Is it bright in here?  Let's find out!  Time for a light sensor demo.  I'm going to begin taking light intensity readings, using "
                       "my photoresistor, and outputting data at 2 Hz (2 times per second).  While I am outputting data, cover my light sensor to see how that affects me.  "
                       "I have been programmed to only recognize three light levels, as you will see.  First, however, let's calibrate my sensor to the lighting "
                       "in this room."));
                       
    //light sensor demo while loop (to allow repeats of this demo)
    keep_going1 = true;
    while (keep_going1==true)
    {
      Keyboard.println(F("\n(Make sure my light sensor is NOT covered, then press my pushbutton to calibrate the \"bright\" light setting.)\n"));
                         
      stop_code = wait_for_button_press_and_release(&button_action,&button_state); 
      if (stop_code==true){return;} //if stop_code==true; leave the entire setup() function             
      unsigned int bright = get_avg_of_50_light_readings(); //bright light reading
      move_cursor_to_end(); //press ctrl + end to make sure cursor is at the very end of the document, in case the user moved the cursor duing the pause
      Keyboard.print(F("The calibrated bright light reading is ")); Keyboard.println(bright); Keyboard.println();
      Keyboard.println(F("Now, let's calibrate the \"dark\" reading. \n"
                         "(Gently cover the light sensor with your finger, then press the pushbutton to continue.)\n"));
      stop_code = wait_for_button_press_and_release(&button_action,&button_state); 
      if (stop_code==true){return;} //if stop_code==true; leave the entire setup() function     
      unsigned int dark = get_avg_of_50_light_readings(); //dark light reading
      
      move_cursor_to_end(); //press ctrl + end to make sure cursor is at the very end of the document, in case the user moved the cursor duing the pause
      Keyboard.print(F("The calibrated dark light reading is ")); Keyboard.println(dark); Keyboard.println();
      
      //figure out steps
      //find the value you will consider the transition from pitch black to dim; make it the dark reading + 20% of the difference
      unsigned int dark_to_dim = dark + (bright-dark)*0.2;
      //find the value you will consider the transition from dim to bright; make it the bright reading - 20% of the difference
      unsigned int dim_to_bright = bright - (bright-dark)*0.2;
      
      Keyboard.print(F("Light sensor calibration done.\n"
                       "Readings below ")); Keyboard.print(dark_to_dim); Keyboard.print(F(" will be considered \"pitch black\"\n"));
      Keyboard.print(F("From ")); Keyboard.print(dark_to_dim); Keyboard.print(F(" to ")); Keyboard.print(dim_to_bright); Keyboard.print(F(" will be considered \"dim\", and\n"));
      Keyboard.print(F("Above ")); Keyboard.print(bright); Keyboard.print(F(" will be considered \"bright\".\n"));
      Keyboard.println(F("Now, we will begin taking and printing light readings at 2 Hz.  Play around with the light sensor by covering it, either entirely or partially, to see how that "
                         "affects the results.  Also, turn the lights on and off in the room and watch the readings change!\n"));
      Keyboard.println(press_to_continue_press_and_HOLD_to_stop_str);
                         
      stop_code = wait_for_button_press_and_release(&button_action,&button_state); 
      if (stop_code==true){return;} //if stop_code==true; leave the entire setup() function
      stop_code = take_light_sensor_readings_until_button_pressed(&button_action,&button_state,dark_to_dim,dim_to_bright);
      if (stop_code==true){return;} //if stop_code==true; leave the entire setup() function
      move_cursor_to_end(); //press ctrl + end to make sure cursor is at the very end of the document, in case the user moved the cursor duing the pause
      Keyboard.println(F("\nLight Sensor OFF."));
      delay(1000);
      
      //should we repeat the demo?
      Keyboard.println(F("\nWould you like to redo the photoresistor calibration and repeat this light sensor demonstration? If so, press the pushbutton TWICE in a row (the 2nd press "
                         "must occur within 3 seconds of the 1st press). Otherwise, press the button only once, then wait 3 seconds.\n"));
      
      //read the user's answer (YES or NO) via their button presses
      read_user_input_via_number_of_button_presses(&button_action,&button_state,&keep_going1); //makes the input parameter boolean "true" if user does 2 presses, and "false" if user does 1 press, within a limited time period
    } //end of light sensor demo while loop
    //exiting light sensor demo
    Keyboard.println(F("\nExiting light sensor demo."));
    Keyboard.println(press_to_continue_str);
    stop_code = wait_for_button_press_and_release(&button_action,&button_state); 
    if (stop_code==true){return;} //if stop_code==true; leave the entire setup() function
  #elif SKIP_LIGHTSENSOR_DEMO==1
    Keyboard.println(F("\nSkipping light sensor (photoresistor) demos since there are too many demos to fit on the Arduino all at one time.  Compile "
                       "& run the other main demo code to see any skipped demos!\n"));
  #endif

  #if SKIP_RGBLED_DEMO!=1
    //------------------------------------------------------------------------------------------------------------------------------------------
    //RGB LED
    //------------------------------------------------------------------------------------------------------------------------------------------                       
    move_cursor_to_end(); //press ctrl + end to make sure cursor is at the very end of the document, in case the user moved the cursor duing the pause                       
    Keyboard.println(F("In this next demonstration, I'm going to be using an RGB (Red/Green/Blue) LED.  This means that a single LED case has all three of these LED "
                       "colors built right in, as separate LEDs, but all in the same plastic case.  You can turn them on one at a time, or all at once, or "
                       "whatever you want.  Additionally, using the analogWrite() command in Arduino, you can send a PWM (Pulse Width Modulation) signal to an "
                       "LED to vary its brightness, or intensity.  Therefore, using one RGB LED you can mix different intensities of colored light and generate ANY color of the rainbow.  "
                       "Let's see this in action!\n\n"
                       
                       "(Press my pushbutton to see the red LED turn on).\n"));
                       
    stop_code = wait_for_button_press_and_release(&button_action,&button_state); 
    if (stop_code==true){return;} //if stop_code==true; leave the entire setup() function
    digitalWrite(red,HIGH);
    
    move_cursor_to_end(); //press ctrl + end to make sure cursor is at the very end of the document, in case the user moved the cursor duing the pause
    Keyboard.println(F("(Now press my pushbutton to see only the green LED on)."));
    stop_code = wait_for_button_press_and_release(&button_action,&button_state); 
    if (stop_code==true){return;} //if stop_code==true; leave the entire setup() function
    digitalWrite(red,LOW);
    digitalWrite(green,HIGH);
    
    move_cursor_to_end(); //press ctrl + end to make sure cursor is at the very end of the document, in case the user moved the cursor duing the pause
    Keyboard.println(F("(Now press my pushbutton to see only the blue LED on)."));
    stop_code = wait_for_button_press_and_release(&button_action,&button_state); 
    if (stop_code==true){return;} //if stop_code==true; leave the entire setup() function
    digitalWrite(green,LOW);
    digitalWrite(blue,HIGH);
    
    move_cursor_to_end(); //press ctrl + end to make sure cursor is at the very end of the document, in case the user moved the cursor duing the pause
    Keyboard.println(F("(Now press my pushbutton to see both the RED AND GREEN LED on.  This makes Yellow.  Practice on your own later to write code to make "
                       "the RGB LED turn yellow, cyan and magenta).\n"));
    stop_code = wait_for_button_press_and_release(&button_action,&button_state); 
    if (stop_code==true){return;} //if stop_code==true; leave the entire setup() function
    digitalWrite(blue,LOW);
    digitalWrite(red,HIGH);
    digitalWrite(green,HIGH);
    
    move_cursor_to_end(); //press ctrl + end to make sure cursor is at the very end of the document, in case the user moved the cursor duing the pause
    Keyboard.println(F("Now press my pushbutton to see the RGB LED go through the whole rainbow, fading in and out of all of the colors!  Press the pushbutton "
                       "again to stop this demo and continue on."));
    stop_code = wait_for_button_press_and_release(&button_action,&button_state); 
    if (stop_code==true){return;} //if stop_code==true; leave the entire setup() function
    
    move_cursor_to_end(); //press ctrl + end to make sure cursor is at the very end of the document, in case the user moved the cursor duing the pause
    Keyboard.println(F("Rainbow ON.\n"
                       "The color progression is RED --> (YELLOW) --> GREEN --> (CYAN) --> BLUE --> (MAGENTA) --> RED\n"));
    
    digitalWrite(green,LOW); //turn off green
    //Perform action until button is pressed again
    stop_code = do_this_action_until_button_pressed_then_wait_for_release(&button_action,&button_state,make_rainbow);
    if (stop_code==true){return;} //if stop_code==true; leave the entire setup() function
    digitalWrite(red,LOW);
    digitalWrite(green,LOW);
    digitalWrite(blue,LOW);
    
    move_cursor_to_end(); //press ctrl + end to make sure cursor is at the very end of the document, in case the user moved the cursor duing the pause
    Keyboard.println(F("Rainbow OFF\n"));
  #elif SKIP_RGBLED_DEMO==1
    Keyboard.println(F("\nSkipping really cool RGB LED (multi-color light) demos since there are too many demos to fit on the Arduino all at one "
                       "time.  Compile & run the other main demo code to see any skipped demos!\n"));
  #endif
  
  #if SKIP_TEMPSENSOR_DEMO!=1
    //------------------------------------------------------------------------------------------------------------------------------------------
    //Temp Sensor
    //------------------------------------------------------------------------------------------------------------------------------------------
    Keyboard.println(F("Whew! Is it hot in here or just me? :) My microprocessor seems to be getting all worked up over the excitement of all the cool things I can do! Let's check "
                      "the room temp. w/my TMP36 analog temperature sensor (thermometer).  Gently squeeze the sensor w/your fingers to watch the temp. rise!\n"));
    Keyboard.println(press_to_continue_press_and_HOLD_to_stop_str);    
                   
    stop_code = wait_for_button_press_and_release(&button_action,&button_state); 
    if (stop_code==true){return;} //if stop_code==true; leave the entire setup() function
    
    move_cursor_to_end(); //press ctrl + end to make sure cursor is at the very end of the document, in case the user moved the cursor duing the pause
    Keyboard.println(F("Thermometer ON."));
                      
    //Perform action until button is pressed again
    stop_code = do_this_action_until_button_pressed_then_wait_for_release(&button_action,&button_state,printTemp);
    if (stop_code==true){return;} //if stop_code==true; leave the entire setup() function
    
    move_cursor_to_end(); //press ctrl + end to make sure cursor is at the very end of the document, in case the user moved the cursor duing the pause
    Keyboard.println(F("Thermometer OFF.\n"));
    Keyboard.println(F("Cool stuff, let's keep going!\n"
                       "(Press the pushbutton to continue).\n"));
                       
    stop_code = wait_for_button_press_and_release(&button_action,&button_state); 
    if (stop_code==true){return;} //if stop_code==true; leave the entire setup() function
  #elif SKIP_TEMPSENSOR_DEMO==1
    Keyboard.println(F("\nSkipping TMP36 analog temperature sensor (thermometer) demo since there are too many demos to fit on the Arduino all at one "
                       "time.  Compile & run the other main demo code to see any skipped demos!\n"));
  #endif

  #if SKIP_SERVO_DEMO!=1 //a Compiler Directive used to disable portions of code to save memory
    //------------------------------------------------------------------------------------------------------------------------------------------
    //Servo (controlled by potentiometer)
    //-you will likely have to use bit-banging due to conflicts with Timer1 between Servo.h and toneAC.h --> WRONG! I ended up copying and modifying 
    //the Servo library instead, starting w/these instructions here (http://www.pololu.com/docs/0J57/8.b).  Now, I am using the modified servo library
    //now called "Servo_32U4_Timer3.h" (see my notes about it at the very top of this code, near the #include statement for it).
    //------------------------------------------------------------------------------------------------------------------------------------------
    //prepare to use servo
    myservo.attach(servoPin);
  
    move_cursor_to_end(); //press ctrl + end to make sure cursor is at the very end of the document, in case the user moved the cursor duing the pause
    Keyboard.println(F("One of the really cool things about Arduino is how useful it is in robotics! For this demo, turn the blue potentiometer knob to control the servo."));
    Keyboard.println(press_to_continue_press_to_stop_str);         
                       
    stop_code = wait_for_button_press_and_release(&button_action,&button_state); 
    if (stop_code==true){return;} //if stop_code==true; leave the entire setup() function
    move_cursor_to_end(); //press ctrl + end to make sure cursor is at the very end of the document, in case the user moved the cursor duing the pause
    Keyboard.println(F("Servo control START."));
    //Perform action until button is pressed again
    stop_code = do_this_action_until_button_pressed_then_wait_for_release(&button_action,&button_state,driveServoWithPotentiometer);
    if (stop_code==true){return;} //if stop_code==true; leave the entire setup() function
    move_cursor_to_end(); //press ctrl + end to make sure cursor is at the very end of the document, in case the user moved the cursor duing the pause
    Keyboard.println(F("Servo control STOP.\n"));
    myservo.detach();
  #elif SKIP_SERVO_DEMO==1
    Keyboard.println(F("\nSkipping really cool servo (ex: robotic arm type actuator) demo since there are too many demos to fit on the Arduino all at "
                       "one time.  Compile & run the other main demo code to see any skipped demos!\n"));
  #endif //END OF CODE PORTION I AM MARKING TO *NOT* EXECTUTE
    
  #if SKIP_BUZZER_DEMO!=1
    //------------------------------------------------------------------------------------------------------------------------------------------
    //Piezo Buzzer: Mario Theme Songs!
    //------------------------------------------------------------------------------------------------------------------------------------------
    Keyboard.println(F("We are on the final demo!  I feel like we've really come close these past several minutes, you know, as we've learned together, "
                       "so what do you say I serenade you with some of my favorite classical music, using my piezo buzzer?\n\n"
                       
                       "There is no interaction required from you on this one; all you have to do is listen.  When the song is over, it will end automatically. "
                       "Can you guess which song it might be?  PS. before the music plays, I will do some sound sweeps, fast, then slow, to "
                       "demonstrate the range of notes I can play.\n\n"
                       
                       "(Press the pushbutton to continue)\n"));
                       
    stop_code = wait_for_button_press_and_release(&button_action,&button_state); 
    if (stop_code==true){return;} //if stop_code==true; leave the entire setup() function
    move_cursor_to_end(); //press ctrl + end to make sure cursor is at the very end of the document, in case the user moved the cursor duing the pause
    Keyboard.println(F("soundSweepFast START (To me, this sounds like the sound they make in cartoons when a character slips on a banana"));
    //Play mario music
    soundSweepFast();
    Keyboard.println(F("soundSweepFast END"));
    delay(1000);
    Keyboard.println(F("soundSweepSlow START"));
    soundSweepSlow();
    Keyboard.println(F("soundSweepSlow END"));
    delay(1000);
    Keyboard.println(F("serenadeYouWithBeautifulMusic START"));
    playMarioMusic();
    Keyboard.println(F("serenadeYouWithBeautifulMusic END"));
  #elif SKIP_BUZZER_DEMO==1
    Keyboard.println(F("\nSkipping some really sweet tunes and melodies, played out of my piezo buzzer, demo since there are too many demos to fit on the "
                       "Arduino all at one time.  Compile & run the other main demo code to see any skipped demos!\n"));
  #endif
  
  //------------------------------------------------------------------------------------------------------------------------------------------
  //END OF ALL DEMOS
  //------------------------------------------------------------------------------------------------------------------------------------------
  move_cursor_to_end(); //press ctrl + end to make sure cursor is at the very end of the document, in case the user moved the cursor duing the pause
  Keyboard.print(F("\nBefore you go, let me give you a proper introduction:  I am an Arduino microcontroller development platform.  "
                   "There are many types of Arduinos.  My type is called \"Leonardo\".  I am based on an Atmel ATmega32U4 microcontroller.  Today, in these demos, "
                   "you have seen only a *tiny* sample of what I can do.  I can do ANYTHING you tell me to do.  ANYTHING you program me to do.  "
                   "I can change the world.  I can change the way we live, but only if YOU make me do so.  Your students can change the world, they can "
                   "learn and grow and CREATE, and make it a better place, but only if YOU help them learn to do so.  Let's all *strive* to improve ourselves, "
                   "and remember that it is US who make up the world, and it is US who determine the destiny of the world.  Let us use our time wisely, share "
                   "our talents with each other, and become THINKERS *AND* DOERS, not just HEARERS.  \"Be a thinker, and be a doer.\"  That is my motto.\n\n"
                   "Sincerely,\n"
                   "Gabriel Staples\n\n"
                   "END OF DEMO.\nThanks for your time, "));
  //print out person's name
  for (byte i=0; i<sizeof(persons_name); i++)
  {
    Keyboard.print(persons_name[i]);
  }
  Keyboard.println(F(" :)."));
  Keyboard.println(F("\nThis program was created by Gabriel Staples (http://ElectricRCAircraftGuy.blogspot.com/), June 2014. \n"));
  
  //press ctrl + b to make next text BOLD
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press('b');
  delay(100);
  Keyboard.releaseAll();
  PROGMEM static const char text3[] = "I'm still watching you...:)\n\n";
  for (byte i=0; i<sizeof(text3); i++)
  {
    move_cursor_to_end(); //press ctrl + end to make sure cursor is at the very end of the document, in case the user moved the cursor duing the pause
    Keyboard.print(char(pgm_read_byte(&(text3[i]))));
    delay(350);
  }
  //press ctrl + b to *disable* bold from future text
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press('b');
  delay(100);
  Keyboard.releaseAll();
  
  //Save this file (ctrl + s, then enter)
  move_cursor_to_end(); //press ctrl + end to make sure cursor is at the very end of the document, in case the user moved the cursor duing the pause
  Keyboard.println(F("Saving file, please wait..."));
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press('s');
  delay(100);
  Keyboard.releaseAll();
  delay(2000); //give the save window time to open
  Keyboard.press(KEY_RETURN);
  delay(100);
  Keyboard.releaseAll();
  move_cursor_to_end(); //press ctrl + end to make sure cursor is at the very end of the document, in case the user moved the cursor duing the pause
  Keyboard.println(F("File Saved\n"));
  #if DEMO_NUMBER==1
    Keyboard.println(F("NEXT, GET HELP FROM THE INSTRUCTOR TO UPLOAD THE DEMO2 CODE AND BEGIN AGAIN TO SEE THE SKIPPED DEMOS."));
  #endif
  
} //end of setup()

//------------------------------------------------------------------------------------------------------------------------------------------
//loop()
//------------------------------------------------------------------------------------------------------------------------------------------
void loop()
{
  while (digitalRead(USB_emulationOn_pin) == HIGH) //do nothing until pin 2 goes low
  {
    //if pin is high, do this
    Keyboard.releaseAll();
    Keyboard.end();
    delay(50);
  }
  //the code will only get to this point if the USB_emulation_on_pin is pulled LOW by running a wire from it to GND
  
  delay(1000);
}


