// sketch_12_04_server_wifi

#include <SPI.h>
#include <WiFi.h>

char ssid[] = "My network name";  // your network SSID (name) 
char pass[] = "mypassword";     // your network password

WiFiServer server(80);
WiFiClient client;

const int numPins = 5;
int pins[] = {3, 8, 5, 6, 9};
int pinState[] = {0, 0, 0, 0, 0};
char line1[100];
char buffer[100];

void setup()
{
  Serial.begin(9600);
  while (!Serial){};  // Leonardo needs this
  for (int i = 0; i < numPins; i++)
  {
     pinMode(pins[i], OUTPUT);
  }
  if (WiFi.begin(ssid, pass)) 
  {
    Serial.print(F("Point your Browser at: http://"));
    Serial.println(WiFi.localIP());
  }
  else
  {
    Serial.println(F("Could not connect to network"));
  }
  server.begin();
}

void loop()
{
  client = server.available();
  if (client) 
  {
    if (client.connected()) 
    {
      readHeader();
      if (! pageNameIs("/"))
      {
        client.stop();  
        return;
      }
      client.println(F("HTTP/1.1 200 OK\nContent-Type: text/html\n"));
      sendBody();
      delay(1);
      client.stop();          
    }
  }
}

void sendBody()
{
  client.println(F("<html><body>"));
  sendAnalogReadings();
  client.println(F("<h1>Output Pins</h1>\n<form method='GET'>"));
  setValuesFromParams();
  setPinStates();
  sendHTMLforPins();
  client.println(F("<input type='submit' value='Update'/>\n</form>\n</body></html>"));
}

void sendAnalogReadings()
{
  client.println(F("<h1>Analog Inputs</h1>\n<table border='1'>"));
  for (int i = 0; i < 5; i++)
  {
    int reading = analogRead(i);
    client.print(F("<tr><td>A")); client.print(i); 
    client.print(F("</td><td>")); client.print((float) reading / 205.0);
    client.println(F(" V</td></tr>"));
  }
  client.println("</table>");
}

void sendHTMLforPins()
{
  for (int i = 0; i < numPins; i++)
  {
    client.print(F("<p>Pin "));
    client.print(pins[i]);  
    client.print(F("<select name='"));
    client.print(i);
    client.println(F("'>\n<option value='0'"));
    if (pinState[i] == 0)
    {
      client.print(F(" selected"));
    }
    client.println(F(">Off</option>\n<option value='1'"));
    if (pinState[i] == 1)
    {
      client.print(F(" selected"));
    }
    client.println(F(">On</option>\n</select></p>"));
  }
}

void setPinStates()
{
  for (int i = 0; i < numPins; i++)
  {
     digitalWrite(pins[i], pinState[i]);
  }
}

void setValuesFromParams()
{
  for (int i = 0; i < numPins; i++)
  {
    pinState[i] = valueOfParam(i + '0');
  }
}

void readHeader()
{
  readRequestLine(line1);
  while (readRequestLine(buffer) > 1 && buffer[0] != '\n') {}
}

int readRequestLine(char *line)
{
  char ch;
  int i = 0;
  while (ch != '\n' && i < 100 && client.available())
  {
    if (client.available())
    {
      ch = client.read();
      line[i] = ch;
      i ++;
    }
  }
  line[i] = '\0'; 
  return i;
}

boolean pageNameIs(char* name)
{
   // page name starts at char pos 4
   // ends with space
   int i = 4;
   char ch = line1[i];
   while (ch != ' ' && ch != '\n' && ch != '?')
   {
     if (name[i-4] != line1[i])
     {
       return false;
     }
     i++;
     ch = line1[i];
   }
   return true;
}

int valueOfParam(char param)
{
  for (int i = 0; i < strlen(line1); i++)
  {
    if (line1[i] == param && line1[i+1] == '=')
    {
      return (line1[i+2] - '0');
    }
  }
  return 0;
}



