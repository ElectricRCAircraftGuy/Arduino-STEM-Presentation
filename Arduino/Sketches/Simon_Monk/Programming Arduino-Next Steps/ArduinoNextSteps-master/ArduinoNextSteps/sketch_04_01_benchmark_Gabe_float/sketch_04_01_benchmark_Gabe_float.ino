// sketch 04_01_benchmark

//slightly modified by Gabriel Staples, 8 May 2014

/*
My results are as follows, as copied/pasted from the Serial Monitor:
"Starting Test
0.00
Finished Test
Seconds taken: 467.91"
*/

void setup()
{
  Serial.begin(115200);
  while (! Serial) {};
  Serial.println("Starting Test");
  long startTime = millis();
  
  // test code here
  long  i = 0;
//  long j = 0;
  float j = 0;
  for (i = 0; i < 20000000; i ++)
  {
    j = i + i * 10.0;
    if (j > 10) j = 0.0;
  }
  // end of test code
  long endTime = millis();
  
  Serial.println(j); // prevent loop being optimized out
  Serial.println("Finished Test");
  Serial.print("Seconds taken: "); 
  Serial.println((endTime - startTime) / 1000.0);
}

void loop()
{
  
}
