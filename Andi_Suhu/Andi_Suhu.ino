#include <Wire.h>
#include <Adafruit_MLX90614.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <ESP8266TelegramBOT.h>

Adafruit_MLX90614 mlx = Adafruit_MLX90614();

// Initialize Wifi connection to the router
char ssid[] = "RMX20"; // your network SSID (name)
char pass[] = "zx12345678"; // your network key

// Initialize Telegram BOT
#define BOTtoken "1837263761:AAFstp7xdFQn7dRRiPccffzkaU5H4ycP0"  //token of TestBOT
#define BOTname "SuhuV1"
#define BOTusername "SuhuV1_bot"
TelegramBOT bot(BOTtoken, BOTname, BOTusername);

int Bot_mtbs = 1000; //mean time between scan messages
long Bot_lasttime;   //last time messages' scan has been done

/********************************************
 * EchoMessages - function to Echo messages *
 ********************************************/
void Bot_EchoMessages() {

  for (int i = 1; i < bot.message[0][0].toInt() + 1; i++)      {
    bot.sendMessage(bot.message[i][4], bot.message[i][5], "");
  }
  bot.message[0][0] = "";   // All messages have been replied - reset new messages
}

void setup() {

  Serial.begin(115200);
  delay(3000);
  
  // attempt to connect to Wifi network:
  Serial.print("Connecting Wifi: ");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  IPAddress ip = WiFi.localIP();
  Serial.println(ip);

  bot.begin();      // launch Bot functionalities

  Serial.println("Adafruit MLX90614 test");  

  mlx.begin();  
}

void loop() {
  Serial.print("Ambient = "); Serial.print(mlx.readAmbientTempC()); 
  Serial.print("*C\tObject = "); Serial.print(mlx.readObjectTempC()); Serial.println("*C");
  Serial.print("Ambient = "); Serial.print(mlx.readAmbientTempF()); 
  Serial.print("*F\tObject = "); Serial.print(mlx.readObjectTempF()); Serial.println("*F");

  Serial.println();
  delay(500);

  if (millis() > Bot_lasttime + Bot_mtbs)  {
    bot.getUpdates(bot.message[0][1]);   // launch API GetUpdates up to xxx message
    Bot_EchoMessages();   // reply to message with Echo
    Bot_lasttime = millis();
  }
}
