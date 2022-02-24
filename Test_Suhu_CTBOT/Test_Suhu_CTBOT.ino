#include <ESP8266WiFi.h>
#include "CTBot.h"
CTBot myBot;
//CTBotReplyKeyboard Tbl;
//CTBotInlineKeyboard TbLp1on, TbLp2on, TbLp3on, TbLp4on, TbLp1off, TbLp2off, TbLp3off, TbLp4off, TbLpAllon, TbLpAlloff;

bool TampilkanTombol;
              
String ssid = "red7";
String pass = "zx12345678";
String token = "1728652547:AAFxpeQY2u5d-QsMKNTbWN0JWYs4xk56rS4";

// SuhuC_bot  1892026010:AAHYEzein9NYCbz06aV5tyIxuaa07W2uG7o
// SuhuV1_bot 1837263761:AAGw5TH-XChg4mTPGHuZJqk6V4BUi3pTad4

void setup() {
  
Serial.begin(115200);  
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
  Serial.print("\n");
  
    if (myBot.testConnection())   
        Serial.println("\nKoneksi Ke Telegram BOT Berhasil!"); 
    else 
        Serial.println("\nTidak Terkoneksi Ke Telegram BOT"); 
}

void loop() {
  TBMessage msg;
  myBot.sendMessage(msg.sender.id, "Halo...\nSelamat Datang Di SuhuC_Bot");
  if (myBot.getNewMessage(msg)) {                                                           
    if (msg.text.equalsIgnoreCase("/start")) {                                         
          //myBot.sendMessage(msg.sender.id, ");
          myBot.sendMessage(msg.sender.id, "Halo...\nSelamat Datang Di SuhuC_Bot");
          Serial.println("\nUser memulai Bot \n");
          TampilkanTombol = true;
    } else if (msg.text.equalsIgnoreCase("/help")) {
          myBot.sendMessage(msg.sender.id, "/start : Untuk Memulai Bot");
          myBot.sendMessage(msg.sender.id, "/help : Untuk melihat perintah yang ada di Bot");
          myBot.sendMessage(msg.sender.id, "Ini di buat oleh Yusuf Maulana MHZZZ");
          Serial.println("\nUser mengirim perintah Help \n");
    } else {   
          myBot.sendMessage(msg.sender.id, "Perintah tidak dikenal?!\n\nGunakan tombol peintah /help");
          Serial.println("\nUser mengirim perintah yang tidak dikenal\n");
    }
  }
  delay(100);
}
