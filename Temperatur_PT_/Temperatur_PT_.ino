#include <Wire.h>
#include <Adafruit_AMG88xx.h>
#include <SPI.h>        
#include <DMD2.h>
#include <fonts/DejaVuSans9.h>
#include <fonts/SystemFont5x7.h>

Adafruit_AMG88xx amg;

SoftDMD dmd(1,1);

// Ping
#define tPin 2
#define ePin 3
long duration;
int jarak;
#include "Ultrasonic.h"

String x;
int baca = 0;
char datame = 0;
bool aktif = 0;
bool pintuSensor = 0;

//Waktu
unsigned long Waktu_S;
unsigned long WaktuL1, WaktuL2 = 0;

float suhu;
float kalibrasi = 4.8;
      
void setup() {
  pinMode (tPin, OUTPUT);
  pinMode (ePin, INPUT);

  Serial.begin(115200);  
  Serial.println(F("AMG88xx test"));

  bool status;
  
  status = amg.begin();
  if (!status) {
      Serial.println("Could not find a valid AMG88xx sensor, check wiring!");
      while (1);
  }  
  dmd.setBrightness(255);
  dmd.selectFont(SystemFont5x7);
  dmd.begin();
  Serial.println("-- Thermistor Test --");
  Serial.println();
  delay(100);  
}
int i = 32;
void loop() {
  Waktu_S = millis();
  sensorJarak();
//    suhu = amg.readThermistor() + kalibrasi;
//    Serial.print("Suhu = "); Serial.print(suhu); Serial.println("°C");
//    dmd.drawString(0, 4, String(suhu) + "°C");
//  }//End Program 1
    if(jarak >= 17 && baca != 1){
      dmd.drawString(i,0, F("Mendekat"));
      dmd.drawString(0,8, String(jarak));
      i--;
      delay(100);
      if(i == -20){
        dmd.clearScreen();
        i=32;
      }
    }
    if(jarak < 17 && jarak > 15 && baca != 1){
      baca = 1;
      suhu = amg.readThermistor() + kalibrasi;
      Serial.print("Suhu = "); Serial.print(suhu); Serial.println("°C");
      if (suhu > 29 && suhu < 37 && baca != 0){
        dmd.drawString(0, 8, " AMAN ");
        dmd.drawString(0, 0," Suhu ");
        delay(500);
        dmd.drawString(0, 0, String(suhu) + "C");
        delay(500);
        baca = 0;
      }
      else if (suhu >= 37 && suhu <= 100 && baca != 0){
        dmd.drawString(0,0, "Suhu Anda Bahaya");
        delay(2000);
        baca = 0;
      }
    }
//  }//Program 2
}
