void ceknode() {
  if (Serial3.available() > 0) {
    char inChar = (char)Serial3.read();
    dataIn += inChar;
    delay(20);
//    Serial.print("dataIn     : ");Serial.println(dataIn);
//    Serial.print("dataInLast : ");Serial.println(dataInLast);
    
    if (inChar == '\n' && dataInLast != dataIn) {
        parsing = true;
    }
  }
  if (parsing) {
    dataInLast = dataIn;
    parsingData();
    parsing = false;
    dataIn="";
  }
}
