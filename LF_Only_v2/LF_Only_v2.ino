#include <EEPROM.h>

#define motorkiF 9
#define motorkiB 11
#define motorkaF 6
#define motorkaB 10


// PID
float Kp;
float Ki;
float Kd;

int flag;

float error = 0, error2 = 0, P = 0, I = 0, D = 0, PID_value = 0;
float previous_error = 0, previous_I = 0;

float left_motor_speed;
float right_motor_speed;

byte addMspeed = 1;
byte MotorSpeed = EEPROM.read(addMspeed);

boolean runMode = false;

#include "readSensor.h"
#include "button.h"

char dataku;
void setup() {
  // put your setup code here, to run once:
  pinMode(starter, INPUT_PULLUP);
  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  pinMode(button3, INPUT_PULLUP);
  pinMode(button4, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  if(runMode == false){
    Serial.println("Masih Diam");
    readsensor();
    Serial.print("Sensor : ");
    Serial.println(data,BIN);  

    if(digitalRead(starter) == 0){
      runMode = true;
      MotorSpeed = EEPROM.read(addMspeed);
      Serial.print("Motor_Speed : ");
      Serial.println(MotorSpeed);
   }
   else{
      runMode = false;
   }
    if(Serial.available()){
      dataku = Serial.read();
    }
    if(digitalRead(button1) == 0 || dataku == 'a'){
      MotorSpeed = MotorSpeed + 1;
      EEPROM.write(addMspeed, MotorSpeed);
      Serial.print("Motor_Speed : ");
      Serial.println(MotorSpeed);
      delay(500);
    }
    if(digitalRead(button2) == 0 || dataku == 'b'){
      MotorSpeed--;
      EEPROM.write(addMspeed, MotorSpeed);
      Serial.print("Motor_Speed : ");
      Serial.println(MotorSpeed);
      delay(500);
    }
    dataku = 0;
  }
  if(runMode == true){
   Serial.println("Lari.......");
   readsensor();
   if (error == 100){
        sudut_kiri();
        delay(200);
        readsensor();
      while (error == 0)
      {
        sudut_kiri();
        readsensor();
      }
    }
    else if (error == 101){
        sudut_kanan();
        delay(200);
        readsensor();
      while (error == 0)
      {
        sudut_kanan();
        readsensor();
      }
    }
    else if (error == 102){
      stop_break();
    }
    else {
      calculate_pid();
    }
//    readsensor();
//    calculate_pid();
//    
//    if(data == 0b001100){
//      forward();
//      Serial.println("Maju");
//    }
//    else if(data == 0b011000){
//      belok_kiri();
//      Serial.println("Kiri");
//    }
//    else if(data == 0b110000){
//      sudut_kiri();
//      Serial.println("90 Kiri");
//    }
//    else if(data == 0b000110){
//      belok_kanan();
//      Serial.println("Kanan");
//    }
//    else if(data == 0b000011){
//      sudut_kanan();
//      Serial.println("90 Kanan");
//    }
//    else if(data == 0b111111){
//      stop_break();
//      Serial.println("Stop");
//    }
 }// run mode
}
void forward(){
  analogWrite(motorkiF, left_motor_speed);
  analogWrite(motorkiB, 0);
  analogWrite(motorkaF, right_motor_speed);
  analogWrite(motorkaB, 0); 
}

void belok_kanan(){
  analogWrite(motorkiF, left_motor_speed);
  analogWrite(motorkiB, 0);
  analogWrite(motorkaF, 0);
  analogWrite(motorkaB, 0);
}
void belok_kiri(){
  analogWrite(motorkiF, 0);
  analogWrite(motorkiB, 0);
  analogWrite(motorkaF, right_motor_speed);
  analogWrite(motorkaB, 0);
}

void sudut_kiri(){
  analogWrite(motorkiF, 0);
  analogWrite(motorkiB, MotorSpeed);
  analogWrite(motorkaF, MotorSpeed);
  analogWrite(motorkaB, 0);
}

void sudut_kanan(){
  analogWrite(motorkiF, MotorSpeed);
  analogWrite(motorkiB, 0);
  analogWrite(motorkaF, 0);
  analogWrite(motorkaB, MotorSpeed);
}

void stop_break(){
  analogWrite(motorkiF, 0);
  analogWrite(motorkiB, 0);
  analogWrite(motorkaF, 0);
  analogWrite(motorkaB, 0);
}

void calculate_pid()
{ 
  //int MotorSpeedKa = 100;
  //int MotorSpeedKi = 110;

  Kp = 9;
  Ki = 0.5;
  Kd = 3.5;

  P = error;
  I = I + previous_I;
  D = error - previous_error;

  PID_value = (Kp * P) + (Ki * I) + (Kd * D);

  left_motor_speed = MotorSpeed - PID_value;
  right_motor_speed = MotorSpeed + PID_value;

  // The motor speed should not exceed the max PWM value
  left_motor_speed = constrain(left_motor_speed, 0, 100);
  right_motor_speed = constrain(right_motor_speed, 0, 100);

    Serial.print(PID_value);
    Serial.print("\t");
    Serial.print(left_motor_speed);
    Serial.print("\t");
    Serial.println(right_motor_speed);
  forward();
  flag = 0;
  previous_I = I;
  previous_error = error;
}
