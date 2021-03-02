#include <SoftwareSerial.h>
#include <MFRC522.h>

SoftwareSerial rfidan(2,3);
  // ----- RFID BEGIN
  /* Mega2560
   * MISO     50 
   * MOSI     51
   * SDA      53
   * SCK      52
  */
  #define SS_PIN 53 // SDA
  #define RST_PIN 49 // RST
  MFRC522 rfid(SS_PIN, RST_PIN);
  MFRC522::MIFARE_Key key;
  String id;
  boolean lockdoor = true;
  // ----- RFID END

  String nama;;
  
void setup() {
  SPI.begin();
  rfid.PCD_Init();
  // put your setup code here, to run once:
  pinMode (13, OUTPUT);
  Serial.begin(115200);
  rfidan.begin(115200);
  Serial.println("*Uji RFID Ready ....");
}

void loop() {
  // put your main code here, to run repeatedly:
  rfid_card();
}


void rfid_card(){
  if ( ! rfid.PICC_IsNewCardPresent())
    return;

  // Verify if the NUID has been readed
  if ( ! rfid.PICC_ReadCardSerial())
    return;

  Serial.print(F("*PICC type: "));
  MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
  Serial.println(rfid.PICC_GetTypeName(piccType));

  Serial.println(F("*The NUID tag is:"));
  Serial.print(F("*In hex: "));
  printHex(rfid.uid.uidByte, rfid.uid.size);
  Serial.println();

  Serial.print(F("*In dec: "));
  printDec(rfid.uid.uidByte, rfid.uid.size);
  Serial.println();
  
  rfid.PICC_HaltA();
  Serial.print("*ID RFID : ");
  rfidan.print("*ID RFID : ");
  Serial.println(id);
  rfidan.print(id);
  rfidan.print("\n");
  rfidan.print("\n");
  
  if (id == "21ab9d1" || // master
  id == "3b7bd7c0" || // Yusuf
  id == "e5369f10" || // YusufA
  id == "20d5473b" || // Fadly
  id == "cb84dcc0" ||
  id == "0bf5f50e" ||
  id == "okoc"){ // Yamayuki

    if(id == "3b7bd7c0")nama = "Yusuf Maulana";
    Serial.print("*NAMA : " + String(nama));  
    Serial.println();
    Serial.print("*<><> Access Accepted <><>");
    Serial.println();
    Serial.println(); 
    if(lockdoor == true){
      lockdoor = false; 
      digitalWrite(13,1);
      delay(2000);
      digitalWrite(13,0);
    }
    else if(lockdoor == false){
      lockdoor = true;
      digitalWrite(13,0);
    }

  }
  else {
    Serial.print("*<!><!> Access Denied <!><!>");
    Serial.println();
    Serial.println();
    digitalWrite(13,0);
  }

  id = "";
}

void printHex(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? "0" : "");
    Serial.print(buffer[i], HEX);
    id = id + String(buffer[i] < 0x10 ? "" : "")+String(buffer[i], HEX);
  }
}
//void printHex(byte *buffer, byte bufferSize) {
//  for (byte i = 0; i < bufferSize; i++) {
//    tagval = tagval + String(buffer[i] < 0x10 ? "" : "")+
//    String(buffer[i], HEX);
//  }
//}
void printDec(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], DEC);
  }
}
