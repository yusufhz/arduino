#include <SoftwareSerial.h>
SoftwareSerial blut(A0,A1); // RX, TX

#define ma_kanan 9
#define mu_kanan 10

#define ma_kiri 5
#define mu_kiri 6

char datame = 0 ;
char databt = 0;

void setup() {
  Serial.begin(9600);
  blut.begin(9600);

}

void loop() {
  if(Serial.available() || blut.available()){
    //datame = Serial.read();
    databt = blut.read();
    //databt = datame;
  }
  switch(databt){
    case 'f':
    maju();
    break;
    case 'h':
    mundur();
    break;
    case 'g':
    belok_kiri();
    break;
    case 'e':
    belok_kanan();
    break;
    default:
    berhenti();
    break;
  }
  

}
// maju lurus 50cm
// kanan 243
// kiri 250
void maju(){
  analogWrite(ma_kanan, 243);
  analogWrite(ma_kiri, 250);
  analogWrite(mu_kanan, 0);
  analogWrite(mu_kiri, 0);
}

void mundur(){
  analogWrite(ma_kanan, 0);
  analogWrite(ma_kiri, 0);
  analogWrite(mu_kanan, 243);
  analogWrite(mu_kiri, 250);
}

void belok_kanan(){
  analogWrite(ma_kanan, 0);
  analogWrite(ma_kiri, 250);
  analogWrite(mu_kanan, 243);
  analogWrite(mu_kiri, 0);
}

void belok_kiri(){
  analogWrite(ma_kanan, 243);
  analogWrite(ma_kiri, 0);
  analogWrite(mu_kanan, 0);
  analogWrite(mu_kiri, 250);
}

void berhenti(){
  analogWrite(ma_kanan, 0);
  analogWrite(ma_kiri, 0);
  analogWrite(mu_kanan, 0);
  analogWrite(mu_kiri, 0);
}
