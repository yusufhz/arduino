#include <SoftwareSerial.h>
SoftwareSerial data(A0,A1);

#define Maju 2
#define Mundur 3
#define BelKa 4
#define BelKi 5
#define Buka 6
#define Tutup 7
#define Turun 8
#define Angkat 9
#define Tambahan 10
#define LSwitch 11

char dataread = 0;
char datalast;
boolean limits = 1;
void setup() {
  pinMode(Maju, OUTPUT);
  pinMode(Mundur, OUTPUT);
  pinMode(BelKa, OUTPUT);
  pinMode(BelKi, OUTPUT);
  pinMode(Buka, OUTPUT);
  pinMode(Tutup, OUTPUT);
  pinMode(Turun, OUTPUT);
  pinMode(Angkat, OUTPUT);
  pinMode(Tambahan, OUTPUT);
  pinMode(LSwitch, INPUT_PULLUP);
  Serial.begin(9600);
  data.begin(9600);
  Serial.println("Ready");
}

void loop() {
  limits = digitalRead(LSwitch);
  dataread = 0;
  if(Serial.available() || data.available()){
    dataread = Serial.read();
    Serial.println(dataread);
    datalast = data.read();
  }
  if(datalast == 'a' || dataread == 'a'){
    digitalWrite(Maju, 1);
  }
  else{
    digitalWrite(Maju, 0);
  }
  if(datalast == 'b' || dataread == 'b'){
    digitalWrite(Mundur, 1);
  }
  else{
    digitalWrite(Mundur, 0);
  }
  if(datalast == 'c' || dataread == 'c'){
    digitalWrite(BelKa, 1);
  }
  else{
    digitalWrite(BelKa, 0);
  }
  if(datalast == 'd' || dataread == 'd'){
    digitalWrite(BelKi, 1);
  }
  else{
    digitalWrite(BelKi, 0);
  }
  if(datalast == 'e' || dataread == 'e'){
    digitalWrite(Buka, 1);
  }
  else{
    digitalWrite(Buka, 0);
  }
  if(datalast == 'f' || dataread == 'f'){
    digitalWrite(Tutup, 1);
  }
  else{
    digitalWrite(Tutup, 0);
  }
  if(datalast == 'g' || dataread == 'g'){
    digitalWrite(Turun, 1);
    if(limits == 1){
      digitalWrite(Turun, 0);  
    }
  }
  else if(datalast == 'h' || dataread == 'h'){
    digitalWrite(Angkat, 1);
  }
  else{
    digitalWrite(Angkat, 0);
  }
  if(datalast == 'i' || dataread == 'i'){
    digitalWrite(Tambahan, 1);
  }
  else{
    digitalWrite(Tambahan, 0);
  }
  Serial.println(dataread);
  Serial.println(datalast);
  //delay(100);
}
