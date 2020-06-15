// Code by Jody Biggs / May 2013

int triggerPin = 2;
int echoPin = 3;

// Distance = ((Duration of high level)*(Sonic :340m/s))/2
// => Distance = HIGH duration in us * 170 / 1000000
// 340 m/s is an approximation, but a pretty good one.
// 0% humidity air at 15C (or ~60F) has sound of speed at 340.29 m/s
// going up or down 10 degrees C changes speed of sound by +/- ~3 m/s
float measure_distance()
{
  // trigger the ultrasonic range finder by setting trigger to HIGH
  // for at least 10us
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);

  // wait for echoPin to go HIGH, and read how long (in microseconds)
  // it remains HIGH. Time out at 100ms (i.e. 100k microseconds)
  long duration = pulseIn(echoPin, HIGH, 100000);

  //return (duration * 170 / 1000000.0); // in meters
  // 39.3701 inches per meter
  return (39.3701 * duration * 170 / 1000000.0); // in inches
}

void setup()
{
  // set trigger and echo pin modes to output and input respectively
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // set the trigger pin to LOW, just to be sure where we're starting
  digitalWrite(triggerPin, LOW);

  // begin serial communications, so that we'll be able to send our
  // distance measurements to the computer later on
  Serial.begin(115200);
}

void loop()
{
  // measure the distance (in inches)
  float dist = measure_distance();

  // report the measured distance over Serial
  Serial.print("distance measured = ");
  Serial.print(dist);
  Serial.println(" inches");

  // pause for a second
  delay(1000);
}
