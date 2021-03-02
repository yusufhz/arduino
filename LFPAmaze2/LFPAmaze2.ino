#include "robotDefines.h"

void reset() {
  mazeSolved = false;
  nullify(path);
  nullify(optimizedPath);
  pathLength = 0;
  optimizedPathLength = 0;
}

void setup(){
  pinMode(motorkiB, OUTPUT);
  pinMode(motorkaB, OUTPUT);
  pinMode(motorkiF, OUTPUT);
  pinMode(motorkaF, OUTPUT);
  pinMode(buzzer,OUTPUT);
  pinMode(kipas, OUTPUT);
  pinMode(starter, INPUT_PULLUP);
  Serial.begin(9600);
  pinMode(sensorapi, INPUT);
  digitalWrite(kipas, HIGH);
  digitalWrite(buzzer, LOW);
  
//  simpleMaze();
}


void loop(){
//  readsensor();
//  calculate_pid();
  if(robot_run == false){
    readsensor();
    if(digitalRead(starter) == 0){
      robot_run = true;
    }
  }
  else{
    Maze();
  }
}




