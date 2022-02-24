#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// === LCD ===
LiquidCrystal_I2C lcd (0x27, 16, 2);

// ==== Gerakan ====
#include <SoftwareSerial.h>
SoftwareSerial Dataku(51,52);//rx,tx
int tundacuy = 10;

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
#include "Sound_activator.h"

// === ON / OFF =====
boolean Ping_Sensor = true;
boolean Vlame = true;
boolean Gerak_Jalan = 1;
boolean Gerak_Jalan_Api = 0;

// ==== Millis ====
unsigned long waktuS;
unsigned long waktuping = 0;
unsigned long waktusensor = 0;
unsigned long waktuwalk = 0;
unsigned long waktuwalkfire = 0;
unsigned long waktuUVtron = 0;

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
    }
    // END  ===== Sensor Ping ======
    // BEGIN ====== Sensor Api =====
    if(waktuS - waktusensor >= invlvlame && Vlame == true){
      waktusensor = waktuS;
      Vlame_Reading();
      if(Read_Vlame[1] < 100){
        madamkan();
        digitalWrite(Relay_Ex, HIGH);
        delay(100);
        madamkan();
        digitalWrite(Relay_Ex, HIGH);
        delay(100);
        digitalWrite(Relay_Ex, LOW);
      }
    }
    // END ====== Sensor Api ======
    // BEGIN ==== Navigasi No Fire ========
    if(waktuS - waktuwalk > invlwalk && Gerak_Jalan == true && Read_UVtron != 0){
      waktuwalk = waktuS;
      Navigasi_Darat();
      digitalWrite(Relay_Ex, LOW);
      Gerak_Jalan_Api = true;
    }
    // END ==== Navigasi No Fire ========
    // BEGIN ==== Navigasi Fire ========
    if(waktuS - waktuwalkfire >= invlwalkfire && Gerak_Jalan_Api == true && Read_UVtron != 1){
      waktuwalkfire = waktuS;
      Navigasi_Api();
    }
    // END ==== Navigasi Fire ========
    // BEGIN ==== UVtron Detected Api ========
    if(waktuS - waktuUVtron >= 10 && Gerak_Jalan == true && Read_UVtron != 1){
      waktuUVtron = waktuS;
      if(KeLedUV == LOW){
        KeLedUV = HIGH;
      }else{
        KeLedUV = LOW;
      }
      digitalWrite(pinLedUV, KeLedUV);
      delay(10);
      lcd.print("    NEOS BLUE   ");
      lcd.setCursor(0, 1);
      lcd.print("  FIRE ON FIELD ");
    }
    // END ==== UVtron Detected Api ========
  }
  // END ====== Running =======
}
