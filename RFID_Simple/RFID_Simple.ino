#include <MFRC522.h>
#include <SPI.h>
#include <EEPROM.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define SS_PIN 10
#define RST_PIN 9

MFRC522 rfid(SS_PIN, RST_PIN);

MFRC522::MIFARE_Key key;

String id;
int addr = 0;

void setup(){
  Serial.begin(9600);
  SPI.begin();
  rfid.PCD_Init();
  
}

void loop(){
  pembacaan();
  if(id != id){
    addr++;
    EEPROM.write(addr, id);    
  }
  if(id != id){
    addr++;
    EEPROM.read(addr);
  }
}
void pembacaan(){
  if ( ! rfid.PICC_IsNewCardPresent())
    return;

  // Verify if the NUID has been readed
  if ( ! rfid.PICC_ReadCardSerial())
    return;

  Serial.print(F("PICC type: "));
  MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
  Serial.println(rfid.PICC_GetTypeName(piccType));

  id = String(rfid.uid.uidByte[0], HEX) + 
  String(rfid.uid.uidByte[1], HEX) + 
  String(rfid.uid.uidByte[2], HEX) +
  String(rfid.uid.uidByte[3], HEX);
  Serial.println(id);
  

  rfid.PICC_HaltA();
}

