#include <Servo.h>
#include <SoftwareSerial.h>
#include <DFPlayer_Mini_Mp3.h>
#include "mode_testing.h"

//#define Testing false
//#define Tes_Sensor false
//#define Tes_Suara false

SoftwareSerial SerialX(10, 11);// RX, TX

Servo tutup;

#define pinMetal 2
#define pinPlastik 3
#define pinTrig 4
#define pinEcho 5
#define pinServo 6
#define pinLed 13

boolean metal;
boolean plastik;
byte distance;
unsigned long duration;

// multi tasking
unsigned long waktu_sekarang;
unsigned long waktu_sebelum1 = 0;
unsigned long waktu_sebelum2 = 0;
unsigned long waktu_sebelum3 = 0;
unsigned long waktu_sebelum4 = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  SerialX.begin(9600);
  tutup.attach(pinServo);
  mp3_set_serial (SerialX);  //set Serial for DFPlayer-mini mp3 module 
  delay(1);  //wait 1ms for mp3 module to set volume
  mp3_set_volume (50);
  pinMode(pinMetal, INPUT);
  pinMode(pinPlastik, INPUT);
  pinMode(pinEcho, INPUT);
  
  pinMode(pinTrig, OUTPUT);
  pinMode(pinLed, OUTPUT);
  pin_testing();
  Serial.println("Saya Siap Menjalankan Tugas");
  for(int j = 0; j < 2;j++){
    for(int i = 105; i < 140; i+=5){
      tutup.write(i);
      delay(50);
    }
    for(int i = 145; i > 105; i-=5){
      tutup.write(i);
      delay(50);
    }
    for(int i = 105; i > 55; i-=5){
      tutup.write(i);
      delay(50);
    }
    for(int i = 55; i < 105; i+=5){
      tutup.write(i);
      delay(50);
    }
  }
  mp3_play(6);
  delay(1);
    for(int j = 0; j < 20;j++){
    for(int i = 105; i < 140; i+=5){
      tutup.write(i);
      delay(50);
    }
    for(int i = 145; i > 105; i-=5){
      tutup.write(i);
      delay(50);
    }
    for(int i = 105; i > 55; i-=5){
      tutup.write(i);
      delay(50);
    }
    for(int i = 55; i < 105; i+=5){
      tutup.write(i);
      delay(50);
    }
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  waktu_sekarang = millis();
  Test();
  if(waktu_sekarang - waktu_sebelum3 > 1000 && Tes_Sensor == true){
    waktu_sebelum3 = waktu_sekarang;
    Serial.println("===== Mode Testing ON ====");
    pinSensor();
    Ultrasonic();
    Serial.print("Jarak = ");
    Serial.print(distance);
    Serial.println(" cm");
    Serial.print("Plastik = ");
    Serial.println(plastik);
    Serial.print("Metal = ");
    Serial.println(metal);
    tutup.write(180);
    delay(200);
    tutup.write(63);
    delay(200);
    tutup.write(0);
    delay(200);
    tutup.write(63);
  }
  if(waktu_sekarang - waktu_sebelum4 > 1000 && Tes_Suara == true){
    waktu_sebelum4 = waktu_sekarang;
    Serial.println("Play 1");
    mp3_play(1);
    delay(5500);
    Serial.println("Play 2");
    mp3_play(2);
    delay(3500);
    Serial.println("Play 3");
    mp3_play(3);
    delay(3500);
    Serial.println("Play 4");
    mp3_play(4);
    delay(4500);
    Serial.println("Play 5"); 
    mp3_play(5);
    delay(3500);
  }
  if(waktu_sekarang - waktu_sebelum2 > 1000 && Testing == false){
    waktu_sebelum2 = waktu_sekarang;
    Ultrasonic();
    if(distance < 30){ //jika jarak < 30cm
      Serial.print("Jarak = ");
      Serial.println(distance);
      Serial.println("Ada Orang Di depan Saya");
      mp3_play(1);//silahkan dekatkan sampah anda pada detektor
      delay(5500);//sesuai durasi diatas
      sensor : pinSensor();
      Serial.print("Plastik = ");
      Serial.println(plastik);
      Serial.print("Metal = ");
      Serial.println(metal);
      if(metal == false){
          Serial.println("Non Organik");
          mp3_play(2);// Sampah Metal
          tutup.write(55);
          delay(3500);
          mp3_play(4);//Silahkan Masukan Sampah Anda
          delay(4500);
          mp3_play(5);//Terima Kasih
          delay(3500);
          tutup.write(100);
          mp3_play(6);//Lagu
          delay(1000);
      }
      else if (plastik == true) {
          Serial.println("Organik");
          mp3_play(3);// Sampah Plastik
          tutup.write(145);
          delay(3500);
          mp3_play(4);//Silahkan Masukan Sampah Anda
          delay(4500);
          mp3_play(5);//Terima Kasih
          delay(3500);
          tutup.write(100);
          mp3_play(6);//Lagu
          delay(1000);
        }
        else{
          goto sensor;
        }
    }
    else {
      Serial.print("Jarak = ");
      Serial.println(distance);      
      Serial.println("Tidak Ada Orang Di depan Saya");
      delay(500);
    }
  }
}
// ==========================================================
void Ultrasonic(){
  digitalWrite (pinTrig, LOW);
  delayMicroseconds(2);

  digitalWrite(pinTrig,HIGH);
  delayMicroseconds(10);
  digitalWrite(pinTrig,LOW);

  duration = pulseIn(pinEcho,HIGH);
  distance = duration*0.034/2;
  if(distance >= 3){
    distance = distance +1; 
  }
  else if(distance==4){
    distance=4;
  }
  else if(distance < 3){
    distance = duration*0.034/2;
  }
}
void pinSensor(){
  metal = digitalRead(pinMetal);
  plastik = digitalRead(pinPlastik);
}
