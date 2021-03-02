#include <SoftwareSerial.h>

SoftwareSerial sim800l(8, 9); // RX,TX for Arduino and for the module it's TXD RXD, they should be inverted

void setup() {
  // put your setup code here, to run once:
  sim800l.begin(9600);   //Module baude rate, this is on max, it depends on the version
  Serial.begin(9600); 
  SendSMS();
}

void loop() {
  // put your main code here, to run repeatedly:

}

void SendSMS()
{
  Serial.println("Sending SMS...");               //Show this message on serial monitor
  sim800l.print("AT+CMGF=1\r");                   //Set the module to SMS mode
  delay(100);
  sim800l.print("AT+CMGS=\"+6285891122785\"\r");  //Your phone number don't forget to include your country code, example +212123456789"
  delay(500);
  sim800l.print("T");       //This is the text to send to the phone number, don't make it too long or you have to modify the SoftwareSerial buffer
  delay(500);
  sim800l.print((char)26);// (required according to the datasheet)
  delay(500);
  sim800l.println();
  Serial.println("Text Sent.");
  delay(500);

}
