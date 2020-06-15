//autoscroll_really_long_phrase
//By Gabriel Staples
//23 April 2014

//12 May 2014: sketch size withOUT PROGMEM: 6936 bytes Flash, 524 bytes RAM
//             sketch size WITH PROGMEM: 6930 bytes Flash, 330 bytes RAM (note: RAM now uses 194 bytes less, which is exactly equal to the length of the "long_str" below!)

// include the library code:
#include <Wire.h>
#include <Adafruit_MCP23017.h>
#include <Adafruit_RGBLCDShield.h>

// The shield uses the I2C SCL and SDA pins. On classic Arduinos
// this is Analog 4 and 5 so you can't use those for analogRead() anymore
// However, you can connect other I2C sensors to the I2C bus and share
// the I2C bus.
//Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();
Adafruit_RGBLCDShield lcd; //alternate way to do the above line ~GS

// These #defines make it easy to set the backlight color
#define RED 0x1
#define YELLOW 0x3
#define GREEN 0x2
#define TEAL 0x6
#define BLUE 0x4
#define VIOLET 0x5
#define WHITE 0x7

//Global Variables & Constants
PROGMEM char long_str[] = "Hi, I would like to tell you a bit about myself. "
                          "My name is Gabriel Staples, and I like to fly RC airplanes. "
                          "I also really enjoy Arduino microcontroller programming. It is a VERY powerful tool!";
uint8_t str_len = sizeof(long_str); //194 bytes last I checked on 12 May 2014
const uint8_t lcd_cols = 16; //# of characters (& columns) that can fit accross the display (usu. 16 or 20)
const uint8_t lcd_rows = 2; //# of rows (usu. 2 or 4)
char str_buffer[lcd_cols + 1]; //create an empty string buffer equal to the length of the display, + 1 for the mandatory character array null terminator


void setup()
{
  str_buffer[lcd_cols] = '\0'; //add in the mandatory null terminator
  //Note: if you do *not* do the line above, you will break the .print & .write functions where you print this variable (ex: Serial.print(str_buffer) & lcd.write(str_buffer),
  //etc.  See here: "Generally, strings are terminated with a null character (ASCII code 0). This allows functions (like Serial.print()) to tell where the end of a
  //string is. Otherwise, they would continue reading subsequent bytes of memory that aren't actually part of the string."
  //For more info read here, under the "Null termination" section for the "string" reference page: file:///C:/Program%20Files%20(x86)/Arduino/reference/String.html
  lcd.begin(lcd_cols, lcd_rows);
  lcd.print("Str_len: ");
  lcd.print(str_len);
  delay(2000);
  lcd.clear(); //clear display
  lcd.setCursor(0, 1); //first column, second row
  lcd.print("Time(sec):");
}


void loop()
{
  static unsigned int t_delay = 0; //ms; delay time between prints; 
    //I want to use a more sophisticated method to delay so that I can still quickly read the push-buttons on the LCD display
  static unsigned long t_start = millis(); //ms; time since last print to lcd
  static unsigned long last_sec = millis()/1000; //sec; the last time stamp since the second counter on the LCD was updated 
  
  if (millis()-t_start >= t_delay){
    //if adequate delay time has elapsed, update the LCD
    t_delay = printString(); //print the string & get the new delay time, t_delay, in ms
    t_start = millis(); //ms; time since last print to lcd
  }
  
  //display the time elapsed on the second row of the LCD
  //update only if necessary (ie: if the second has changed)
  unsigned long sec_now = millis()/1000; //sec; time stamp now
  if (sec_now > last_sec){
    lcd.setCursor(11, 1);
    lcd.print(sec_now);
    last_sec = sec_now; //sec; update
  }

  //read buttons, & set backlight color according to the button that is pressed
  uint8_t buttons = lcd.readButtons();
  if (buttons != 0) //one or more buttons are pressed
  {
    //set background colors according to the buttons
    if (buttons & BUTTON_UP) {
      lcd.setBacklight(RED);
    }
    if (buttons & BUTTON_DOWN) {
      lcd.setBacklight(YELLOW);
    }
    if (buttons & BUTTON_LEFT) {
      lcd.setBacklight(GREEN);
    }
    if (buttons & BUTTON_RIGHT) {
      lcd.setBacklight(TEAL);
    }
    if (buttons & BUTTON_SELECT) {
      lcd.setBacklight(VIOLET);
    }
    if (((buttons & BUTTON_UP) != 0) && ((buttons & BUTTON_DOWN) != 0)) { //Both Up AND Down are pressed simultaneously
      lcd.setBacklight(WHITE);
    }
  }
  
} //end of loop()


void clearTopRow()
{
  lcd.home();
  lcd.print(F("                ")); //16 blank spaces, + automatic null terminator at end, to clear one line on a 16 column display
}


//function to print the string, scrolling accross the display
unsigned int printString()
{
  //local variables
  static unsigned int i = 0; //string index
  static uint8_t first_itn = true;
  unsigned int t_delay; //ms; delay time

  //fill the string buffer that hold one line of characters for the LCD display
  for (int j = 0; j < lcd_cols; j++)
  {
    if ((i + j) < (str_len - 1)) //the -1 is so I don't print the end-of-string character
    {
      //if I'm not at the end of the long_str yet
      str_buffer[j] = pgm_read_byte(&(long_str[i + j])); //fill buffer
    }
    else
    {
      //I have reached the end of the long_str
      str_buffer[j] = ' '; //fill with an empty space
    }
  }

  //print out the data to the lcd display
  lcd.setCursor(0, 0); //same as lcd.home();
  lcd.print(str_buffer);

  //increment string buffer index; must be done BEFORE calculating delays, since I also reset i in that area
  i++;

  //Calculate Delays
  //if we have just printed the whole thing
  if (i >= (str_len - 1)) //the -1 is so I don't print the end-of-string character (null terminator)
  {
    //if the whole long string is done printing
    i = 0; //reset
    clearTopRow();
    t_delay = 1000; //ms; provide extra time for the reader to see that the string is at the very end, and is about to reset back to the beginning
    first_itn = true; //reset
  }
  else if (first_itn) {
    t_delay = 1000; //ms; provide extra time to read the first line
    first_itn = false;
  }
  else
  {
    t_delay = 100; //ms; the normal delay between each reprint to the LCD screen (ie: between "scrollings" of characters)
  }
  
  return t_delay; //ms
}



