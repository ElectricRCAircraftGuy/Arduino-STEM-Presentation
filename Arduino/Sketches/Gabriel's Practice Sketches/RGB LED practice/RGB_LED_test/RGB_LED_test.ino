//Gabriel Staples
//5 June 2014

const byte red = 3;
const byte green = 9;
const byte blue = 10;

void setup()
{
  Serial.begin(115200);
  pinMode(red,OUTPUT);
  pinMode(green,OUTPUT);
  pinMode(blue,OUTPUT);
}

void loop()
{
  digitalWrite(red,HIGH);
  delay(500);
  digitalWrite(red,LOW);
  
  digitalWrite(green,HIGH);
  delay(500);
  digitalWrite(green,LOW);
  
  digitalWrite(blue,HIGH);
  delay(500);
  digitalWrite(blue,LOW);
}



