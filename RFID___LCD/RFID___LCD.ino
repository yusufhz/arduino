/*
 * Typical pin layout used:
 * -----------------------------------------------------------------------------------------
 *             MFRC522      Arduino       Arduino   Arduino    Arduino          Arduino
 *             Reader/PCD   Uno/101       Mega      Nano v3    Leonardo/Micro   Pro Micro
 * Signal      Pin          Pin           Pin       Pin        Pin              Pin
 * -----------------------------------------------------------------------------------------
 * RST/Reset   RST          9             5         D9         RESET/ICSP-5     RST
 * SPI SS      SDA(SS)      10            53        D10        10               10
 * SPI MOSI    MOSI         11 / ICSP-4   51        D11        ICSP-4           16
 * SPI MISO    MISO         12 / ICSP-1   50        D12        ICSP-1           14
 * SPI SCK     SCK          13 / ICSP-3   52        D13        ICSP-3           15
 */
#include <MFRC522.h>
#include <SPI.h>
#include <EEPROM.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define SS_PIN 10
#define RST_PIN 9
#define Buzzer 2

LiquidCrystal_I2C lcd (0x27, 16, 2);
MFRC522 rfid(SS_PIN, RST_PIN);
MFRC522::MIFARE_Key key;

byte data;
byte data_now;
byte Kartu_ID[4];

/* ------ Kartu yang terdaftar ----- */
byte kartu1[]={210, 155, 63, 91};
byte kartu2[]={32, 148, 58, 82};
byte kartu3[]={33, 171, 157, 01};
byte kartu4[]={20, 222, 88, 28};

void setup() {
  lcd.begin();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print(" Yusuf Maulana ");
  lcd.setCursor(0, 1);
  lcd.print("RFIDUINO Project");
  Serial.begin(9600);
  delay(2000);
  lcd.clear();
  Serial.begin(9600);
  pinMode (Buzzer, OUTPUT);
  Serial.begin(9600);
  SPI.begin();
  rfid.PCD_Init();

  for (byte i = 0; i < 6 ;i++){
    key.keyByte[i] = 0xFF;
  }
  Serial.println(F("Scan Kode dengan NUID"));
  Serial.print(F("Menggunakan kode : "));
  printHex(key.keyByte, MFRC522::MF_KEY_SIZE);
}

void loop() {
  if ( ! rfid.PICC_IsNewCardPresent())
    return;

  // Verify if the NUID has been readed
  if ( ! rfid.PICC_ReadCardSerial())
    return;

  Serial.print(F("PICC type: "));
  MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
  Serial.println(rfid.PICC_GetTypeName(piccType));

  // Check is the PICC of Classic MIFARE type
  if (piccType != MFRC522::PICC_TYPE_MIFARE_MINI &&  
    piccType != MFRC522::PICC_TYPE_MIFARE_1K &&
    piccType != MFRC522::PICC_TYPE_MIFARE_4K) {
    Serial.println(F("Bukan Kartu MFRC522."));
    return;
  }

  if (rfid.uid.uidByte[0] != Kartu_ID[0] || 
    rfid.uid.uidByte[1] != Kartu_ID[1] || 
    rfid.uid.uidByte[2] != Kartu_ID[2] || 
    rfid.uid.uidByte[3] != Kartu_ID[3] ) {
    Serial.println(F("Kartu Baru Terdeteksi"));

    // Store NUID into nuidPICC array
    for (byte i = 0; i < 4; i++) {
      Kartu_ID[i] = rfid.uid.uidByte[i];
      digitalWrite(Buzzer, HIGH);
      delay(200);
      digitalWrite(Buzzer, LOW);
    }
   
    Serial.println(F("The NUID tag is:"));
    Serial.print(F("In hex: "));
    printHex(rfid.uid.uidByte, rfid.uid.size);
    Serial.println();
    Serial.print(F("In dec: "));
    printDec(rfid.uid.uidByte, rfid.uid.size);
    Serial.println();
  }
  else Serial.println(F("Kartu Telah di Baca Tadi."));
  if (rfid.uid.uidByte[0] == kartu1[0] && 
  rfid.uid.uidByte[1] == kartu1[1] && 
  rfid.uid.uidByte[2] == kartu1[2] &&
  rfid.uid.uidByte[3] == kartu1[3]){
    lcd.setCursor(0,0);
    lcd.print("Nama  : ");
    lcd.setCursor(8,0);
    lcd.print("Fulan   ");
    lcd.setCursor(0,1);
    lcd.print("Kelas : ");
    for (int i = 8; i>= 9; i++){
      lcd.setCursor(i,0);
      lcd.print(" XII TKJ 3 ");
    }
  }
  else {
    for (int i = -2; i>= 16; i++){
      lcd.setCursor(i,0);
      lcd.print(" ID tidak terdaftar !!! ");
      lcd.setCursor(0,1);
      lcd.print("Peringatan  !!!");
      digitalWrite(Buzzer, HIGH);
      delay(100);
      lcd.setCursor(0,1);
      lcd.print("               ");
      digitalWrite(Buzzer, LOW);
      delay(100);
    }
  }
  // Halt PICC
  rfid.PICC_HaltA();

  // Stop encryption on PCD
  rfid.PCD_StopCrypto1();
}


/**
 * Helper routine to dump a byte array as hex values to Serial. 
 */
void printHex(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], HEX);
  }
}

/**
 * Helper routine to dump a byte array as dec values to Serial.
 */
void printDec(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], DEC);
//    data = buffer[i];
//    EEPROM.write(i,data);
//    data_now = EEPROM.read(i);
//    Serial.println(data_now);
  }
}
