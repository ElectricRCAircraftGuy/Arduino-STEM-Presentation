//By Gabriel Staples
//5 June 2014

const byte photoPin = A1;

void setup()
{
  Serial.begin(115200);  
}

void loop()
{
  unsigned int photoVal = analogRead(photoPin);
  Serial.print(photoVal); Serial.print(", ");
  if (photoVal <=600) //<=600
  {
    Serial.println("pitch black");
  }
  else if (photoVal < 850) //601 to 849
  {
    Serial.println("dim");
  }
  else //>=850
  {
    Serial.println("bright");
  }
    
  delay(500);
}
