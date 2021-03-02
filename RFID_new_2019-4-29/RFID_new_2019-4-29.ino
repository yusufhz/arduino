#include <MFRC522.h>
  // ----- RFID BEGIN
  /* Mega2560
   * MISO     50 
   * MOSI     51
   * SDA      52
   * SCK      53
  */
  #define SS_PIN 53 // SDA
  #define RST_PIN 49 // RST
  MFRC522 rfid(SS_PIN, RST_PIN);
  MFRC522::MIFARE_Key key;
  String id;
  boolean lockdoor = true;
  // ----- RFID END

  String nama;
  
void setup() {
  SPI.begin();
  rfid.PCD_Init();
  // put your setup code here, to run once:
  pinMode (13, OUTPUT);
  Serial.begin(9600);
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

  Serial.print(F("PICC type: "));
  MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
  Serial.println(rfid.PICC_GetTypeName(piccType));

  Serial.println(F("The NUID tag is:"));
  Serial.print(F("In hex: "));
  printHex(rfid.uid.uidByte, rfid.uid.size);
  Serial.println();
  
//  id = String(rfid.uid.uidByte[0], HEX) + 
//  String(rfid.uid.uidByte[1], HEX) + 
//  String(rfid.uid.uidByte[2], HEX) +
//  String(rfid.uid.uidByte[3], HEX);
  
  rfid.PICC_HaltA();
  Serial.print("ID RFID : ");
  Serial.println(id);
  
  if (id == "0b51f20e" || // 1
  id == "0bf5f50e" || // 2
  id == "bb17ff0e" || // 3
  id == "eb5d340d" || // 4
  id == "ebc5430d"){ // 5
     
    if(lockdoor == true){
      lockdoor = false;
      Serial.println("<><> Access Accepted <><>"); 
      digitalWrite(13,1);                  
    }
    else if(lockdoor == false){
      lockdoor = true;
      digitalWrite(13,0);
    }

  }
  else {
    Serial.println();
    Serial.println("<!><!> Access Denied <!><!>");

    Serial.println("   O---------------------O ");
    Serial.println("   | O        O        O | ");
    Serial.println("   |   O      O      O   | ");
    Serial.println("   |     O    O    O     | ");
    Serial.println("   |       O  O  O       | ");
    Serial.println("   |         OOO         | ");
    Serial.println("   |       O  O  O       | ");
    Serial.println("   |     O    O    O     | ");
    Serial.println("   |   O      O      O   | ");
    Serial.println("   | O        O        O | ");
    Serial.println("   O---------------------O ");    
  }
  if(id == "0b51f20e"){
      nama = "Nomor 1";
  }
  Serial.print("NAMA : ");
  Serial.println(nama);
  id = "";
}

void printHex(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? "0" : "");
    Serial.print(buffer[i], HEX);
    id = id + String(buffer[i] < 0x10 ? "0" : "")+String(buffer[i], HEX);
  }
}
