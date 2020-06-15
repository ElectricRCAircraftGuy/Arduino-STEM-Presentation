// ---------------------------------------------------------------------------
// Example NewPing library sketch that does a ping about 20 times per second.
// ---------------------------------------------------------------------------

//tested by Gabriel Staples on 10 June 2014

#include <NewPing.h> //GS: this is for the ultrasonic rangefinder; note: this library uses the ATmega328 Timer2, thereby disabling Arduino PWM outputs on Pins 3 & 11 when NewPing is in use

#define TRIGGER_PIN  12  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     11  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 500 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

//Global variables or constants
const float MICROSECONDS_PER_INCH = 74.6422; //us per inch; sound traveling through air at sea level ~GS

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

void setup() 
{
  Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.
}

void loop() 
{
  delay(50); // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  
//  unsigned int t_ping = sonar.ping(); //us; ping time; note: 0 means the distance is outside of set distance range (MAX_DISTANCE)
  unsigned int t_ping = sonar.ping_median(5); //us; the *median* ping time after conducting __ # of pings; this is the application of a basic non-linear median filter!
  float dist_in = t_ping/MICROSECONDS_PER_INCH/2.0; //in; distance; divide by 2 since the ultrasonic wave must travel there AND back, which is 2x the distance you are measuring
  float dist_ft = dist_in/12.0; //ft; distance
  
  Serial.print("Ping(us) = "); Serial.print(t_ping); Serial.print(", dist(in) = "); Serial.print(dist_in); Serial.print(", dist(ft) = "); Serial.println(dist_ft);
  
}
