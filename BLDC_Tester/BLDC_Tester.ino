#include <Servo.h>
Servo bldc;
int speedbldc = 50;
void setup() {
  Serial.begin(115200);
  bldc.attach(9);
  bldc.write(30);
  delay(3000);
  // put your setup code here, to run once:

}

void loop() {
  if(Serial.available()){
    char datame = Serial.read();
    if(datame == 'a'){
      speedbldc+=5;
    }
    if(datame == 'b'){
      speedbldc-=5;
    }
    datame="";
  }
  Serial.println(speedbldc);
  bldc.write(speedbldc);
  delay(15);
  // put your main code here, to run repeatedly:

}
