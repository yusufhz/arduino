// Ahmad Bukhari
// Yusuf Maulana

#include <Servo.h>
Servo Servokami;

int ledPin = 13;     
int inputPin = 9;   
int pirState = LOW; 
int val = 0;        

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(inputPin, INPUT);
  Servokami.attach(8);
  Servokami.write(0);
}
void loop(){
  val = digitalRead(inputPin);
  if ((val == HIGH) && (pirState == LOW)) {
    digitalWrite(ledPin, HIGH);
    Serial.println("Terdeteksi gerakan!");
    pirState = HIGH;
    Servokami.write(90); // buka pintu  
    delay(3000);
  }
  if((val == LOW) && (pirState == HIGH)){
    digitalWrite(ledPin, LOW);
    Serial.println("Tidak ada gerakan!");
    pirState = LOW;
    Servokami.write(0);
  }
}
