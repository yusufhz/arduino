#define mkiri_maju 9 //in3
#define mkiri_mundur 5 //in4

#define mkanan_maju 11 //in1
#define mkanan_mundur 10 //in2

#define echoPin 7
#define triggerPin 8

// deteksi putih = 208+-10
// deteksi hitam = 920 +- 10

int nilai_makiri = 0;
int nilai_makanan = 0;
int nilai_mukiri = 0;
int nilai_mukanan = 0;

unsigned long waktuS;
unsigned long waktuL1 = 0;
unsigned long waktuL2 = 0;
unsigned long waktuL3 = 0;

long duration;
int distance;
int mundur = 0;
#include "UltrasonicOK.h"

void setup(){
  pinMode (triggerPin, OUTPUT);
  pinMode (echoPin, INPUT);
  Serial.begin(9600);
}

void loop(){
  waktuS = millis();
  if(waktuS - waktuL1 > 100){
    waktuL1 = waktuS;
    Sultra();
  }
  if(waktuS - waktuL2 > 100){
    waktuL2 = waktuS;
    if(distance <= 30){
      berhenti();
      nilai_makiri = 0;
      nilai_mukanan = 250;   
      nilai_mukiri = 250;
      nilai_makanan = 0;
      motor();
      delay(200);

      nilai_makiri = 200;
      nilai_mukanan = 200;   
      nilai_mukiri = 0;
      nilai_makanan = 0;
      motor();
      delay(200);
      //Serial.println("Belok Kanan");
    }
    else if(distance >= 30 && distance <= 60){
      nilai_makiri = nilai_makiri - 50;
      nilai_makanan = nilai_makanan - 50;
      nilai_mukiri = 0;
      nilai_mukanan = 0;
      if(nilai_makiri < 100){
        nilai_makiri = 100;
        nilai_makanan = 100;
        nilai_mukiri = 0;
        nilai_mukanan = 0;
      }
      motor();
      //Serial.println("Pelan2");
    }
    else if (distance >= 51){
      nilai_makiri = 250;
      nilai_makanan = 250;
      nilai_mukiri = 0;
      nilai_mukanan = 0;
      motor();
      //Serial.println("Maju");
    }
  }
}

void motor(){
  analogWrite(mkiri_maju,nilai_makiri);
  analogWrite(mkiri_mundur,nilai_mukiri);
  analogWrite(mkanan_maju,nilai_makanan);
  analogWrite(mkanan_mundur,nilai_mukanan);
  delayMicroseconds(2);
}

void berhenti(){
  analogWrite(mkiri_maju,0);
  analogWrite(mkiri_mundur,0);
  analogWrite(mkanan_maju,0);
  analogWrite(mkanan_mundur,0);
  delayMicroseconds(2);
}

void printspeed(){
  Serial.println(nilai_mukiri);
  Serial.println(nilai_mukanan);
  Serial.println(nilai_makiri);
  Serial.println(nilai_makanan);
}
