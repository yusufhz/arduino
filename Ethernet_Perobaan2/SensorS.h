// --- Pintu BEGIN -----
  #define buka 2 //pwm
  #define tutup 3 //pwm
// --- Pintu END -----
// --- Sensor BEGIN ------
  // ----- Suhu BEGIN
  #define pinSuhu A0
  int ReadSuhu = 0;
  // ----- Suhu END
  
  // ----- PIR BEGIN
  #define ledPin 22
  #define inputPin 23
  #define Buzzer 3
  int pirState = LOW;
  int ReadPIR = 0;
  int val;
  unsigned long waktuL5 = 0;
  // ----- PIR END
  
  // ----- KEYPAD BEGIN
  // ----- KEYPAD END

  // ----- RFID BEGIN
  /*
   * MOSI 51
   * MISO 50
   */
  #define SS_PIN 53 // SDA
  #define RST_PIN 49 // RST
  MFRC522 rfid(SS_PIN, RST_PIN);
  MFRC522::MIFARE_Key key;
  String id;
  boolean lockdoor = true;
  // ----- RFID END

boolean SSuhu, SPintu, SMotion = false;
// --- Sensor END ------

// --- void tambahan ------
void suhu(){
  ReadSuhu = analogRead(pinSuhu);
  Serial.println(ReadSuhu);
}

void pirmotion(){
  val = digitalRead(inputPin);
  delay(1);
  if (val == HIGH) {
    digitalWrite(ledPin, HIGH);
    delay(1);
    if (pirState == LOW) {
      Serial.println("Terdeteksi suatu pergerakan!");
      SMotion = true;
      pirState = HIGH;
    }
  } else {
      digitalWrite(ledPin, LOW);
      delay(1);  
      if (pirState == HIGH){
        Serial.println("Motion ended!");
        SMotion = false;
        pirState = LOW;
    }
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
  id == "3b7bd7c0" || // Yusuf
  id == "20d5473b" || // Fadly
  id == "cb84dcc0" ||
  id == "okoc"){ // Yamayuki
    if(lockdoor == true){
      lockdoor = false;
      SPintu = false;
    }
    else if(lockdoor == false){
      lockdoor = true;
      SPintu = true;
    }
  }
  id = "0";
}
// --- void tambahan END ---

