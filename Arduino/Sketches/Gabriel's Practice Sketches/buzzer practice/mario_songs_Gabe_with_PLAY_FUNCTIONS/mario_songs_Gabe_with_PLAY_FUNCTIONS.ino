/*
  http://www.linuxcircle.com/2013/03/31/playing-mario-bros-tune-with-arduino-and-piezo-buzzer/
  Arduino Mario Bros Tunes
  With Piezo Buzzer and PWM
  by: Dipto Pratyaksa
  last updated: 31/3/13
*/

//Mario music courtesy of Dipto Pratyaksa, ported by Gabriel Staples to use the toneAC library, which provides extra clarity and volume over
//other techniques to make music using an Arduino and a piezo buzzer
//For additional demos & info on using a piezo buzzer, see here: http://arduino.cc/en/Tutorial/Tone

#include "pitches.h"
#include "mario_songs.h"
#include <toneAC.h> //connect buzzer to pins 9 & 10

//Global Variables
const byte volume = 4; //choose from 0 to 10

void setup()
{
}

void loop() 
{
  soundSweepFast();
  delay(1000);
  soundSweepSlow();
  delay(1000);
  playMarioMusic();
  while(1); // Stop (so it doesn't repeat forever driving you crazy--you're welcome).
}

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
  for (byte i=0; i<2; i++)
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








////Global Variables & Constants
//const byte melodyPin = 3;
////#define melodyPin 3
//
////------------------------------------------------------------------------------------------------------------------------------------------
////setup()
////------------------------------------------------------------------------------------------------------------------------------------------
//void setup()
//{
//   pinMode(3, OUTPUT);//buzzer
//   pinMode(13, OUTPUT);//led indicator when singing a note
//}
//
////------------------------------------------------------------------------------------------------------------------------------------------
////loop()
////------------------------------------------------------------------------------------------------------------------------------------------
//void loop()
//{
//  //sing the tunes
//  sing(1);
//  sing(1);
//  sing(2);
//}
//
////------------------------------------------------------------------------------------------------------------------------------------------
////sing
////------------------------------------------------------------------------------------------------------------------------------------------
//void sing(int s)
//{
//   //local variables
//   static int song = 0;
//   
//   // iterate over the notes of the melody:
//   song = s;
//   if(song==2){
//     Serial.println(" 'Underworld Theme'");
//     int size = sizeof(underworld_melody) / sizeof(int);
//     for (int thisNote = 0; thisNote < size; thisNote++) {
//
//       // to calculate the note duration, take one second
//       // divided by the note type.
//       //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
//       int noteDuration = 1000/underworld_tempo[thisNote];
//
//       buzz(melodyPin, underworld_melody[thisNote],noteDuration);
//
//       // to distinguish the notes, set a minimum time between them.
//       // the note's duration + 30% seems to work well:
//       int pauseBetweenNotes = noteDuration * 1.30;
//       delay(pauseBetweenNotes);
//
//       // stop the tone playing:
//       buzz(melodyPin, 0,noteDuration);
//
//    }
//
//   }else{
//
//     Serial.println(" 'Mario Theme'");
//     int size = sizeof(melody) / sizeof(int);
//     for (int thisNote = 0; thisNote < size; thisNote++) {
//
//       // to calculate the note duration, take one second
//       // divided by the note type.
//       //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
//       int noteDuration = 1000/tempo[thisNote];
//
//       buzz(melodyPin, melody[thisNote],noteDuration);
//
//       // to distinguish the notes, set a minimum time between them.
//       // the note's duration + 30% seems to work well:
//       int pauseBetweenNotes = noteDuration * 1.30;
//       delay(pauseBetweenNotes);
//
//       // stop the tone playing:
//       buzz(melodyPin, 0,noteDuration);
//
//    }
//  }
//}
//
////------------------------------------------------------------------------------------------------------------------------------------------
////buzz
////------------------------------------------------------------------------------------------------------------------------------------------
//void buzz(int targetPin, long frequency, long length) {
//  digitalWrite(13,HIGH);
//  long delayValue = 1000000/frequency/2; // calculate the delay value between transitions
//  //// 1 second's worth of microseconds, divided by the frequency, then split in half since
//  //// there are two phases to each cycle
//  long numCycles = frequency * length/ 1000; // calculate the number of cycles for proper timing
//  //// multiply frequency, which is really cycles per second, by the number of seconds to 
//  //// get the total number of cycles to produce
//  for (long i=0; i < numCycles; i++){ // for the calculated length of time...
//    digitalWrite(targetPin,HIGH); // write the buzzer pin high to push out the diaphram
//    delayMicroseconds(delayValue); // wait for the calculated delay value
//    digitalWrite(targetPin,LOW); // write the buzzer pin low to pull back the diaphram
//    delayMicroseconds(delayValue); // wait again or the calculated delay value
//  }
//  digitalWrite(13,LOW);
//}

