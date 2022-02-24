#include <ESP8266WiFi.h>
#include "CTBot.h"
#include "koneksi.h"
#include "pin.h"
#include "Ultrasonic.h"
#include <Wire.h>
#include <Adafruit_MLX90614.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

Servo pintu;
LiquidCrystal_I2C lcd(0x27, 16, 2);
Adafruit_MLX90614 mlx = Adafruit_MLX90614();

CTBot myBot;
float suhu;
float kalibrasi = 3.7;
      
TBMessage msg; 
void setup() {

  pinMode (pinGreen, OUTPUT);
  pinMode (pinRed, OUTPUT);
  pinMode (buzzer, OUTPUT);
  pinMode (tPin, OUTPUT);
  pinMode (ePin, INPUT);

  Serial.begin(115200);  
  mlx.begin();
  lcd.begin();
  lcd.backlight();
  
  Serial.println("");         
  Serial.println("Memulai Koneksi...");

  myBot.wifiConnect(ssid, pass);
  myBot.setTelegramToken(token);
     
  Serial.println("");
  Serial.print("Terhubung dengan : ");
  Serial.println(ssid);
  Serial.print("\n");
  Serial.print("IP address : ");
  Serial.print(WiFi.localIP());
  lcd.setCursor(0,0);
  lcd.print("SSID : " + String(ssid));
  lcd.setCursor(0,1);
  lcd.print(WiFi.localIP());
  Serial.print("\n");
  
    if (myBot.testConnection()) {  
        Serial.println("\nKoneksi Ke Telegram BOT Berhasil!"); 
        Serial.println("\n✅ User memulai Temperatur Warning Bot \n");
        lcd.clear();
        lcd.setCursor(0,0); lcd.print(" Telegram Ready ");
        }
    else {
        Serial.println("\nTidak Terkoneksi Ke Telegram BOT"); 
        lcd.setCursor(0,0); lcd.print("  Telegram DC   ");
        }

  pintu.attach(pinServo);
  pintu.write(90);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("=> Temperatur <=");
  lcd.setCursor(0,1);
  lcd.print("    Warning     ");
  delay(2000);
  lcd.clear();
}

int baca = 0;
char datame = 0;
unsigned long waktus; 
unsigned long waktuL1 = 0;
unsigned long waktuL2 = 0;
unsigned long waktuL3 = 0;

void loop() {
  waktus = millis();
  datame = 0;
  suhu = 0;
  if (waktus - waktuL1 > 200){
    waktuL1 = waktus;
    sensorJarak();   
    if(Serial.available()>0){
      datame = Serial.read();
    }
    if(jarak < 16 && jarak > 14 && baca != 1 || datame == 'n'){
      lcd.clear();
      suhu = mlx.readObjectTempC() + kalibrasi;
      //Serial.print("Suhu = "); Serial.print(suhu); Serial.println("°C");
      myBot.sendMessage(msg.sender.id, "Suhu Anda " + String(suhu) + "°C"); 
      lcd.setCursor(0,0); lcd.print("Suhu Anda " + String(suhu));
      baca = 1;
    }
    else if (jarak >= 16 && baca != 1){
      lcd.clear();
      lcd.setCursor(0,0); lcd.print("MENDEKAT +- 15cm");
      lcd.setCursor(0,1); lcd.print("JARAK = " + String(jarak) + "cm");
      delay(90); 
    }
  }
  if (waktus - waktuL2 > 100){
    waktuL2 = waktus;
    if (suhu > 29 && suhu < 37){
      digitalWrite(pinGreen, HIGH);
      //Serial.println("Buka Pintu");
      lcd.setCursor(0,1); lcd.print("Suhu Anda Aman  ");
      myBot.sendMessage(msg.sender.id, "⛔️ Warning !!! \n Suhu " + String(suhu) + "°C"); 
      pintu.write(180);
      delay(2000);
      //Serial.println("Tutup Pintu");        
      pintu.write(90);
      delay(2000);
      digitalWrite(pinGreen, LOW);
      baca = 0;
    }
    if (suhu >= 37 && suhu <= 100){
      if (myBot.testConnection()) {  
          //Serial.println("\nKoneksi Ke Telegram BOT Berhasil!"); 
          myBot.sendMessage(msg.sender.id, "⛔️ Warning !!! \n Suhu " + String(suhu) + "°C"); 
      }
      else {
          //Serial.println("\nTidak Terkoneksi Ke Telegram BOT"); 
      }
      lcd.setCursor(0,1); lcd.print("Suhu Anda Bahaya");
      //Serial.print("⛔️ Warning !!! \n Suhu " + String(suhu));Serial.println("°C");    
      delay(1000);
      digitalWrite(buzzer, 1);
      digitalWrite(pinRed, 1);
      delay(2000);
      digitalWrite(buzzer, 0);
      digitalWrite(pinRed, 0);
      delay(2000);
      baca = 0;
    }
    if (suhu > 100){
      lcd.setCursor(0,1); lcd.print("Suhu Anda Bahaya");
      //Serial.print("⛔️ Warning !!! \n Suhu " + String(suhu));
      //Serial.println("°C");
      digitalWrite(buzzer, 1);
      delay(500);
      digitalWrite(buzzer, 0);
      baca = 0;
    }
  }
  if(waktus - waktuL3 > 100){
    waktuL3 = waktus;
  // kirim pesan ke telegram
    if (myBot.getNewMessage(msg)) {                                                           
      if (msg.text.equalsIgnoreCase("/start")) {                                         
            //myBot.sendMessage(msg.sender.id, ");
            myBot.sendMessage(msg.sender.id, "✅ Halo...\nSelamat Datang Di Temperatur Warning System");
            //Serial.println("\n✅ User memulai Temperatur Warning Bot \n");
            //TampilkanTombol = true;
      } 
    }
  }
}
