#define pinS 2
boolean ReadS = true;
boolean Running = false;
boolean KeLed = LOW;
void setup() {
  pinMode(pinS, INPUT_PULLUP);
  pinMode(13, OUTPUT);
  pinMode(7, OUTPUT);  
}

void loop() {
  ReadS = digitalRead(pinS);
  if(ReadS ==  false && Running == false){
    Running = true;
    for(int i = 0; i < 20;i++){
      if(KeLed == LOW){
        KeLed = HIGH;
      }else{
        KeLed = LOW;
      }
      digitalWrite(7, KeLed);
      delay(100);
    }
  }
  if(Running == true){
    for(int i = 0; i < 10;i++){
      if(KeLed == LOW){
        KeLed = HIGH;
      }else{
        KeLed = LOW;
      }
      digitalWrite(13, KeLed);
      delay(100);
    }
  }
}
