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

  pinMode (pinPintu, INPUT);
  pinMode (buzzer, OUTPUT);
  pinMode (tPin, OUTPUT);
  pinMode (ePin, INPUT);

  Serial.begin(115200);  
  mlx.begin();
  lcd.begin();
  lcd.backlight();
  
  Serial.println("");         
  Serial.println("Memulai Koneksi...");
  lcd.setCursor(0,0);
  lcd.print("Menunggu Hotspot");

  myBot.wifiConnect(ssid, pass);
  myBot.setTelegramToken(token);
     
  Serial.println("");
  Serial.print("Terhubung dengan : ");
  Serial.println(ssid);
  Serial.print("\n");
  Serial.print("IP address : ");
  Serial.print(WiFi.localIP());
  lcd.clear();
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
  delay(1000);
//  lcd.setCursor(0,0);
//  lcd.print("Kirim \"/start\"");
//  lcd.setCursor(0,1);
//  lcd.print("Dari Telegram   ");
//  aktif = 0;
//  while(aktif == 0){
//    lcd.setCursor(0,1);
//    lcd.print("Dari Telegram   ");
//    delay(100);
//    lcd.setCursor(0,1);
//    lcd.print("Menunggu.");
//    delay(100);
//    lcd.setCursor(0,1);
//    lcd.print("Menunggu...     ");
//    delay(100);
//    if (myBot.getNewMessage(msg)) {                                                           
//      if (msg.text.equalsIgnoreCase("/start")) {                                         
//            myBot.sendMessage(msg.sender.id, "✅ Halo...\nSelamat Datang Di Temperatur Warning System");
//            aktif = 1;
//      } 
//    }
//  }
    if (myBot.getNewMessage(msg)) {                                                           
      if (msg.text.equalsIgnoreCase("/start")) {                                         
            myBot.sendMessage(msg.sender.id, "✅ Halo...\nSelamat Datang Di Temperatur Warning System");
            aktif = 1;
      } 
    }
}

void loop() {
  
  if(Serial.available()){
    datame = Serial.read();
  }
  if(aktif == 0){
    lcd.setCursor(0,0);
    lcd.print("Kirim \"/start\"");
    lcd.setCursor(0,1);
    lcd.print("Dari Telegram   ");

    if (myBot.getNewMessage(msg)) {                                                           
        if (msg.text.equalsIgnoreCase("/start")) {                                         
              myBot.sendMessage(msg.sender.id, "✅ Halo...\nSelamat Datang Di Temperatur Warning System");
              aktif = 1;
        } 
    }
  }
  if(aktif == 1){
  sensorJarak();  
  suhu = 0;
  if (jarak >= 17 && baca != 1){
    lcd.clear();
    lcd.setCursor(0,0); lcd.print("MENDEKAT +- 15cm");
    lcd.setCursor(0,1); lcd.print("JARAK = " + String(jarak) + "cm    ");
    delay(90); 
  }
  if(jarak < 17 && jarak > 15 && baca != 1 || datame == 'n'){
    lcd.clear();
    datame = '0';
    suhu = mlx.readObjectTempC() + kalibrasi;
    Serial.print("Suhu = "); Serial.print(suhu); Serial.println("°C");
    lcd.setCursor(0,0); lcd.print("Suhu Anda " + String(suhu));
    if (suhu > 29 && suhu < 37){
      digitalWrite(pinGreen, HIGH);
      lcd.setCursor(0,1); lcd.print("Suhu Anda Aman  ");
      myBot.sendMessage(msg.sender.id, "✅ Aman !!! \n Suhu " + String(suhu) + "°C");
      digitalWrite(buzzer, 1);
      delay(500);
      digitalWrite(buzzer, 0);
      delay(500); 
      Serial.println("Buka Pintu");
      pintu.write(180);
      delay(100);      
      int var;
      var = digitalRead(pinPintu);
      while(var  == 1){
        var = digitalRead(pinPintu);
        Serial.println("Pintu Terbuka");
        delay(50);
      }
      delay(2000);
      pintu.write(90);
      delay(2000);
      Serial.println("Tutup Pintu");        
      digitalWrite(pinGreen, LOW);
      baca = 0;
    }
    else if (suhu >= 37 && suhu <= 100){
      lcd.setCursor(0,1); lcd.print("Suhu Anda Bahaya");
      Serial.print("⛔️ Warning !!! \n Suhu " + String(suhu));Serial.println("°C");    
      myBot.sendMessage(msg.sender.id, "⛔️ Warning !!! \n Suhu " + String(suhu) + "°C");
      for(int i = 0; i < 5; i++){
        digitalWrite(buzzer, 1);
        delay(500);
        digitalWrite(buzzer, 0);
        delay(500);
      }
      delay(1000);
      baca = 0;
    }
  }
  }
//  else if (suhu > 100){
//    lcd.setCursor(0,1); lcd.print("Suhu Anda Bahaya");
//    //Serial.print("⛔️ Warning !!! \n Suhu " + String(suhu));
//    //Serial.println("°C");
//    digitalWrite(buzzer, 1);
//    delay(500);
//    digitalWrite(buzzer, 0);
//    baca = 0;
//  }
  // kirim pesan ke telegram
//  if (myBot.getNewMessage(msg) && aktif == 0) {                                                           
//    if (msg.text.equalsIgnoreCase("/start")) {                                         
//          //myBot.sendMessage(msg.sender.id, ");
//          myBot.sendMessage(msg.sender.id, "✅ Halo...\nSelamat Datang Di Temperatur Warning System");
//          //Serial.println("\n✅ User memulai Temperatur Warning Bot \n");
//          //TampilkanTombol = true;
//          aktif = 1;
//    } 
//  }
}
