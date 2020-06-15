//sketch 06-08

int outputPin = 3;


void setup()
{
  pinMode(outputPin, OUTPUT);
  Serial.begin(115200);
  while (!Serial){} //If using an Arduino Leonardo or equivalent, wait until the serial port 
                    //is ready so that the following statement is not missed by the Serial Monitor
  
  /////////////////////////////////////////////////////////////////////////////////
  //USER *MUST* INPUT A CHAR ON THE SERIAL PORT BEFORE THE PROGRAM WILL BEGIN!!!!//
  /////////////////////////////////////////////////////////////////////////////////
  
  //wait for the user to input any character to begin the program               
  while (Serial.available()<=0){}
  //flush the serial input buffer of the just entered character(s)
  while (Serial.available()>0){
    Serial.read();
  }
  Serial.println("Enter Volts 0 to 5");
}


void loop()
{
  if (Serial.available() > 0)
  {
//    char ch = Serial.read();
//    int volts = (ch - '0') * 51;
//    analogWrite(outputPin, volts);

    float V_des = Serial.parseFloat(); //V
    uint8_t command = V_des*51.0; //V; truncated to uint8_t
    float V_com = command*5.0/255.0; //Voltage actually commanded, based on truncation above, & resolution of analogWrite
    Serial.print("V_des = ");
    Serial.print(V_des,4);
    Serial.print(", PWM command = ");
    Serial.print(command);
    Serial.print(" or ");
    Serial.print(command,4); //<--------NOTE: THIS PRODUCES STRANGE OUTPUT, W/4 #S INSTEAD OF 3 AT TIMES (EX: 34-->344 OR SOMETHING)
                             //I *THINK* that what *may* be happening, is when I specify the precision, it forces Serial.print to interpret
                             //the "command" value as a 4-byte float instead of a 1-byte uint8_t.
    Serial.print(", V_commanded = ");
    Serial.println(V_com,4);
    analogWrite(outputPin,command);
  }
}
