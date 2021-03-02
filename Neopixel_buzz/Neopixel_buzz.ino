#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h>
#endif

#define PIN 6 // On Trinket or Gemma, suggest changing this to 1

#define NUMPIXELS 8 // Popular NeoPixel ring size

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#define DELAYVAL 500
int buzz = 12;

unsigned long waktus;
unsigned long waktul1 = 0;
unsigned long waktul2 = 0;
unsigned long waktul3 = 0;
unsigned long waktul4 = 0;

void setup() {
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  pixels.begin();
  pinMode(13,OUTPUT);
}

void loop() {
  waktus = millis();
  if(waktus - waktul1 > 50){
    waktul1 = waktus;
    police();
  }
//  if(waktus - waktul2 > 100){
//    waktul2 = waktus;
//    merah();
//  }
//  if(waktus - waktul3 > 100){
//    waktul3 = waktus;
//    biru();
//  }
//  if(waktus - waktul4 >= 50){
//    waktul4 = waktus;
//    
//  }
}
void merah(){
   pixels.clear(); 
   pixels.setPixelColor(0, pixels.Color(255,0, 0));
   pixels.setPixelColor(1, pixels.Color(255, 0, 0));
   pixels.setPixelColor(2, pixels.Color(255, 0, 0));
   pixels.setPixelColor(3, pixels.Color(255, 0, 0));
   pixels.show();
}

void biru(){
  pixels.clear();
  pixels.setPixelColor(4, pixels.Color(0, 0, 255));
  pixels.setPixelColor(5, pixels.Color(0, 0, 255));
  pixels.setPixelColor(6, pixels.Color(0, 0, 255));
  pixels.setPixelColor(7, pixels.Color(0, 0, 255));
  pixels.show();
}
void police() {                             //This function produces the 4th siren(POLICE) sound with led transition.
  biru();
  for(int hz = 440; hz < 1000; hz+=2){
    tone(buzz, hz, 50);
    delay(5);
  }
  merah();
  for(int hz = 1000; hz > 440; hz-=2){
    tone(buzz, hz, 50);
    delay(5);
  }
}
