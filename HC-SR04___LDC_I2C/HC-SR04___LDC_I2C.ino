#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define led 13
#define vcc 8
#define gnd 11

LiquidCrystal_I2C lcd (0x27, 16, 2);

const int triggerPin = 2;
const int echoPin = 3;

long duration;
int distance;

void setup() {
  pinMode (vcc, OUTPUT);
  pinMode (gnd, OUTPUT);
  digitalWrite (vcc, 1);
  digitalWrite (gnd, 0);
  pinMode(led, OUTPUT);
  lcd.begin();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print(" Yusuf Maulana ");
  lcd.setCursor(0, 1);
  lcd.print("Arduino Project");
  Serial.begin(9600);
  delay(2000);
  lcd.clear();

  pinMode (led, OUTPUT);
  pinMode (triggerPin, OUTPUT);
  pinMode (echoPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  // ------ SENSOR ULTRASONIC --------//
  digitalWrite (triggerPin, LOW);
  delayMicroseconds(2);

  digitalWrite(triggerPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin,LOW);

  duration = pulseIn(echoPin,HIGH);
  distance = duration*0.034/2;
  if(distance >= 3){
    distance = distance +1; 
  }
  else if(distance==4){
    distance=4;
  }
  else if(distance < 3){
    distance = duration*0.034/2;
  }

  Serial.print("Distance : ");
  Serial.print(distance);
  Serial.println("cm");
  //-------- END SENSOR ULTRASONIC ------//
  //-------- LCD -------//
  lcd.setCursor(0, 0);
  lcd.print("Jarak : ");
  if(distance < 10){
    lcd.setCursor(10,0);
    lcd.print("  ");
  }
  if(distance < 100){
    lcd.setCursor(11,0);
    lcd.print(" ");
  }
  lcd.setCursor(9, 0);
  lcd.print(distance);
  lcd.setCursor(12, 0);
  lcd.print(" cm");
  lcd.setCursor(1, 1);
  lcd.print("Arduino Project ");  
  //------ END LCD -------//
//  //------ LED --------
//  if(distance >= 100){
//    digitalWrite(hijau, HIGH);
//    digitalWrite(kuning, LOW);
//    digitalWrite(merah, LOW);
//  }
//  if(distance >= 50 && distance < 100){
//    digitalWrite(hijau, LOW);
//    digitalWrite(kuning, HIGH);
//    digitalWrite(merah, LOW);
//  }
//  if(distance < 30 ){
//    digitalWrite(hijau, LOW);
//    digitalWrite(kuning, LOW);
//    digitalWrite(merah, HIGH);
//  }
  if(distance < 30){
    digitalWrite(led, 1);
    delay(200);
    digitalWrite(led, 0);
    delay(200);
  }
}
