#include<Arduino.h>
#include<WiFi.h>
#include<HTTPClient.h>

void setup() {
Serial.begin(115200);
Serial.println();

for(uint8_t t=4;t>0;t--)
{
  Serial.printf("[SETUP] Wait %d...\n",t);
  Serial.flush();
  delay(1000);
}
WiFi.begin("sunil","8790225440");
}

void loop() {
if(WiFi.status() == WL_CONNECTED)
{
  HTTPClient http;
  Serial.print("[HTTP] begin ...\n");
  http.begin("http://api.thingspeak.com/channels/272149/fields/1/last.txt");
  //http.begin("http://api.thingspeak.com/update?api_key=2BVNRYTR0TQARZ35&field1=10");
  //http.begin("http://api.thingspeak.com/channels/272149/fields/1/last.txt");
  Serial.print("HTTP Get ...\n");
  int httpcode=http.GET();
    Serial.printf("[HTTP] GET... code:%d\n",httpcode);
    
    if(httpcode==200)
    {
      String mydata=http.getString();
      Serial.println(mydata);
      if(mydata=="1")
      {
        Serial.println("Char Data received");
      }
      int a=mydata.toInt();
      if(a==1)
      {
        Serial.println("Int Data received");
      }   
    }
    else
    {
      Serial.printf("[HTTP] GET Failed, Error:%d",httpcode);
    }
    http.end();
  delay(5000);
}
}
