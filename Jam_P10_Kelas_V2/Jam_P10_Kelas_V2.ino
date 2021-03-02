//#include <DS3231.h>
#include "RTClib.h"
#include <SPI.h>        //SPI.h must be included as DMD is written by SPI (the IDE complains otherwise)
#include <DMD.h>        //
#include <TimerOne.h>   //
#include "SystemFont5x7.h"
#include "Arial_black_16.h"
#include "BauhausMdBT14.h"

RTC_DS3231 rtc;
//DS3231  rtc(SDA, SCL);
//Fire up the DMD library as dmd
#define DISPLAYS_ACROSS 1
#define DISPLAYS_DOWN 1
DMD dmd(DISPLAYS_ACROSS, DISPLAYS_DOWN);

char daysOfTheWeek[7][12] = {"MINGGU", "SENIN", "SELASA", "RABU", "KAMIS", "JUM'AT", "SABTU"};

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
   //rtc.setDOW(WEDNESDAY);     // Set Day-of-Week to SUNDAY
   //rtc.setTime(14, 16, 0);     // Set the time to 12:00:00 (24hr format)
   //rtc.setDate(2, 3, 2021);   // Set the date to January 1st, 2014   
   //rtc.adjust(DateTime(2021, 2, 3, 15, 37, 0));
}

void loop(void) {
  DateTime now = rtc.now();
//  Serial.println(rtc.getTimeStr()); 
//  Serial.print(rtc.getDOWStr());

  //jam
  dmd.clearScreen( true );
  String mnt = String(now.minute());
  Serial.println(mnt);
  String jam = String(now.hour()) + String(":") + String(now.minute());
  String x=jam; // Display TEXT SF
  x=x.substring(0,6);
  char a[6];
  x.toCharArray(a,6);
  dmd.selectFont(BauhausMdBT14);
  //dmd.selectFont(SystemFont5x7); // Font used
  dmd.drawString(0, 2, a,6, GRAPHICS_NORMAL); // Display TEXT SFE
  delay(10000);
  dmd.clearScreen( true );

//  String jam2 = String(now.second());
//  String x2=jam2; // Display TEXT SF
//  x2=x2.substring(0,6);
//  char a2[6];
//  x2.toCharArray(a2,6);
//  //dmd.selectFont(BauhausMdBT14);
//  dmd.selectFont(SystemFont5x7); // Font used
//  dmd.drawString(0, 8, a2,6, GRAPHICS_NORMAL); // Display TEXT SFE
//  delay(1000);
//  dmd.clearScreen( true );
  

  //Hari
  dmd.clearScreen( true );
  x=String(daysOfTheWeek[now.dayOfTheWeek()]); // Display TEXT SF
  char b[11]="";
  dmd.selectFont(Arial_Black_16);
  x.toCharArray(b,11);
  dmd.drawMarquee(b,11,(32*DISPLAYS_ACROSS)-1,1);
   long start=millis();
   long timer=start;
   boolean ret=false;
   while(!ret){
     if ((timer+80) < millis()) {
       ret=dmd.stepMarquee(-1,0);
       timer=millis();
     }
   }

   //tgl
  dmd.clearScreen( true );
  String datet = String(now.day()) + String("/") + String(now.month()) + String("/") + String(now.year()); 
  x=datet; // Display TEXT SF
  char c[11]="";
  dmd.selectFont(Arial_Black_16);
  x.toCharArray(c,11);
  dmd.drawMarquee(c,11,(32*DISPLAYS_ACROSS)-1,1);
   start=millis();
   timer=start;
   ret=false;
   while(!ret){
     if ((timer+80) < millis()) {
       ret=dmd.stepMarquee(-1,0);
       timer=millis();
     }
   }

} //end loop

