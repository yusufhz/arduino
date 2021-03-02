void padamkan (){
  if(padam==true){
  int i;
  while (i < 3){
  for(i = 0; i < 3; i++){
    unsigned long previousMillis = 0;
    const long interval = 1000; 
    unsigned long currentMillis = millis();
   if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;
    int ApiPadam = digitalRead(sensorapi);
      if(ApiPadam == HIGH){
        digitalWrite(kipas, LOW);
        digitalWrite(buzzer, HIGH);
        }
      else if(ApiPadam == LOW){
        digitalWrite(kipas, HIGH);
        digitalWrite(buzzer, LOW);
      }
    }
   }
  }
 }
}
