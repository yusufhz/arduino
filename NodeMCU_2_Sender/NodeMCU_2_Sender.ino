#include "SoftwareSerial.h"
SoftwareSerial Kirim(12,13);

void setup() {                                          
  Serial.begin(115200);
  Kirim.begin(115200);
  
  Serial.println("NodeMCU_2_Sender");
  Kirim.print("Data Terikirim");
}

void loop() {
  if(Serial.available()){
    char data = Serial.read();
    Kirim.println(data);
  }
  delay(50);
}
