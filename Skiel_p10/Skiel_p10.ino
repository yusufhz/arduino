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



void ScanDMD()
{ 
  dmd.scanDisplayBySPI();
}

void setup(void)
{
  Serial.begin (9600); //baud komunikasi pada 9600
   rtc.begin();
   //initialize TimerOne's interrupt/CPU usage used to scan and refresh the display
   Timer1.initialize( 5000 );           //period in microseconds to call ScanDMD. Anything longer than 5000 (5ms) and you can see flicker.
   Timer1.attachInterrupt( ScanDMD );   //attach the Timer1 interrupt to ScanDMD which goes to dmd.scanDisplayBySPI()
   //clear/init the DMD pixels held in RAM
   dmd.clearScreen( true );   //true is normal (all pixels off), false is negative (all pixels on)
   rtc.setDOW(WEDNESDAY);     // Set Day-of-Week to SUNDAY
   rtc.setTime(13, 45, 0);     // Set the time to 12:00:00 (24hr format)
   rtc.setDate(2, 3, 2021);   // Set the date to January 1st, 2014   

}

void loop(void)
{

 
  Serial.println(rtc.getTimeStr()); 
  Serial.print(rtc.getDOWStr());
  
  //jam
  dmd.clearScreen( true );

  String y=rtc.getDOWStr(); // Display TEXT SF
  y=y.substring(0,9);
  char c[9];
  y.toCharArray(c,9);
  //dmd.selectFont(Arial_Black_16);
  dmd.selectFont(SystemFont5x7); // Font used
  //const char *MSG = y;
  dmd.drawString(3, 0, c,9, GRAPHICS_NORMAL); // Display TEXT SFE
//  dmd.drawString(2, 8, y, 10, GRAPHICS_NORMAL); // Display TEXT SFE
  
  String x=rtc.getTimeStr(); // Display TEXT SF
  x=x.substring(0,6);
  char a[6];
  x.toCharArray(a,6);
  dmd.selectFont(SystemFont5x7); // Font used
  dmd.drawString(2, 8, a,6, GRAPHICS_NORMAL); // Display TEXT SFE
  delay(3000);
  dmd.clearScreen( true );

  
  
//  //tgl
//  dmd.clearScreen( true );
//  x=rtc.getDateStr(); // Display TEXT SF
//  char c[11];
//  dmd.selectFont(Arial_Black_16);
//  x.toCharArray(c,11);
//  dmd.drawMarquee(c,11,(32*DISPLAYS_ACROSS)-1,1);
//   long start=millis();
//   long timer=start;
//   boolean ret=false;
//   while(!ret){
//     if ((timer+80) < millis()) {
//       ret=dmd.stepMarquee(-1,0);
//       timer=millis();
//     }
//   }
//
//
//    // kata
//   dmd.clearScreen( true );
//   dmd.selectFont(Arial_Black_16);
//   dmd.drawMarquee("SMKN 1 GUNUNGPUTRI",18,(30*DISPLAYS_ACROSS)-1,1);
//   start=millis();
//   timer=start;
//   ret=false;
//   while(!ret){
//     if ((timer+50) < millis()) {
//       ret=dmd.stepMarquee(-1,0);
//       timer=millis();
//     }
//   }
//
//   // kata
//   dmd.clearScreen( true );
//   dmd.selectFont(Arial_Black_16);
//   dmd.drawMarquee("TEKNIK ELEKTRONIKA INDUSTRI",27,(32*DISPLAYS_ACROSS)-1,1);
//   start=millis();
//   timer=start;
//   ret=false;
//   while(!ret){
//     if ((timer+50) < millis()) {
//       ret=dmd.stepMarquee(-1,0);
//       timer=millis();
//     }
//   }
//
//    dmd.clearScreen( true );
//   dmd.selectFont(Arial_Black_16);
//   const char *MSG = "* ELIND *";
//   dmd.drawString(9, 1, MSG,9, GRAPHICS_NORMAL); // Display TEXT SFE
//  delay(1000);
//  dmd.clearScreen( true );
//
//
//   // kata
//   dmd.clearScreen( true );
//   dmd.selectFont(Arial_Black_16);
//   dmd.drawMarquee("TETAP PATUHI PROTOKOL KESEHATAN",31,(32*DISPLAYS_ACROSS)-1,1);
//   start=millis();
//   timer=start;
//   ret=false;
//   while(!ret){
//     if ((timer+50) < millis()) {
//       ret=dmd.stepMarquee(-1,0);
//       timer=millis();
//     }
//   }
//
//   // kata
//   dmd.clearScreen( true );
//   dmd.selectFont(Arial_Black_16);
//   dmd.drawMarquee("MENCUCI TANGAN, MEMAKAI MASKER DAN JAGA JARAK",45,(32*DISPLAYS_ACROSS)-1,1);
//   start=millis();
//   timer=start;
//   ret=false;
//   while(!ret){
//     if ((timer+50) < millis()) {
//       ret=dmd.stepMarquee(-1,0);
//       timer=millis();
//     }
//   }

  
 
 }

