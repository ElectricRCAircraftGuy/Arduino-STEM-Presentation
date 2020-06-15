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
//move_cursor_to_end()
//------------------------------------------------------------------------------------------------------------------------------------------
void move_cursor_to_end()
{
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_END);
  delay(100);
  Keyboard.releaseAll();
}

//------------------------------------------------------------------------------------------------------------------------------------------
//open_and_configure_MSWord
//------------------------------------------------------------------------------------------------------------------------------------------
void open_and_configure_MSWord()
{
  //open MSWord
  //press Windows + r to open up the "run" command window
  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.press('r');
  delay(100);
  Keyboard.releaseAll();
  //type "winword" and press enter (this is the new-line character)
  Keyboard.println("winword");
  //give MS Word 7.5 seconds to open; INCREASE THIS VALUE IF WORD DOESN'T OPEN IN TIME!!!
  delay(7500);
  
  //Maximize the screen with alt + space, then "x"
  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press(' '); //space
  delay(100);
  Keyboard.releaseAll();
  Keyboard.print('x');
  
  setDefaultFontSettings();
  setDefaultParagraphSettings();
}

//------------------------------------------------------------------------------------------------------------------------------------------
//setDefaultFontSettings()
//------------------------------------------------------------------------------------------------------------------------------------------
void setDefaultFontSettings()
{
  //Configure Font settings
  //Right click and go to "f" to access the Font settings.  Using the keyboard only, do this by pressing Shift + F10, then "f"
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.press(KEY_F10);
  delay(100);
  Keyboard.releaseAll();
  Keyboard.print('f');
  delay(1000);
  //type in "times new roman" then press alt + s to go to the Size menu, and type "12"
  Keyboard.print(F("times new roman"));
  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press('s');
  delay(100);
  Keyboard.releaseAll();
  Keyboard.print("12");
  //press tab 15 times to get to the "ok" button, then press enter
  for (byte i=0; i<15; i++)
  {
    Keyboard.press(KEY_TAB);
    delay(100);
    Keyboard.releaseAll();
    delay(100);
  }
  Keyboard.press(KEY_RETURN);
  delay(100);
  Keyboard.releaseAll();
  //just in case we are in the wrong menu at this time, due to an alternate version of MSWord or something, hit Escape now to exit any extraneous menus we may
  //accidentally be in
  Keyboard.press(KEY_ESC);
  delay(100);
  Keyboard.releaseAll();
}

//------------------------------------------------------------------------------------------------------------------------------------------
//setDefaultParagraphSettings()
//------------------------------------------------------------------------------------------------------------------------------------------
void setDefaultParagraphSettings()
{
  //Configure Paragraph settings
  //press shift + F10 to get the "right-click" menu; then press "p" twice, and press enter
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.press(KEY_F10);
  delay(100);
  Keyboard.releaseAll();
  Keyboard.println("pp");
  //press alt + b to go to the spacing "before" box; then type a zero
  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press('b');
  delay(100);
  Keyboard.releaseAll();
  Keyboard.print(0);
  //press alt + f to go to the spacing "after" box; then type a zero
  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press('f');
  delay(100);
  Keyboard.releaseAll();
  Keyboard.print(0);
  //press alt + n to go to the "Line spacing" box; then type "s" for single, 
  //then enter to select "single" line spacing, then enter again to leave the menu
  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press('n');
  delay(100);
  Keyboard.releaseAll();
  Keyboard.print("s");
  Keyboard.press(KEY_RETURN);
  delay(100);
  Keyboard.releaseAll();
  delay(100);
  Keyboard.press(KEY_RETURN);
  delay(100);
  Keyboard.releaseAll();
  //just in case we are in the wrong menu at this time, due to an alternate version of MSWord or something, hit Escape now to exit any extraneous menus we may
  //accidentally be in
  Keyboard.press(KEY_ESC);
  delay(100);
  Keyboard.releaseAll();
}

//------------------------------------------------------------------------------------------------------------------------------------------
//setFontColor
//------------------------------------------------------------------------------------------------------------------------------------------
void setFontColor(byte red, byte green, byte blue)
{
//  //local variables
//  static boolean first_time = true;
  
  //press ctrl + shift + f to open Font settings
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.press('f');
  delay(100);
  Keyboard.releaseAll();
  delay(100);
  //alt + c to chance color
  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press('c');
  delay(100);
  Keyboard.releaseAll();
  //m for more colors
  Keyboard.print('m');
//  if (first_time)
//  {
    //right arrow for custom colors; 
    //<---NOTE: THIS IS ONLY NECESSARY THE *FIRST* TIME YOU SET A COLOR!!! ---maybe not; commenting out this if statement....
    Keyboard.press(KEY_RIGHT_ARROW);
    delay(100);
    Serial.println("first time");
    Keyboard.releaseAll();
//    first_time = false; //update
//  }
  //set red color
  //alt + r, then type value from 0-255 to set red color
  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press('r');
  delay(100);
  Keyboard.releaseAll();
  Keyboard.print(red);
  //set green color
  //alt + g, then type value from 0-255 to set red color
  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press('g');
  delay(100);
  Keyboard.releaseAll();
  Keyboard.print(green);
  //set blue color
  //alt + b, then type value from 0-255 to set red color
  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press('b');
  delay(100);
  Keyboard.releaseAll();
  Keyboard.print(blue);
  //enter, tab, enter to leave menu
  Keyboard.press(KEY_RETURN);
  delay(100);
  Keyboard.releaseAll();
  Keyboard.press(KEY_TAB);
  delay(100);
  Keyboard.releaseAll();
  Keyboard.press(KEY_RETURN);
  delay(100);
  Keyboard.releaseAll();
  //just in case we are in the wrong menu at this time, due to an alternate version of MSWord or something, hit Escape now to exit any extraneous menus we may
  //accidentally be in
  Keyboard.press(KEY_ESC);
  delay(100);
  Keyboard.releaseAll();
}

