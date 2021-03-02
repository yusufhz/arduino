/*************************************************************
  Author    : Yusuf Maulana, S.Pd
  
 *************************************************************/
#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "d4e7849feaba448faf0e1391087cfb59";

char ssid[] = "ReNo7";
char pass[] = "12345678zx";

void setup()
{
  Serial.begin(9600);
  
  pinMode (D5, OUTPUT);
  pinMode (D6, OUTPUT);
  pinMode (D7, OUTPUT);
  pinMode (D4, OUTPUT);
  
  digitalWrite(D5, 0);
  digitalWrite(D6, 1);
  digitalWrite(D7, 1);
  digitalWrite(D4, 1);
  
  Blynk.begin(auth, ssid, pass);
}

void loop()
{
   Blynk.run();
}
