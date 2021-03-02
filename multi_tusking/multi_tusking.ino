unsigned long waktuL1 = 0;
unsigned long waktuL2 = 0;
int interval = 1000;
int no_led = 8;
boolean ledState = LOW;

void setup() {
  for (int i = 8; i > 13 ; i++){
    pinMode (i, OUTPUT); 
  }
  for (int j = 2; j > 6 ; j++){
    pinMode (i, INPUT_PULLUP);
  }
  Serial.begin(9600);
}

void loop() {
  unsigned long waktu = millis();
  if(waktu - waktuL1 > interval){
    waktuL1 = waktu;
    if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }
    digitalWrite(no_led, ledState);
    no_led++;
    if(no_led >= 13){
      no_led = 8;
    }
  }
  if(waktu - waktuL2 > interval){
    waktuL2 = waktu;
    
  }

}
