/*
By Gabriel Staples
http://electricrcaircraftguy.blogspot.com/
19 Nov. 2013

-plug in a jumper wire to pin 7.  Open the serial monitor, set the baud rate to 115200, and touch the jumper wire to watch it detect your touch "intensity."
*/


void setup() {
  Serial.begin(115200);

}

void loop() {
  int cycle_count = readCapacitivePin(7);
  Serial.print("Cycle count (ie: touch intensity): ");
  Serial.println(cycle_count);
  delay(500);
  
}
