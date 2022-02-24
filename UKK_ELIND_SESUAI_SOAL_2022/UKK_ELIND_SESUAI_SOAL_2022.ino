#define BTN1 11
#define BTN2 12
#define BTN3 13
#define IN1 6
#define IN2 5
#define EN1 4
void setup() {
  pinMode (BTN1, INPUT);
  pinMode (BTN2, INPUT);
  pinMode (BTN3, INPUT);
  pinMode (EN1, OUTPUT);
  digitalWrite(EN1, 1);
  Serial.begin(9600);
  Serial.println("Program SIAP");
}

void loop() {
  if(digitalRead(BTN1) == 1){
    analogWrite(IN1, 255);
    analogWrite(IN2,0);
    Serial.println("IN 1 ON CW");
  }
  if(digitalRead(BTN2) == 1){
    analogWrite(IN1,0);
    analogWrite(IN2,255);
    Serial.println("IN 2 ON CCW");
  }
  if(digitalRead(BTN3) == 1){
    analogWrite(IN1,0);
    analogWrite(IN2,0);
    Serial.println("IN 3 ON STOP");
  }
}
