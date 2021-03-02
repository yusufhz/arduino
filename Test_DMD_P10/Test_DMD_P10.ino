#include <DS3231.h>

#include <SPI.h>        //SPI.h must be included as DMD is written by SPI (the IDE complains otherwise)
#include <DMD.h>        //
#include <TimerOne.h>   //

#include "SystemFont5x7.h"
#include "Arial_black_16.h"

DS3231  rtc(SDA, SCL);
//Fire up the DMD library as dmd
#define DISPLAYS_ACROSS 1
#define DISPLAYS_DOWN 1

DMD dmd(DISPLAYS_ACROSS, DISPLAYS_DOWN);

unsigned long start;
unsigned long timer;
bool ret;


void ScanDMD()
{ 
  dmd.scanDisplayBySPI();
}

void setup(void)
{
  Serial.begin (9600); //baud komunikasi pada 9600
  rtc.begin();
//  dmd.setBrightness(255);
//  dmd.selectFont(SystemFont5x7);
//  dmd.begin();
   //initialize TimerOne's interrupt/CPU usage used to scan and refresh the display
   Timer1.initialize( 5000 );           //period in microseconds to call ScanDMD. Anything longer than 5000 (5ms) and you can see flicker.
   Timer1.attachInterrupt( ScanDMD );   //attach the Timer1 interrupt to ScanDMD which goes to dmd.scanDisplayBySPI()
   //clear/init the DMD pixels held in RAM
   dmd.clearScreen( true );   //true is normal (all pixels off), false is negative (all pixels on)
   
}

void loop(void)
{
    // kata
   //dmd.clearScreen( true );
   
   box.selectFont(SystemFont5x7);
   box.drawMarquee("SMKN 1 GUNUNGPUTRI",18,(32*DISPLAYS_ACROSS)-1,1);
   start=millis();
   timer=start;
   ret=false;
   while(!ret){
     if ((timer+50) < millis()) {
       ret=dmd.stepMarquee(-1,0);
       timer=millis();
     }
   }  
 }//end loop

