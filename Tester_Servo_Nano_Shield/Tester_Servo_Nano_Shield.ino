#include <Servo.h>

Servo Atas ; Servo Tengah ; Servo Bawah ; 
void setup() {
  Serial.begin(9600);  
  Atas.attach(10); Tengah.attach(12); Bawah.attach (11);
  delay(2000);
  Serial.begin(9600); 
  Atas.write(90); 
}

void loop() {
//  Atas.write(60); Tengah.write(90); Bawah.write (90);
//  delay(200);
//  Atas.write(40); Tengah.write(60); Bawah.write (60);
//  delay(200);
//  Atas.write(40); Tengah.write(90); Bawah.write (90);
//  delay(200);
}
