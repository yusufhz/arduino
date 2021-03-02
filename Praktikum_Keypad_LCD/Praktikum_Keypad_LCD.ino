#include <Keypad.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
String datastring;
const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns

char hexaKeys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {A15, A14, A13, A12}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {A11, A10, A9, A8}; //connect to the column pinouts of the keypad
byte love[8] = {B00000, B01010, B11111, B11111, B11111, B01110, B00100, B00000};
//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

void setup(){
  Serial.begin(9600);
  lcd.begin();
  lcd.createChar(1, love);
  lcd.setCursor(3,0);
  lcd.print((char)1);
  lcd.print(" Universitas Negeri Jakarta               ");
  for (int i = 0 ; i < 24; i ++) {
      lcd.scrollDisplayLeft();
      delay(500);
  }
  lcd.clear();
  lcd.setCursor(0,1);
  lcd.print((char)1);
  lcd.print(" Robotic Club ");
  lcd.setCursor(15,1);
  lcd.print((char)1);
  delay(3000);
  lcd.clear();
}
  
void loop(){
  char customKey = customKeypad.getKey();
  lcd.setCursor(0,0);
  lcd.print("Masukan data :  ");
  if (customKey){
    Serial.println(customKey);
    datastring = datastring + customKey;
    Serial.println(datastring);
    if(customKey == 'C' || datastring.length() > 16){
      datastring = "Clear           ";
      Serial.println(datastring);
      lcd.setCursor(0,1);
      lcd.print(datastring);
      delay(1000);
      datastring = "";
      lcd.clear();
    }
   lcd.setCursor(0,1);
   lcd.print(datastring);
  }
}
