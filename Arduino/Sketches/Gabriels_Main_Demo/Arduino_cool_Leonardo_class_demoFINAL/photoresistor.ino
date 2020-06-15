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
//get_avg_of_50_light_readings()
//------------------------------------------------------------------------------------------------------------------------------------------
unsigned int get_avg_of_50_light_readings()
{
  //take and average 50 light readings, but throw out the first value
  analogRead(photoPin); //throw out first value
  unsigned long light_reading_sum = 0; //initialize
  for (int i=0; i<50; i++) //take 50 readings: each reading will be from 0-1023 max
  {
    light_reading_sum += analogRead(photoPin);
  }
  //get avg
  unsigned int avg_light_reading = light_reading_sum/50.0;
  return avg_light_reading;
}