//=========================================================================================================================================
//=========================================================================================================================================

//------------------------------------------------------------------------------------------------------------------------------------------
//random_mouse_slide_around
//------------------------------------------------------------------------------------------------------------------------------------------
void random_mouse_slide_around()
{
  //Grab a couple random values approximately equal to +/- half the screen resolution size, since experimental tests show that for my specific mouse settings,
  //I get approximately 2 pixels of movement per 1 unit of command in the Mouse.move() command, and I want the dx_full or dy_full value to have the ability to
  //move the mouse across the entire screen, from one side to the other, Left to Right (dx_full), or Top to Bottom (dy_full).
//    int dx_full = random(-800,800);
//    int dy_full = random(-450,450);
  //test with smaller values
  int dx_full = random(-800/2,800/2);
  int dy_full = random(-450/2,450/2);
  
  //determine which is larger, dx_full or dy_full
  int large, small;
  boolean large_dx;  //is the large val dx?
  if (abs(dx_full) > abs(dy_full)){ //dx is larger
    large = dx_full;
    large_dx = true;
    small = dy_full;
  }
  else{ //dy is larger
    large = dy_full;
    large_dx = false;
    small = dx_full;
  }
  
  int sign_dx, sign_dy; //+ or -
  if (dx_full < 0) { //dx_full is neg
    sign_dx = -1;
  }
  else{
    sign_dx = 1;
  }
  if (dy_full < 0) { //dy_full is neg
    sign_dy = -1;
  }
  else{
    sign_dy = 1;
  }
  
  int j = 0; //counter
  int dx, dy; //mouse movement increments per j iteration
  for (int i=0; i < abs(large); i++)
  {
    if (large_dx == true){
      dx = sign_dx;
      if (j < abs(small)){
        dy = sign_dy;
      }
      else {
        dy = 0;
      }
    }
    else { //large value is dy
      dy = sign_dy;
      if (j < abs(small)){
        dx = sign_dx;
      }
      else {
        dx = 0;
      }
    }
    j++;
    
    Mouse.move(dx,dy,0);
  }  
}

//------------------------------------------------------------------------------------------------------------------------------------------
//random_mouse_jump_around
//------------------------------------------------------------------------------------------------------------------------------------------
void random_mouse_jump_around()
{
  Mouse.move(random(-800,800),random(-450,450),0);
}

//------------------------------------------------------------------------------------------------------------------------------------------
//random_mouse_buzz_around
//------------------------------------------------------------------------------------------------------------------------------------------
void random_mouse_buzz_around()
{
  Mouse.move(random(-10,11),random(-10,11),0);
}

//------------------------------------------------------------------------------------------------------------------------------------------
//draw_squares_with_mouse_movements
//------------------------------------------------------------------------------------------------------------------------------------------
//draw_squares_with_mouse_movements
//Note: the square_side_length is in units of "mouse movement command increments."  You cannot put this into pixels directly, as each individual computer will
//have different mouse settings (ex: sensitivity, speed, acceleration, etc), which affect how the mouse cursor actually responds to these mouse movement commands.
//Let's use clockwise rotation of the mouse movements in the square shape
void draw_squares_with_mouse_movements()
{
  //local variables or constants
  const unsigned int square_side_length = 100;
  
  //Top edge: Left to Right
  for (unsigned int i=0; i<square_side_length; i++)
  {
    Mouse.move(1,0,0);
  }
  //Right edge: Top to Bottom
  for (unsigned int i=0; i<square_side_length; i++)
  {
    Mouse.move(0,1,0);
  }
  //Bottom edge: Right to Left
  for (unsigned int i=0; i<square_side_length; i++)
  {
    Mouse.move(-1,0,0);
  }
  //Left edge: Bottom to Top
  for (unsigned int i=0; i<square_side_length; i++)
  {
    Mouse.move(0,-1,0);
  }
}

//------------------------------------------------------------------------------------------------------------------------------------------
//mouse_move_to_lower_left_of_screen
//------------------------------------------------------------------------------------------------------------------------------------------
void mouse_move_to_lower_left_of_screen()
{
  //local variables or constants
  const unsigned int delay_us = 10000; //us
  
  Mouse.move(-1,1,0); 
  delayMicroseconds(delay_us); //delay this # of microseconds (us) before repeating; use higher "delay_ms" value to slow down the mouse movement, lower value to speed it up
}

//------------------------------------------------------------------------------------------------------------------------------------------
//printString
//------------------------------------------------------------------------------------------------------------------------------------------
void printString(char* string,unsigned int str_length,unsigned int delay_ms)
{
  for (byte i=0; i<str_length; i++)
  {
    Keyboard.print(string[i]);
    delay(delay_ms);
  }
}

