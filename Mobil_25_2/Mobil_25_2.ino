#include <Adafruit_NeoPixel.h>

#define PIN 11 // On Trinket or Gemma, suggest changing this to 1

#define NUMPIXELS 8 // Popular NeoPixel ring size

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#define DELAYVAL 500
#define kelakson 12

int buzz = 12;
int pol = 0;

char dataread;
char datalast;
#include <SoftwareSerial.h>
SoftwareSerial data(7,8);//rx,tx

void setup() {
  data.begin(9600);
  Serial.begin(9600);
  Serial.println("Arduino N2 Ready");
  pixels.begin();
  pinMode(kelakson, OUTPUT);
  delay(100);
  All_On();
  delay(2000);
  All_off();
}

void loop() {
  Serial.println("pol = " + String(pol));
  if(Serial.available() || data.available()){
    if(Serial.available()>0){
      dataread = Serial.read();
      Serial.println(dataread);
    }else{
      datalast = data.read();
      Serial.println(datalast);
    }
    if(datalast == 'k' || dataread == 'k'){
      digitalWrite(kelakson, 1);
    }
    else if(datalast == '2' || dataread == '2'){
      //police();
    }
    else if(datalast == '3' || dataread == '3'){
      //police2();
    }
    else{
      digitalWrite(kelakson, 0);
    }
    if(datalast == '2'){
      for(int i = 0; i < 2; i++){
        police();
      }
      All_off();
    }
    if(datalast == '3'){
      for(int i = 0; i < 2; i++){
        police2();
      }
      All_off();
    }
  }//end serial.available
}//end loop
void Kiri(){
  pixels.clear(); 
  pixels.setPixelColor(0, pixels.Color(255,0, 0));
  pixels.setPixelColor(1, pixels.Color(255, 0, 0));
  pixels.setPixelColor(2, pixels.Color(255, 0, 0));
  pixels.setPixelColor(3, pixels.Color(255, 0, 0));
  pixels.show();
}

void Kiri2(){
  pixels.clear(); 
  pixels.setPixelColor(0, pixels.Color(0,0, 255));
  pixels.setPixelColor(1, pixels.Color(0, 0, 255));
  pixels.setPixelColor(2, pixels.Color(0, 0, 255));
  pixels.setPixelColor(3, pixels.Color(0, 0, 255));
  pixels.show();
}

void Kanan(){
  pixels.clear();
  pixels.setPixelColor(4, pixels.Color(0, 0, 255));
  pixels.setPixelColor(5, pixels.Color(0, 0, 255));
  pixels.setPixelColor(6, pixels.Color(0, 0, 255));
  pixels.setPixelColor(7, pixels.Color(0, 0, 255));
  pixels.show();
}

void All_off(){
  pixels.clear(); 
  pixels.setPixelColor(0, pixels.Color(0,0, 0));
  pixels.setPixelColor(1, pixels.Color(0, 0, 0));
  pixels.setPixelColor(2, pixels.Color(0, 0, 0));
  pixels.setPixelColor(3, pixels.Color(0, 0, 0));
  pixels.setPixelColor(4, pixels.Color(0, 0, 0));
  pixels.setPixelColor(5, pixels.Color(0, 0, 0));
  pixels.setPixelColor(6, pixels.Color(0, 0, 0));
  pixels.setPixelColor(7, pixels.Color(0, 0, 0));
  pixels.show();
}

void All_On(){
  pixels.clear(); 
     pixels.setPixelColor(1, pixels.Color(255, 0, 0));
  pixels.setPixelColor(2, pixels.Color(0, 255, 0));
  pixels.setPixelColor(3, pixels.Color(0, 0, 255));
  pixels.setPixelColor(4, pixels.Color(255, 255, 0));
  pixels.setPixelColor(5, pixels.Color(255, 0, 255));
  pixels.setPixelColor(6, pixels.Color(0, 255, 255));
  pixels.setPixelColor(7, pixels.Color(255, 255, 255));
  pixels.setPixelColor(0, pixels.Color(255, 255, 255));
  pixels.show();
}

void police(){
  Kanan();
  for(int hz = 440; hz < 1000; hz+=2){
    tone(buzz, hz, 50);
    delay(5);
  }
  Kiri2();
  for(int hz = 1000; hz > 440; hz-=2){
    tone(buzz, hz, 50);
    delay(5);
  }
  Kanan();
}

void police2(){
  Kanan();
  tone(buzz, 440, 50);
  delay(200);
  Kiri2();
  tone(buzz, 500, 50);
  delay(200);
}
