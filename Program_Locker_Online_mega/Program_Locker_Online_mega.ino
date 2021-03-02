/* Pin RFID dan Arduino
 * ---------------------------------
 * RST          49     
 * MISO         50
 * MOSI         51
 * SCK          52
 * SDA(SS)      53
 * ---------------------------------
 * Pin Nextion dan Arduino
 * RX           11
 * TX           10
 */
 
#include <SharpIR.h>
#include <SPI.h>
#include <MFRC522.h>
#include <SoftwareSerial.h>
#include <SharpIR.h>

#define relay1 5
#define relay2 6
#define relay3 7

#define indiL1 23
#define indiL2 25
#define indiL3 27

#define RS 49
#define SS 53

MFRC522 rfid(SS, RS);
MFRC522::MIFARE_Key key;
SoftwareSerial next(10, 11); // RX | TX

int i;

bool masuk;
bool parsing;

String uid;
String tagval;
String dt[20];
String dataIn = "";
String dataInLast = "*";
String message;
String cekserial;
String L1, L2, L3;

byte distance1;
byte distance2;
byte distance3;

bool locker1, locker2, locker3;

#include "pencocokan.h"
#include "Parsing_data.h"
#include "nodemcu_LO.h"

void(* me_reset)(void)=0;
void setup() {
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);

  digitalWrite(relay1, 1);
  digitalWrite(relay2, 1);
  digitalWrite(relay3, 1);
  
  Serial.begin(115200);
  Serial3.begin(115200);
  next.begin(9600);
  digitalWrite(SS, 1);
  delay(200);
  digitalWrite(SS, 0);
  SPI.begin();
  rfid.PCD_Init();
  digitalWrite(SS, 1);
  
  pinMode (indiL1, OUTPUT);
  pinMode (indiL2, OUTPUT);
  pinMode (indiL3, OUTPUT);
  digitalWrite(indiL1, 0);
  digitalWrite(indiL2, 0);
  digitalWrite(indiL3, 0);
  
  Serial.println("  Lockeronline.dx.am");
  Serial.println("  ---- -Ready ------");
  masuk = false;
}

void loop() {
  serialxx();
  if (!next.available()) {
    if (message.length() > 14) {
      Serial.println(message);
      if (message[4] == '2' || message[4] == '4') {
        uid = "x";
        masuk = true;
        message = "";
      } else if (message[4] == '1') {
        Serial.println("------ Ready ------");
        //me_reset();
        masuk = false;
        message = "";
      }
      message = "";
    }
  }
  if (next.available()) {
    message.concat(next.read());
  }
  aktifkan();
//  readrfid();
}

void serialxx(){
  if(Serial.available()){
    char luwak = Serial.read();
    if(luwak == 'm'){
      uid = "x";
      masuk = true;
//      sensor_a = false;
    }
    else if(luwak == 'n'){
      masuk = false;
    }
  }
}

void aktifkan() {
  if (masuk == true) {
    readrfid();
    ceknode();
    pencocokan();
  } else {
    uid = "";
//    digitalWrite(relay1, 1);
//    digitalWrite(relay2, 1);
//    digitalWrite(relay3, 1);
  }
}

void readrfid() {
  if (!rfid.PICC_IsNewCardPresent()) {
    return;
  }
  if (!rfid.PICC_ReadCardSerial()) {
    return;
  }  

  printHex(rfid.uid.uidByte, rfid.uid.size);
  //rfid.PICC_HaltA(); // stop reading
  if (tagval.length() >= 5) {
    if (tagval != "") {
      uid = tagval;
      Serial.print ("ID RFID TERBACA : ");
      Serial.println(uid);
      delay(1000);
    }
    tagval = "";
  }
}

void printHex(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    tagval = tagval + String(buffer[i] < 0x10 ? "" : "")+
    String(buffer[i], HEX);
  }
}
