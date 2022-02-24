#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd (0x20, 16, 2);

#define Sensor1 2
#define Sensor2 3
#define Sensor3 4
#define Sensor4 5
#define Sensor5 6

#define Pompa 7

int Sensor1_read = 0;
int Sensor2_read = 0;
int Sensor3_read = 0;
int Sensor4_read = 0;
int Sensor5_read = 0;

void setup() {
  pinMode (Sensor1, INPUT);
  pinMode (Sensor2, INPUT);
  pinMode (Sensor3, INPUT);
  pinMode (Sensor4, INPUT);
  pinMode (Sensor5, INPUT);
  pinMode (Pompa, OUTPUT);
  
  lcd.begin();
  Serial.begin(9600);

  lcd.setCursor(0,0);
  lcd.print("Gallon        ");
  delay(500);
}
unsigned long time_now;
unsigned long time_last1;
unsigned long time_last2;
unsigned long time_last3;
unsigned long time_last4;
unsigned long time_last5;

void loop() {
  time_now = millis();
  if(time_now-time_last1 >= 1000){
    time_last1 = time_now;
    Sensor1_read = digitalRead(Sensor1);
    Sensor2_read = digitalRead(Sensor2);
    Sensor3_read = digitalRead(Sensor3);
    Sensor4_read = digitalRead(Sensor4);
    Sensor5_read = digitalRead(Sensor5);
  }
  if(time_now - time_last2 >= 1000){
    time_last2 = time_now;
    if(Sensor5_read){
      digitalWrite(Pompa, 0);
    }else if(Sensor4_read){
      digitalWrite(Pompa, 1);
    }else if(Sensor3_read){
      digitalWrite(Pompa, 1);
    }else if(Sensor2_read){
      digitalWrite(Pompa, 1);
    }else if(Sensor1_read){
      digitalWrite(Pompa, 1);
    }else{
      digitalWrite(Pompa, 1);
    }
  }
  if(time_now - time_last3 >= 1000){
   time_last3 = time_now;
   if(Sensor5_read && Sensor4_read){
      lcd.setCursor(0,0);
      lcd.print(" Galon Penuh    ");
      lcd.setCursor(0,1);
      lcd.print(" Pompa Mati     ");
      Serial.println("  Galon Penuh   ");
      Serial.println("  Pompa Mati    ");
      delay(200);
    }else if(Sensor4_read && !Sensor5_read){
      lcd.setCursor(0,0);
      lcd.print(" Galon 80%      ");
      lcd.setCursor(0,1);
      lcd.print(" Pompa Aktif    ");
      Serial.println("  Galon 80%     ");
      Serial.println("  Pompa Aktif   ");    
      delay(200);
    }else if(Sensor3_read && !Sensor4_read){
      lcd.setCursor(0,0);
      lcd.print(" Galon 60%      ");
      lcd.setCursor(0,1);
      lcd.print(" Pompa Aktif    ");
      Serial.println("  Galon 60%     ");
      Serial.println("  Pompa Aktif   ");    
      delay(200);
    }else if(Sensor2_read && !Sensor3_read){
      lcd.setCursor(0,0);
      lcd.print(" Galon 40%      ");
      lcd.setCursor(0,1);
      lcd.print(" Pompa Aktif    ");
      Serial.println("  Galon 40%     ");
      Serial.println("  Pompa Aktif   ");    
      delay(200);
    }else if(Sensor1_read && !Sensor2_read){
      lcd.setCursor(0,0);
      lcd.print(" Galon 20%       ");
      lcd.setCursor(0,1);
      lcd.print(" Pompa Aktif    ");
      Serial.println("  Galon 20%      ");
      Serial.println("  Pompa Aktif   ");    
      delay(200);
    }else{
      lcd.setCursor(0,0);
      lcd.print(" Galon Kosong   ");
      lcd.setCursor(0,1);
      lcd.print(" Pompa Aktif    ");
      Serial.println("  Galon Kosong  ");
      Serial.println("  Pompa Aktif   ");    
    }
  }
}
