#include <EEPROMex.h>
#include "Arduino.h"
String kata;
char input[15] = {};
char output[15] = {};
char c;
int menu = 0;
void setup() {
  Serial.begin(9600);
  Serial.println("Sistem Siap");
  Serial.println();
}

void loop() {
  if(menu == 0){
    if(Serial.available()!= 0){
      c = Serial.read();
      Serial.print("data Masuk : ");
      Serial.println(c);
    }
    if(c == 'a'){
        menu = 1;
        Serial.println("Masuk mode 1");
        c = "";
    }
    else if(c == 'b'){
        menu = 2;
        Serial.println("Masuk mode 2");
        c = "";
    }
  }
  else if(menu == 1){
    // masukkan data
    if(Serial.available()!= 0){
      c = Serial.read();
      Serial.print("data Masuk : ");
      if(c!= '1' || c!= '2' || c!='\n'){kata = kata + c;}
      Serial.println(kata);
    }
    if(c == '1'){
      Serial.print("kata : ");
      Serial.println(kata);
      kata.toCharArray(input, 15);
      EEPROM.writeBlock<char>(1, input, 15); 
      Serial.println("address: 1 ");
      Serial.print("input: ");
      Serial.println(input);
      menu = 0;
      kata = "";
    }
    else if(c == '2'){
      Serial.println(kata);
    }
  }
  else if(menu == 2){
    if(Serial.available()>0){
      c = Serial.read();
      Serial.println("data Masuk : ");
    }
    if(c == '1'){
      EEPROM.readBlock<char>(1, output, 15); 
      Serial.print("output: ");
      kata = output;
      Serial.println(kata);
      Serial.println("");
      menu = 0;
    }
  }
}
