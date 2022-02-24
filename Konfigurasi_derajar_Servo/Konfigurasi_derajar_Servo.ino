#include <Servo.h>
Servo myservo;

#define potpin A0
int val = 0;

void setup() {
  myservo.attach(3);
  Serial.begin(9600);
}

void loop() {
  val = analogRead(potpin);
  val = map(val, 0, 1023, 0, 180);
  myservo.write(val);
  Serial.print("Derajat = ");
  Serial.println(val);
  delay(15);
}

/*  bagian kanan awal 90
 *  bagian kanan \ tambah (+- 100)
 *  bagian kanan / kurang (+- 80)
 *  bagian kiri awal 90
 *  bagian kiri / kurang (+-80)
 *  bagian kiri \ tambah (+- 100)
 */ 
