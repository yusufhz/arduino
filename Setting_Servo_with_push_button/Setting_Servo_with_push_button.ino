#include <Servo.h>
Servo myservo;
int up;
int dw;
int drj=90;
void setup(){
  myservo.attach(9);
  pinMode(2,INPUT);
  pinMode(3,INPUT);
  myservo.write(drj);
  Serial.begin(9600);
}
void loop(){
  myservo.write(drj);
  up = digitalRead(2);
  dw = digitalRead(3);
  if( up == HIGH){
    drj=+10;
  }
  if( dw == HIGH){
    drj=-10;
  }
  Serial.print("Derajat Servo = ");
  Serial.println(drj);
  delay(200);
}

