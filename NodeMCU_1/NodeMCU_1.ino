/*********
  Rui Santos
  Complete project details at https://randomnerdtutorials.com  
*********/

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "SoftwareSerial.h"

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
SoftwareSerial Terima(12,13);

String dataIn = "";
String kata = "";
bool cetak = false;
void setup() {  
  Serial.begin(115200);
  Terima.begin(115200);
  
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(2000);
  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);
  // Display static text
  display.println("= Ready =");
  Serial.println("======== Ready ========");
  display.display(); 
}

void loop() {
  if(Terima.available()){
    dataIn = Terima.readString();
    
    //dataIn += inChar;
    dataIn.replace("\n","");
    kata = dataIn;
    Serial.print("dataIn     : ");Serial.println(dataIn);  
    Serial.println(kata);
    cetak = true;
  }
  if(cetak!=false){
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(0, 10);
    display.println(kata);
    display.display(); 
    cetak = false;
    dataIn = "";
  }
  delay(50);
}
