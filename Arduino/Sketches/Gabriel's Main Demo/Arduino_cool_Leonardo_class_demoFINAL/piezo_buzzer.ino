
/*
  http://www.linuxcircle.com/2013/03/31/playing-mario-bros-tune-with-arduino-and-piezo-buzzer/
  Arduino Mario Bros Tunes
  With Piezo Buzzer and PWM
  by: Dipto Pratyaksa
  last updated: 31/3/13
*/

//Mario music courtesy of Dipto Pratyaksa (see link above), ported by Gabriel Staples to use the toneAC library, which provides extra clarity and volume over
//other techniques to make music using an Arduino and a piezo buzzer
//Gabriel Staples, 13 June 2014, http://electricrcaircraftguy.blogspot.com/

#if SKIP_BUZZER_DEMO!=1
  //------------------------------------------------------------------------------------------------------------------------------------------
  //soundSweepFast()
  //------------------------------------------------------------------------------------------------------------------------------------------
  void soundSweepFast()
  {
    //play intro sound sweep (like a cartoon "slipping" sound)
    for (unsigned long freq = 125; freq <= 15000; freq += 10) {  
      toneAC(freq, volume); // Play the frequency (125 Hz to 15 kHz sweep in 10 Hz steps).
      delay(1);     // Wait __ ms so you can hear it.
    }
  }
  
  //------------------------------------------------------------------------------------------------------------------------------------------
  //soundSweepSlow()
  //------------------------------------------------------------------------------------------------------------------------------------------
  void soundSweepSlow()
  {
    //play intro sound sweep (like a cartoon "slipping" sound)
    for (unsigned long freq = 125; freq <= 15000; freq += 10) {  
      toneAC(freq, volume); // Play the frequency (125 Hz to 15 kHz sweep in 10 Hz steps).
      delay(20);     // Wait __ ms so you can hear it.
    }
  }
  
  //------------------------------------------------------------------------------------------------------------------------------------------
  //playMarioMusic()
  //------------------------------------------------------------------------------------------------------------------------------------------
  void playMarioMusic()
  {
    //local variables & constants
    unsigned int melody_length; 
    
  //  //play intro sound sweep (like a cartoon "slipping" sound)
  //  for (unsigned long freq = 125; freq <= 15000; freq += 10) {  
  //    toneAC(freq, volume); // Play the frequency (125 Hz to 15 kHz sweep in 10 Hz steps).
  //    delay(1);     // Wait __ ms so you can hear it.
  //  }
    toneAC(); // Turn off toneAC, can also use noToneAC().
    delay(1000); // Wait a second.
  
    //play mario theme song twice in a row
    melody_length = sizeof(melody)/sizeof(int);
    for (byte i=0; i<2; i++) //play twice
    {
      for (int thisNote = 0; thisNote < melody_length; thisNote++) 
      {
        int noteDuration = 1000/tempo[thisNote]*4/3; //5/4;
        toneAC(melody[thisNote], volume, noteDuration, true); // Play thisNote at full volume for noteDuration in the background.
        delay(noteDuration * 4 / 3); // Wait while the tone plays in the background, plus another 33% delay between notes.
      }
    }
    
    //play mario underworld song
    melody_length = sizeof(underworld_melody)/sizeof(int);
    for (int thisNote = 0; thisNote < melody_length; thisNote++) 
    {
      int noteDuration = 1000/underworld_tempo[thisNote]*4/3;
      toneAC(underworld_melody[thisNote], volume, noteDuration, true); // Play thisNote at full volume for noteDuration in the background.
      delay(noteDuration * 4 / 3); // Wait while the tone plays in the background, plus another 33% delay between notes.
    }
  }
#endif
