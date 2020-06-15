//autoscroll_really_long_phrase
//By Gabriel Staples
//23 April 2014

//include the library code:
#include <LiquidCrystal.h>

//initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7,8,9,10,11,12);

//Global Variables & Constants
char long_str[] =   "Hi, I would like to tell you a bit about myself. "
                    "My name is Gabriel Staples, and I like to fly RC airplanes. "
                    "My contact info is ____.";
uint8_t str_len = sizeof(long_str);
const uint8_t lcd_cols = 20; //# of characters (& columns) that can fit accross the display (usu. 16 or 20)
char str_buffer[lcd_cols + 1]; //create an empty string buffer equal to the length of the display, + 1 for the mandatory character array null terminator

void setup()
{
  str_buffer[lcd_cols + 1] = '\0'; //add in the mandatory null terminator
    //Note: if you do *not* do the line above, you will break the .print & .write functions where you print this variable (ex: Serial.print(str_buffer) & lcd.write(str_buffer),
    //etc.  See here: "Generally, strings are terminated with a null character (ASCII code 0). This allows functions (like Serial.print()) to tell where the end of a
    //string is. Otherwise, they would continue reading subsequent bytes of memory that aren't actually part of the string."
    //For more info read here, under the "Null termination" section for the "string" reference page: file:///C:/Program%20Files%20(x86)/Arduino/reference/String.html 
  lcd.begin(20,4);
  lcd.print("Str_len: "); 
  lcd.print(str_len);
  delay(2000);
}


void loop()
{
   static unsigned int i = 0; //string index
   static uint8_t first_itn = true;
   //fill the string buffer that hold one line of characters for the LCD display
   for (int j=0; j < lcd_cols; j++)
   {
     if ((i+j)<(str_len-1)) //the -1 is so I don't print the end-of-string character
     {
       //if I'm not at the end of the long_str yet
       str_buffer[j] = long_str[i+j]; //fill buffer
     }
     else
     {
       //I have reached the end of the long_str
       str_buffer[j] = ' '; //fill with an empty space
     }
   }
   lcd.clear();
   
   //print out the data to the lcd display
   lcd.write(str_buffer);
   if (first_itn){
     delay(1000); //provide extra time to read the first line
     first_itn = false;
   }   
   i++;
   if (i >= (str_len-1)) //the -1 is so I don't print the end-of-string character (null terminator)
   { 
     //if the whole long string is done printing
     i = 0; //reset
     lcd.clear();
     delay(1000);
     first_itn = true; //reset
   }
   else
   {
     delay(150);
   }
}
