#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <TelnetSpy.h>

#include <ArduinoJson.h>
#include <SoftwareSerial.h>
#include <ESP8266HTTPClient.h>

SoftwareSerial node(D7, D8); // RX | TX

//const char* ssid = "zx0_plus";
//const char* password = "zxuan000";

const char *ssid = "TP-Link_B7DA";
const char *password = "90134968";

//const char *ssid = "BUK";
//const char *password = "adminbuk";

TelnetSpy SerialAndTelnet;

String kirim;

//#define SERIAL  Serial
#define SERIAL  SerialAndTelnet

void waitForConnection() {
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    SERIAL.print(".");
  }
  SERIAL.println(" Connected!");
}

void setup() {
  SerialAndTelnet.setWelcomeMsg("Welcome to the TelnetSpy example\n\n");
  SERIAL.begin(115200);
  delay(100); // Wait for serial port
  SERIAL.setDebugOutput(false);
  SERIAL.print("\n\nConnecting to WiFi ");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  waitForConnection();

  // Hostname defaults to esp8266-[ChipID]
  ArduinoOTA.setHostname("Skripsi_Yusuf_Maulana");

  // No authentication by default
  // ArduinoOTA.setPassword("admin");
  // During updates "over the air" the telnet session will be closed.
  // So the operations of ArduinoOTA cannot be seen via telnet.
  // So we only use the standard "Serial" for logging.
  ArduinoOTA.onStart([]() {
    Serial.println("Start");
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
    else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
    else if (error == OTA_END_ERROR) Serial.println("End Failed");
  });
  ArduinoOTA.begin();
  
  SERIAL.println("Ready");
  SERIAL.print("IP address: ");
  SERIAL.println(WiFi.localIP());
  SERIAL.print("Terhubung dengan : ");
  SERIAL.println(ssid);
  
  getdata();
  delay(100);
  node.print("\n");
  SERIAL.print("\n");    
  delay(100);    
}

unsigned long waktus;
unsigned long waktu1 = 0;
unsigned long waktu2 = 0;

void loop() {
  SerialAndTelnet.handle();
  ArduinoOTA.handle();

  waktus = millis();
  if(waktus - waktu1 >= 3000){
    waktu1 = waktus;
    getdata();
  }
  if(waktus - waktu2 >= 3000){
    waktu2 = waktus;
    SERIAL.print(kirim);
    node.print(kirim);
    node.print("\n");
    SERIAL.print("\n");
  } 
}

void getdata() {
  String httpGet = "http://locker-online.dx.am/resi/saldo/laci/stats.php";
  HTTPClient http;
  http.begin(httpGet);
  http.addHeader("Cache-Control", "no-cache");
  int httpCode = http.GET();
  String payload = http.getString();
  http.end();
  const size_t capacity = JSON_ARRAY_SIZE(1) + JSON_ARRAY_SIZE(3) + 3*JSON_OBJECT_SIZE(3) + 452;
  DynamicJsonBuffer jsonBuffer(capacity);
  JsonArray& root = jsonBuffer.parseArray(payload);
  JsonArray& root_0 = root[0];
  
  JsonObject& root_0_0 = root_0[0];
  const char* rfid1 = root_0_0["rfid"];
  
  JsonObject& root_0_1 = root_0[1];
  const char* rfid2 = root_0_1["rfid"];
  
  JsonObject& root_0_2 = root_0[2]; 
  const char* rfid3 = root_0_2["rfid"];
  
  kirim = "*" + String(rfid1) + "," + String(rfid2) + "," + String(rfid3) + "#";
//  Serial.print(kirim);
//  node.print(kirim);
}
