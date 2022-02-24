#define BTN1 5
#define BTN2 6
#define BTN3 7
#define IN1 10
#define IN2 11
#define EN1 9
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
    analogWrite(IN1, 150);
    analogWrite(IN2,0);
    Serial.println("IN 1 ON CW");
  }
  if(digitalRead(BTN2) == 1){
    analogWrite(IN1,0);
    analogWrite(IN2,150);
    Serial.println("IN 2 ON CCW");
  }
  if(digitalRead(BTN3) == 1){
    analogWrite(IN1,0);
    analogWrite(IN2,0);
    Serial.println("IN 3 ON STOP");
  }
}
