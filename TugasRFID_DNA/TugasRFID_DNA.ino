  // ----- SERVO BEGIN
#include <Servo.h>
Servo PintuParkir;
  // ----- SERVO END
  // ----- RFID BEGIN
  /* Mega2560 ---- UNO
   *  
   * MOSI 51  ---- 
   * MISO 50  ---- 
   * SCK      ---- 
   */
#include <MFRC522.h>   
#define SS_PIN 53 // SDA
#define RST_PIN 49 // RST
  MFRC522 rfid(SS_PIN, RST_PIN);
  MFRC522::MIFARE_Key key;
  String id;
  boolean AlatMode = false;
  // ----- RFID END
  // ----- PIR BEGIN
  int InputPir = 6;
  int pirState = LOW;
  int ReadPIR = 0;
  int val;
  // ----- PIR END
  // ----- LCD BEGIN
#include <Wire.h>
#include <LiquidCrystal_I2C.h>  
  LiquidCrystal_I2C lcd(0x27, 16, 2);
  // ----- LCD END

#define LedPin 2
#define PintuBuka 3
#define PintuTutup 4

// servopin 5

void setup() {
  SPI.begin();
  rfid.PCD_Init();
  lcd.begin();
  Serial.begin(9600);
  
  PintuParkir.attach(5);
  lcd.setCursor(0,0);
  lcd.print("Loading");
  lcd.setCursor(0,8);
  for(int t = 0; t > 8;t++){
    lcd.print(".");
    delay(100);
  }
  lcd.setCursor(0,0);
  lcd.print("> Sistem Aktif <");
  lcd.setCursor(0,1);
  lcd.print("Office Automasi ");
  delay(2000);
  lcd.clear();
}

void loop() {
  
  if(AlatMode == true){
    
  }
  else{
    Serial.println(" Alat Dimatikan ");
    lcd.setCursor(0,0);
    lcd.print(">>  OFF MODE  <<");
    lcd.setCursor(0,1);
    lcd.print(">>  TAP HERE  <<");
    rfid_card();
  }
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
  id = String(rfid.uid.uidByte[0], HEX) + 
  String(rfid.uid.uidByte[1], HEX) + 
  String(rfid.uid.uidByte[2], HEX) +
  String(rfid.uid.uidByte[3], HEX);
  rfid.PICC_HaltA();
  Serial.println(id);
  if (id == "21ab9d1" || // master
  id == "3b7bd7c0" || // admin1
  id == "20d5473b" || // admin2
  id == "cb84dcc0" ){ // admin3
    if(AlatMode == false){
      AlatMode = true;
      if(id == "21ab9d1"){
        id = "Master Max";
      }
      else if(id == "3b7bd7c0"){
        id = "Admin 1";
      }
      else if(id == "20d5473b"){
        id = "Admin 2";
      }
      else if(id == "cb84dcc0"){
        id = "Admin 3";
      }
      Serial.println("Welcome : " + String(id));
      lcd.setCursor(0,0);
      lcd.print(" Akses Diterima ");
      delay(200);
      lcd.setCursor(0,0);
      lcd.print("    Welcome     ");
      lcd.setCursor(0,1);
      lcd.print(id);
    }
    else if(AlatMode == true){
      AlatMode = false;
      Serial.println(" Alat Dimatikan ");
      lcd.setCursor(0,0);
      lcd.print(" Alat Dimatikan ");    
    }
  }
  else{
    Serial.println("Akses Dilarang !!!");
    lcd.setCursor(0,0);
    lcd.print("Akses Ditolak !!!");
    delay(100);
    lcd.clear();
  }
  id = "0";
}

void pirmotion(){
  val = digitalRead(InputPir);
  delay(1);
  if (val == HIGH) {
    digitalWrite(LedPin, HIGH);
    delay(1);
    if (pirState == LOW) {
      Serial.println("Terdeteksi suatu pergerakan!");
      pirState = HIGH;
    }
  }
  else {
      digitalWrite(LedPin, LOW);
      delay(1);  
      if (pirState == HIGH){
        Serial.println("Motion ended!");
        pirState = LOW;
    }
  }
}

