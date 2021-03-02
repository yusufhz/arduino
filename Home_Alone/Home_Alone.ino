#include <Servo.h>
#include <SoftwareSerial.h>

SoftwareSerial bt(A0,A1);//rx tx

#define LampTeng 2
#define LampDep 4
#define LampSamp 3
#define pinServo 6

Servo garasi;
char datame = 0;
char databt = 0;
String suara;
#include "databt.h"
#include "dataserial.h"
#include "suarabt.h"

void setup() {
  
  Serial.begin(9600);
  bt.begin(9600);
  
  pinMode (LampTeng, OUTPUT);
  pinMode (LampDep, OUTPUT);
  pinMode (LampSamp, OUTPUT);
  garasi.attach(pinServo);
  garasi.write(110);
}

void loop() {
  if(Serial.available() || bt.available()){
    suara = bt.readString();
    datame = Serial.read();
    //databt = bt.read();
    Serial.println(suara);  
    Serial.println(databt);
  }
  datablut();
  dataserial();
  suarabt();
}
