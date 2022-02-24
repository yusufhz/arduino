#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

#define out1 4
#define out2 5
#define BTN_START 6
#define BTN_STOP 7
#define BTN_UP 8
#define BTN_DOWN 9
#define BTN_CCW 10

void setup() {
  pinMode(BTN_START, INPUT_PULLUP);
  pinMode(BTN_STOP, INPUT_PULLUP);
  pinMode(BTN_UP, INPUT_PULLUP);
  pinMode(BTN_DOWN, INPUT_PULLUP);
  pinMode(BTN_CCW, INPUT_PULLUP);
  lcd.begin();
  Serial.begin(9600); 
}

void loop() {
  if(
  
}
