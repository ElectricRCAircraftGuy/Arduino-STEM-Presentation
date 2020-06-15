// Controlling a servo position using a potentiometer (variable resistor) 
// by Michal Rinott <http://people.interaction-ivrea.it/m.rinott> 

//#include <Servo.h> 
#include <Servo_32U4_Timer3.h> //This is a modified version of the main Arduino "Servo" library.  I have simply made a few minor changes to force
                               //the library to use the Leonardo's/(any board w/a 32U4 microcontroller)'s Timer3 instead of Timer1. 
			       //I got the idea from the instructions found here: http://www.pololu.com/docs/0J57/8.b
			       //~Gabriel Staples, http://electricrcaircraftguy.blogspot.com/
 
Servo_32U4_Timer3 myservo;  // create servo object to control a servo 
 
int potpin = 0;  // analog pin used to connect the potentiometer
int val;    // variable to read the value from the analog pin 
 
void setup() 
{ 
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object 
} 
 
void loop() 
{ 
  val = analogRead(potpin);            // reads the value of the potentiometer (value between 0 and 1023) 
  val = map(val, 0, 1023, 0, 179);     // scale it to use it with the servo (value between 0 and 180) 
  myservo.write(val);                  // sets the servo position according to the scaled value 
  delay(15);                           // waits for the servo to get there 
} 
