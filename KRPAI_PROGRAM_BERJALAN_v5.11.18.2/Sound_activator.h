#define pinSoundIN 22
#define pinLedSound 23
boolean ReadS = true;
/* Jika Pake Sound : 
 * Running = false;
 * Jika Tidak Pake Sound : 
 * Running = true;
 */
boolean Running = false;
boolean KeLed = LOW;

void activation(){
  ReadS = digitalRead(pinSoundIN);
  if(ReadS ==  false && Running == false){
    Running = true;
    lcd.setCursor(0, 1);
    lcd.print("       OK      ");
    for(int i = 0; i < 10;i++){
      if(KeLed == LOW){
        KeLed = HIGH;
      }
      else {
        KeLed = LOW;
      }
      digitalWrite(pinLedSound, KeLed);
      delay(100);
    }
  }
}
