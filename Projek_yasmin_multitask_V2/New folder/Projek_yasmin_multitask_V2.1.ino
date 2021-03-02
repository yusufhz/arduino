#include <Servo.h>
#include <SoftwareSerial.h>
#include <DFPlayer_Mini_Mp3.h>

#define Debug true
#define DebugS true
SoftwareSerial SerialX(10, 11);// RX, TX

Servo tutup;

#define pinMetal 2
#define pinPlastik 3
#define pinTrig 4
#define pinEcho 5
#define pinServo 6
#define pinLed 13

boolean metal = true;
boolean plastik = false;
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
  for(int j = 0; j < 2;j++){
  for(int i = 65; i < 180; i+=5){
    tutup.write(i);
    delay(50);
  }
  for(int i = 180; i > 0; i-=5){
    tutup.write(i);
    delay(50);
  }
  for(int i = 0; i > 65; i-=5){
    tutup.write(i);
    delay(50);
  }
  }
  tutup.write(63);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  waktu_sekarang = millis();
  if(waktu_sekarang - waktu_sebelum3 > 1000 && Debug == true){
    waktu_sebelum3 = waktu_sekarang;
    Serial.println("===== Mode Debug ON ====");
    pinSensor();
    Ultrasonic();
    Serial.print("Jarak = ");
    Serial.print(distance);
    Serial.println(" cm");
    Serial.print("Plastik = ");
    Serial.println(plastik);
    Serial.print("Metal = ");
    Serial.println(metal);
  }
  if(waktu_sekarang - waktu_sebelum4 > 1000 && DebugS == true){
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
  if(waktu_sekarang - waktu_sebelum1 > 1000 && Debug == false){
    waktu_sebelum1 = waktu_sekarang;
    Ultrasonic();
    Serial.println("Jarak = ");
    Serial.println(distance);
    Serial.println("==================================");
  }
  if(waktu_sekarang - waktu_sebelum2 > 1000 && Debug == false){
    waktu_sebelum2 = waktu_sekarang;
    if(distance < 30){ //jika jarak < 30cm
      Serial.println("Jarak = ");
      Serial.println(distance);
      Serial.println("Ada Orang");
      sensor : pinSensor();
      mp3_play(1);//silahkan dekatkan sampah anda pada detektor
      delay(5500);//sesuai durasi diatas
      if(plastik == false){
        if(metal == false){
          Serial.println("Non Organik");
          mp3_play(2);// Sampah Metal
          tutup.write(0);
          delay(3500);
          mp3_play(4);//Silahkan Masukan Sampah Anda
          delay(4500);
          mp3_play(5);//Terima Kasih
          tutup.write(63);
          delay(3500);
          mp3_stop();
        }
        else {
          Serial.println("Organik");
          mp3_play(3);// Sampah Plastik
          tutup.write(180);
          delay(3500);
          mp3_play(4);//Silahkan Masukan Sampah Anda
          delay(4500);
          mp3_play(5);//Terima Kasih
          tutup.write(63);
          delay(3500);
          mp3_stop();
        }
      }
      else {
        goto sensor;
      }
    }
    else {
        Serial.println("Tidak Ada Orang");
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