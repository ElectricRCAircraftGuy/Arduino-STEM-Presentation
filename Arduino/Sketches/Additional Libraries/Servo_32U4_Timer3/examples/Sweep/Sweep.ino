// Sweep
// by BARRAGAN <http://barraganstudio.com> 
// This example code is in the public domain.


//#include <Servo.h> 
#include <Servo_32U4_Timer3.h> //This is a modified version of the main Arduino "Servo" library.  I have simply made a few minor changes to force
                               //the library to use the Leonardo's/(any board w/a 32U4 microcontroller)'s Timer3 instead of Timer1. 
			       //I got the idea from the instructions found here: http://www.pololu.com/docs/0J57/8.b
			       //~Gabriel Staples, http://electricrcaircraftguy.blogspot.com/
 
Servo_32U4_Timer3 myservo;  // create servo object to control a servo 
                // a maximum of eight servo objects can be created 
 
int pos = 0;    // variable to store the servo position 
 
void setup() 
{ 
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object 
} 
 
 
void loop() 
{ 
  for(pos = 0; pos < 180; pos += 1)  // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    myservo.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
  } 
  for(pos = 180; pos>=1; pos-=1)     // goes from 180 degrees to 0 degrees 
  {                                
    myservo.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
  } 
} 
