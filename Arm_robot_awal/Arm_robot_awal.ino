#include <Servo.h>
#include "konfigurasi.h"

void setup() {
  Serial.begin(9600);
  kondisi_awal();

  Serial.println("Loading Data");
  for(int i = 0; i > 9 ; i++){
    Serial.print(".");
    delay(100);
  }
  Serial.println("I'm Ready");
  delay(200);

  gerak_awal();
}

void loop() {
  
}

void kondisi_awal(){
  servo_on();
  
  frontback.write(min_fb);
  updown.write(min_ud);
  rightleft.write(mid_rl);
  jepit.write(min_jp);
  delay(1000);
  
  servo_off();
}

void gerak_awal(){
   
  if (move_fb == true){
    frontback.attach(pin_fb);
    for(int i = min_fb ; i < mak_fb; i+=5){
      frontback.write(i);
      delay(40);
    }
    for(int i = mak_fb ; i > min_fb; i-=5){
      frontback.write(i);
      delay(40);
    }
    delay(100);
    frontback.detach();
  }//end

  if (move_ud == true){
    updown.attach(pin_ud);
    for(int i = min_ud ; i < mak_ud; i+=5){
      updown.write(i);
      delay(40);
    }
    for(int i = mak_ud ; i > min_ud; i-=5){
      updown.write(i);
      delay(40);
    }
    delay(100);
    updown.detach();
  }//end

  if (move_rl == true){
    rightleft.attach(pin_rl);
    for(int i = mid_rl ; i < mak_rl; i+=6){
      rightleft.write(i);
      delay(30);
    }
    for(int i = mak_rl ; i > min_rl; i-=6){
      rightleft.write(i);
      delay(30);
    }
    for(int i = min_rl ; i < mid_rl; i+=6){
      rightleft.write(i);
      delay(30);
    }
    rightleft.detach();
    delay(100);
  }//end

  if(move_jp == true){
    jepit.attach(pin_jp);
    for(int i = min_jp ; i < mak_jp; i+=5){
      jepit.write(i);
      delay(40);
    }
    delay(100);
    for(int i = mak_jp ; i > min_jp; i-=5){
      jepit.write(i);
      delay(40);
    }
    delay(100);
    jepit.detach();
  }
}

void servo_on(){
  frontback.attach(pin_fb);
  updown.attach(pin_ud);
  rightleft.attach(pin_rl);
  jepit.attach(pin_jp);
}

void servo_off(){
  frontback.detach();
  updown.detach();
  rightleft.detach();
  jepit.detach();
}
