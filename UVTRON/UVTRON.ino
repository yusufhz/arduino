#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
const int analogInPin = A0;  

int sensorValue = 0;       
int outputValue = 0;       

void setup() {
  Serial.begin(9600);
  pinMode(9,OUTPUT);
  lcd.begin();
  lcd.backlight();
  lcd.print("Hello, world!");
}

void loop() {
  lcd.clear();
  sensorValue = analogRead(analogInPin);
  outputValue = map(sensorValue, 0, 1023, 0, 255);
  lcd.print("sensor = " );
  lcd.print(sensorValue);
  delay(2);
  if(sensorValue >=500) digitalWrite(9,HIGH);
  delay(200);
  digitalWrite(9,LOW);
}
