void pencocokan(){
  Serial.print("data 1 = ");  Serial.println(L1);
  Serial.print("data 2 = ");  Serial.println(L2);
  Serial.print("data 3 = ");  Serial.println(L3);

  if (L1.equals(uid)) {
    Serial.println("LO1 cocok Selesai");
    delay(500);
    digitalWrite(relay1, 0);
    digitalWrite(indiL1, 1);
    delay(5000);
    digitalWrite(relay1, 1);
    digitalWrite(indiL1, 0);  
    masuk = false;
  }else {
    Serial.println("LO1 tidak cocok");
    digitalWrite(relay1, 1);
  }
  if (L2.equals(uid)) {
    Serial.println("LO2 cocok Selesai");
    delay(500);
    digitalWrite(relay2, 0);
    digitalWrite(indiL2, 1);
    delay(5000);
    digitalWrite(relay2, 1);
    digitalWrite(indiL2, 0);
    masuk = false;
  }else {
    Serial.println("LO2 tidak cocok");
    digitalWrite(relay2, 1);
  }
  if (L3.equals(uid)) {
    Serial.println("LO3 cocok Selesai");
    delay(500);
    digitalWrite(relay3, 0);
    digitalWrite(indiL3, 1);
    delay(5000);
    digitalWrite(relay3, 1);
    digitalWrite(indiL3, 0);
    masuk = false;
  }
  else {
    Serial.println("LO3 tidak cocok");
    digitalWrite(relay3, 1);
  }
  if(L1.equals(uid) || L2.equals(uid) || L3.equals(uid)){
     Serial.println();
    Serial.println(" --- Ready --- ");
    Serial.println();
  }
}
