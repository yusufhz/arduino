// Library
#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// I/O
#define Sensor1 2
#define Sensor2 3
#define Sensor3 4
#define Sensor4 5

#define Conveyor 6

Servo metal;
Servo non_metal;

LiquidCrystal_I2C lcd (0x27, 16, 2);

// Servo
int metal_on = 45;
int non_metal_on = 45;
int metal_off = 0;
int non_metal_off = 0;

// Counter
int count_begin = 0;
int count_end = 0;
int count_metal = 0;
int count_non_metal = 0;

//Time
unsigned long last_time1 = 0;
unsigned long last_time2 = 0;
unsigned long last_time3 = 0;
unsigned long last_time4 = 0;
unsigned long last_time5 = 0;
unsigned long last_time6 = 0;

//Sensor_Read
boolean Sensor1_read = 0;
boolean Sensor2_read = 0;
boolean Sensor3_read = 0;
boolean Sensor4_read = 0;

void setup() {
  lcd.begin();
  Serial.begin(9600);
  metal.attach(9);
  non_metal.attach(10);
  pinMode (Sensor1, INPUT);
  pinMode (Sensor2, INPUT);
  pinMode (Sensor3, INPUT);
  pinMode (Sensor4, INPUT);
  
}

void loop() {
  millis();
  if(millis()-last_time1 >= 1000){
    last_time1 = millis();
    Sensor1_read = digitalRead(Sensor1);
    Sensor2_read = digitalRead(Sensor2);
    Sensor3_read = digitalRead(Sensor3);
  }

  if(millis()-last_time2 >= 1000){
    last_time2 = millis();
    if(Sensor1_read){
      count_begin = count_begin + 1;
      count_begin = count_begin - count_metal;
      count_begin = count_begin - count_non_metal;
    }
    if(count_begin > 0){
      digitalWrite(Conveyor, HIGH);
    }else{
      digitalWrite(Conveyor, LOW);
    }
  }

  if(millis()-last_time3 >= 1000){
    last_time3 = millis();
    if(Sensor2_read){
      digitalWrite(Conveyor, HIGH);
      count_metal = count_metal + 1;
      for(int i = 0; i <= metal_on; i+=5){
        metal.write(i);
        delay(10);
      }
      delay(200);
      for(int i = metal_off; i > 0; i-=5){
        metal.write(i);
        delay(10);
      }
      delay(1000);
    }
  }

  if(millis()-last_time4 >= 1000){
    last_time4 = millis();
    if(Sensor3_read){
      digitalWrite(Conveyor, HIGH);
      count_non_metal = count_non_metal + 1;
      for(int i = 0; i <= non_metal_on; i+=5){
        non_metal.write(i);
        delay(10);
      }
      delay(200);
      for(int i = non_metal_off; i > 0; i-=5){
        non_metal.write(i);
        delay(10);
      }
      delay(1000);
    }
  }

  if(millis()-last_time5 >= 1000){
    last_time5 = millis();
    lcd.setCursor(0,0);
    lcd.print("     Mesin      ");
    lcd.setCursor(0,1);
    lcd.print("M = ");

    if(count_metal < 10){
      lcd.setCursor(5,1);
      lcd.print("  ");
    }
    
    lcd.setCursor(4,1);
    lcd.print(count_metal);
    lcd.setCursor(8,1);
    lcd.print("NM = ");
    
    if(count_non_metal < 10){
      lcd.setCursor(14,1);
      lcd.print("  ");
    }
    
    lcd.print(count_metal);
    lcd.setCursor(13,1);
    
    Serial.println("     Mesin      ");
    Serial.print("M = ");
    Serial.print(count_metal);
    Serial.print("NM = ");
    Serial.println(count_non_metal);
  }
}
