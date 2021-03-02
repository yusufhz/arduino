#include <SoftwareSerial.h>
SoftwareSerial data(A0,A1); //RX, TX

#define Maju 2
#define Mundur 4
#define BelKa 5
#define BelKi 6
#define Buka 7
#define Tutup 8
#define Turun 9
#define Angkat 10
#define Tambahan 11
#define LSwitch 12

char dataread = '0';
char datalast;
String parsing;
String dataString;
boolean limits = 1;
unsigned long waktuS;
unsigned long waktuL1 = 0;
unsigned long waktuL2 = 0;
unsigned long waktuL3 = 0;

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
  digitalWrite(Buka, 1);
  digitalWrite(Tutup, 1);
}

void loop(){
  waktuS = millis();
  if(waktuS - waktuL1 > 1){
    if(Serial.available() || data.available()){
      //dataread = Serial.read();
      //parsing = String(dataread)+ parsing; 
      //Serial.println(dataread);
      datalast = data.read();
      parsing = parsing + String(datalast);
      Serial.println(parsing);
    }
    if (parsing == "atasPress"){
      dataread = 'a';
    }
    else if (parsing == "bawahPress"){
      dataread = 'b';
    }
    else if (parsing == "kananPress"){
      dataread = 'c';
    }
    else if (parsing == "kiriPress"){
      dataread = 'd';
    }
    else if (parsing == "kotakPress"){
      dataread = 'e';
    }
    else if (parsing == "segitigaPress"){
      dataread = 'f';
    }    
    else if (parsing == "xPress"){
      dataread = 'g';
    }
    else if (parsing == "bunderPress"){
      dataread = 'h';
    }
    if (parsing == "atasPressatasRelease" 
    || parsing == "bawahPressbawahRelease"
    || parsing == "kananPresskananRelease"
    || parsing == "kiriPresskiriRelease"
    || parsing == "kotakPresskotakRelease"
    || parsing == "segitigaPresssegitigaRelease"
    || parsing == "xPressxRelease"
    || parsing == "bunderPressbunderRelease"){
      dataread = '0';
      parsing = "";
    }
  }
  if(waktuS - waktuL2 > 1){
    waktuL2 = waktuS;
    switch (dataread){
      case 'a':
        digitalWrite(Maju, 1);
        break;
      case 'b':
        digitalWrite(Mundur, 1);
        break;
      case 'c':
        digitalWrite(BelKa, 1);
        break;
      case 'd':
        digitalWrite(BelKi, 1);
        break;
      case 'e':
        digitalWrite(Buka, 0);
        delay(10);
        digitalWrite(Buka, 1);
        break;
      case 'f':
        digitalWrite(Tutup, 0);
        delay(10);
        digitalWrite(Tutup, 1);
        break;
      case 'g':
        digitalWrite(Turun, 1);
        delay(10);
        digitalWrite(Turun, 0);
        break;
      case 'h':
        digitalWrite(Angkat, 1);
        delay(10);
        digitalWrite(Angkat, 0);
        break;
      case 'i':
        digitalWrite(Tambahan, 1);
        break;
      default:
        digitalWrite(Maju, 0);
        digitalWrite(Mundur, 0);
        digitalWrite(BelKa, 0);
        digitalWrite(BelKi, 0);
        digitalWrite(Buka, 1);
        digitalWrite(Tutup, 1);
        digitalWrite(Turun, 0);
        digitalWrite(Angkat, 0);  
        digitalWrite(Tambahan, 0);
        break;
    }
  }
}
