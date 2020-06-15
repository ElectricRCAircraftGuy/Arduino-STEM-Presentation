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

#if SKIP_RANGEFINDER_DEMO!=1
  //------------------------------------------------------------------------------------------------------------------------------------------
  //getDistance()
  //-gets a distance reading from the ultrasonic rangefinder ("ping" sensor), using a median filter on ___ raw samples
  //------------------------------------------------------------------------------------------------------------------------------------------
  void getDistance(unsigned int* p_t_ping, float* p_dist_in, float* p_dist_ft, byte num_samples_to_take)
  {
    *p_t_ping = sonar.ping_median(num_samples_to_take); //us; GS: the *median* ping time after conducting __ # of pings; this is the application of a basic non-linear median filter!
                                                //Note: a value of 65,535 us corresponds to a value of ~73 ft, which is waaaay farther than the max range of this thing, of ~16.4 ft (5m), so
                                                //an unsigned int (0-65535) is easily large enough
    *p_dist_in = *p_t_ping/MICROSECONDS_PER_INCH/2.0; //in; distance; divide by 2 since the ultrasonic wave must travel there AND back, which is 2x the distance you are measuring
    *p_dist_ft = *p_dist_in/12.0; //ft; distance
  }
#endif

