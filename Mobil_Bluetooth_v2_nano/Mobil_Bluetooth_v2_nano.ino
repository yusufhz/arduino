#include <SoftwareSerial.h>

SoftwareSerial data(2,3);

#define mkiri_maju 11
#define mkiri_mundur 10

#define mkanan_maju 9
#define mkanan_mundur 6

#define Sensor A0

// deteksi putih = 208+-10
// deteksi hitam = 920 +- 10

char dataku = 'S';
int nilai_makiri = 0;
int nilai_makanan = 0;
int nilai_mukiri = 0;
int nilai_mukanan = 0;
char last_dataku = 'S';
byte data_masuk = 0;
void setup(){
  Serial.begin(9600);
  data.begin(9600);
}

void loop(){
  readdataku();
  dataku=dataku;
  last_dataku = dataku;
  if(dataku=='M' || dataku=='B'){
    motor();
  }
  if(dataku=='R' || dataku=='L'){
    belok();
    delay(500);
    dataku = 'S';
  }
  if(dataku=='S'){
    berhenti();
  }
  if(last_dataku != dataku || nilai_mukanan!=0 
  || nilai_mukiri != 0 || nilai_makanan != 0){
    last_dataku = dataku;
    printspeed();
  }
  //Serial.println(analogRead(A0));
}
void readdataku(){
  if(data.available() > 0){
    dataku = Serial.read();   
    //dataku = data.read();   
    if(dataku=='M' && nilai_makiri < 255){
        nilai_makiri = nilai_makiri + 100;
        nilai_makanan = nilai_makiri;
        nilai_mukiri = 0;
        nilai_mukanan = 0;
        if(nilai_makiri > 255){
          nilai_makiri = 255;
          nilai_makanan = nilai_makiri;
          nilai_mukiri = 0;
          nilai_mukanan = 0;
        }
      }
    if(dataku=='B' && nilai_mukiri < 255){
      nilai_mukiri = nilai_mukiri + 100;
      nilai_mukanan = nilai_mukiri;
      nilai_makiri = 0;
      nilai_makanan = 0;
      if(nilai_mukiri > 255){
        nilai_mukiri = 255;
        nilai_mukanan = nilai_mukiri;
        nilai_makiri = 0;
        nilai_makanan = 0;
      }
    }
    if(dataku=='L'){
      nilai_makanan = 150;
      nilai_mukiri = 150;
      nilai_mukanan = 0;
      nilai_makiri = 0;
    }
    if(dataku=='R'){
      nilai_makiri = 150;
      nilai_mukanan = 150;   
      nilai_mukiri = 0;
      nilai_makanan = 0;
    }
    if(dataku=='S'){
      nilai_makiri = 0;
      nilai_makanan = 0;
      nilai_mukiri = 0;
      nilai_mukanan = 0;
    }
  }
  delayMicroseconds(2);
}
void motor(){
  analogWrite(mkiri_maju,nilai_makiri);
  analogWrite(mkiri_mundur,nilai_mukiri);
  analogWrite(mkanan_maju,nilai_makanan);
  analogWrite(mkanan_mundur,nilai_mukanan);
  delayMicroseconds(2);
}
void belok(){
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
