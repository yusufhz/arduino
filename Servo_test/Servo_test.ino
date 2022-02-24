#include <Servo.h>
Servo myservo;
void setup() {
  // put your setup code here, to run once:

}

void loop() {
  myservo.attach(2);
  myservo.write(90);
  delay(200);
  myservo.write(95);
  delay(200);
  myservo.write(100);
  delay(200);
  myservo.write(110);
  delay(200);
  myservo.detach();
}
