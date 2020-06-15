
#if SKIP_SERVO_DEMO != 1 //a Compiler Directive used to disable portions of code to save memory
  //copied from the "knob" example that comes with the main, Arduino-supported Servo library
  void driveServoWithPotentiometer()
  {
    unsigned int val = analogRead(potPin);            // reads the value of the potentiometer (value between 0 and 1023) 
    val = map(val, 0, 1023, 0, 179);     // scale it to use it with the servo (value between 0 and 180) 
    myservo.write(val);                  // sets the servo position according to the scaled value 
    delay(15);                           // waits for the servo to get there 
  }
#endif
