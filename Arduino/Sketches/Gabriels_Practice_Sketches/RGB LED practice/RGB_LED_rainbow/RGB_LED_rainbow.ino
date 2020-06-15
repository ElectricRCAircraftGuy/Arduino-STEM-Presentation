//Gabriel Staples
//5 June 2014

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

  //make a rainbow
  //local variables
  unsigned int short_delay = 5; //ms; delay between changing of each PWM value
  unsigned int long_delay = 1; //ms; delay after each primary color, and principal mixed color (ie: red, green, blue, and yellow, cyan, magenta)
  //start with full red, and slowly add in green
  analogWrite(red,255);
  //here it is red
  delay(long_delay); //pause here to briefly show full red
  for (int i=0; i<256; i++)
  {
    analogWrite(green,i);
    delay(short_delay);
  }
  //once green is all added in, slowly subtract red
  //here it is yellow (red and green are full on)
  delay(long_delay); //pause here to briefly show full yellow
  //going down
  for (int i=255; i>=0; i--)
  {
    analogWrite(red,i);
    delay(short_delay);
  }
  //once red is all out, slowly add in blue
  //here it is green
  delay(long_delay); //pause here to briefly show full green
  //going up
  for (int i=0; i<256; i++)
  {
    analogWrite(blue,i);
    delay(short_delay);
  }
  //once blue is all in, slowly subtract green
  //here it is cyan (green and blue are full on)
  delay(long_delay); //pause here to briefly show full cyan
  //going down
  for (int i=255; i>=0; i--)
  {
    analogWrite(green,i);
    delay(short_delay);
  }
  //once green is all out, slowly add in red  
  //here it is blue
  delay(long_delay); //pause here to briefly show full blue
  //going up
  for (int i=0; i<256; i++)
  {
    analogWrite(red,i);
    delay(short_delay);
  }
  //once red is all in, slowly subtract blue
  //here it is magenta (blue and red are full on)
  delay(long_delay); //pause here to briefly show full magenta
  //going down
  for (int i=255; i>=0; i--)
  {
    analogWrite(blue,i);
    delay(short_delay);
  }
  //now, you are left with just red, so start back over

}



