#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// === LCD ===
LiquidCrystal_I2C lcd (0x27, 16, 2);

// ==== Gerakan ====
#include <SoftwareSerial.h>
SoftwareSerial Dataku(51,52);//rx,tx
// ===== SPEAD =====
int tundacuy = 10;
boolean Running = false;
// === ON / OFF =====
boolean Ping_Sensor = true;
boolean Vlame = true;
boolean Gerak_Jalan = 1;
boolean Gerak_Jalan_Api = 0;
boolean Rdebug = 0;

// ==== Sensor ====
#include "Ping_Sensor.h"
#include "Pin_CoFlame.h"

// ===== Library Make It =====
#include "movex.h"
#include "belok_kiri.h"
#include "belok_kanan.h"
#include "maju.h"
#include "mundur.h"
#include "berdiri.h"
#include "Navigasi.h"
#include "DEBUG.h"
#include "Sound_activator.h"

// ==== Millis ====
unsigned long waktuS;
unsigned long waktuping = 0;
unsigned long waktusensor = 0;
unsigned long waktuwalk = 0;
unsigned long waktuwalkfire = 0;
unsigned long waktuUVtron = 0;
unsigned long waktupemadam = 0;
unsigned long waktuwarna = 0;

int invlping = 100; // for ping sensor
int invlvlame = 100; // for vlame sensor
int invlwalk = 100; // for walking
int invlwalkfire = 500; // for walking if fire there
// =========== VOID SETUP ======
void setup() {
  berdiri();
  lcd.begin();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print(">   NEOS BLUE  <");
  lcd.setCursor(0, 1);
  lcd.print("   SHOW TIME :) ");
  Serial.begin(9600);
  Dataku.begin(9600);
  pinMode(pinSoundIN, INPUT_PULLUP);
  pinMode(pinUVtron, INPUT);
  pinMode(pinLedSound, OUTPUT);
  pinMode(Relay_Ex, OUTPUT);
  pinMode(pinLedUV, OUTPUT); 
  pinMode(proxykan, INPUT);
  pinMode(proxykir, INPUT);
  pinMode(proxydep, INPUT);
  Serial.println("===== NEOS BLUE =====");
  Serial.println("=== START MISSION ===");
  berdiri();
}
// =========== VOID LOOP =====================
void loop() {
  activation();
  if(Running == true){
    waktuS = millis();
    // BEGIN ===== Sensor Ping ======
    if(waktuS - waktuping > invlping && Ping_Sensor == true){
      waktuping = waktuS;
      proxymity();
      sensor_pingkan();
      sensor_pingserkan();
      sensor_pingdep();
      sensor_pingserkir();
      sensor_pingkir();
//      Serial.print("Flame ");
//      Serial.print(Vlamed[2]);
//      Serial.print(" ");
//      Serial.println(Read_Vlame[2]);
//      if(Rdebug == true){
//        debug();
//      }
    }
    // END  ===== Sensor Ping ======
    // BEGIN ====== Sensor Api =====
    if(waktuS - waktusensor >= invlvlame && Vlame == true){
      waktusensor = waktuS;
      Vlame_Reading();
    }
    // END ====== Sensor Api ======
    // BEGIN ==== Navigasi No Fire ========
    if(waktuS - waktuwarna >= 100 && Read_Colour < 300 && Read_UVtron == 0){
      waktuwarna = waktuS;
        maju();
        maju();
        maju();
    }
    if(waktuS - waktuwalk > invlwalk && Gerak_Jalan == true && Read_UVtron != 0){
      waktuwalk = waktuS;
      Navigasi_Darat();
      digitalWrite(Relay_Ex, LOW);
      Gerak_Jalan_Api = true;
      digitalWrite(pinLedUV, LOW);
    }
    // END ==== Navigasi No Fire ========
    // BEGIN ==== Navigasi Fire ========
    if(waktuS - waktuwalkfire >= invlwalkfire && Gerak_Jalan_Api == true && Read_UVtron != 1){
      waktuwalkfire = waktuS;
      Navigasi_Api();
      Navigasi_Darat();
    }
    // END ==== Navigasi Fire ========
    // BEGIN ==== UVtron Detected Api ========
    if(waktuS - waktuUVtron >= 10 && Gerak_Jalan == true && Read_UVtron == 0){
      waktuUVtron = waktuS;
      if(KeLedUV == LOW){
        KeLedUV = HIGH;
      }else{
        KeLedUV = LOW;
      }
      digitalWrite(pinLedUV, KeLedUV);
      delay(10);
    }
    if(waktuS - waktupemadam >= 100 && Read_UVtron == 0){
      waktupemadam = waktuS;
      if(Read_Vlame[2] < 30){
        berdiri();
        madamkan();
        digitalWrite(Relay_Ex, HIGH);
        madamkan();
        delay(100);
        lcd.setCursor(0, 1);
        lcd.println("   Padamkan   ");
        Gerak_Jalan = false;
        Gerak_Jalan_Api = false;
      }else {
        digitalWrite(Relay_Ex, LOW);
        Gerak_Jalan = true;
        Gerak_Jalan_Api = true;
        lcd.setCursor(0, 1);
      }
    }
    // END ==== UVtron Detected Api ========
  }
  // END ====== Running =======
}
