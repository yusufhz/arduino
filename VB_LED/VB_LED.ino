/* === Kontrol LED via VB 6 ===
 */
#define Led1 13
#define Led2 12
#define Led3 11
#define Led4 10

char BacaSerial;
int Tunda = 100;
void setup() {
  Serial.begin(9600);
  
  pinMode(Led1, OUTPUT);
  pinMode(Led2, OUTPUT);
  pinMode(Led3, OUTPUT);
  pinMode(Led4, OUTPUT);

  digitalWrite(Led1, LOW);
  digitalWrite(Led2, LOW);
  digitalWrite(Led3, LOW);
  digitalWrite(Led4, LOW);
  
}

void loop() {
  if(Serial.available()){
    BacaSerial = Serial.read();
    // ON 1 1
  }
      if(BacaSerial == 'a'){
      digitalWrite(Led1, HIGH);
    }
    if(BacaSerial == 'b'){
      digitalWrite(Led2, HIGH);
    }
    if(BacaSerial == 'c'){
      digitalWrite(Led3, HIGH);
    }    
    if(BacaSerial == 'd'){
      digitalWrite(Led4, HIGH);
    }
    // OFF 1 1
    if(BacaSerial == 'A'){
      digitalWrite(Led1, LOW);
    }
    if(BacaSerial == 'B'){
      digitalWrite(Led2, LOW);
    }
    if(BacaSerial == 'C'){
      digitalWrite(Led3, LOW);
    }
    if(BacaSerial == 'D'){
      digitalWrite(Led4, LOW);
    }
    // ON ALL
    if(BacaSerial == 'e'){
      digitalWrite(Led1, HIGH);
      digitalWrite(Led2, HIGH);
      digitalWrite(Led3, HIGH);
      digitalWrite(Led4, HIGH);
    }
    // OFF ALL
    if(BacaSerial == 'E'){
      digitalWrite(Led1, LOW);
      digitalWrite(Led2, LOW);
      digitalWrite(Led3, LOW);
      digitalWrite(Led4, LOW);
    }
    // Running LED
    if(BacaSerial == 'r'){
      digitalWrite(Led1, HIGH);
      delay(Tunda);
      digitalWrite(Led1, LOW);
      digitalWrite(Led2, HIGH);
      delay(Tunda);
      digitalWrite(Led2, LOW);
      digitalWrite(Led3, HIGH);
      delay(Tunda);
      digitalWrite(Led3, LOW);
      digitalWrite(Led4, HIGH);
      delay(Tunda);
      digitalWrite(Led4, LOW);
    }
    if(BacaSerial == 'R'){
      BacaSerial = 'E';
    }
  // put your main code here, to run repeatedly:
}
