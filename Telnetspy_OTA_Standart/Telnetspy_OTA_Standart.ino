#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <TelnetSpy.h>

#include <ArduinoJson.h>
#include <SoftwareSerial.h>
#include <ESP8266HTTPClient.h>

SoftwareSerial node(D7, D8); // RX | TX

const char* ssid = "zx0_plus";
const char* password = "zxuan000";

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

void waitForDisconnection() {
  while (WiFi.status() == WL_CONNECTED) {
    delay(500);
    SERIAL.print(".");
  }
  SERIAL.println(" Disconnected!");
}

void setup() {
  SerialAndTelnet.setWelcomeMsg("Selamat Datang di Majalengka\n\n");
  SERIAL.begin(115200);
  delay(100); // Wait for serial port
  SERIAL.setDebugOutput(false);
  SERIAL.print("\n\nConnecting to WiFi ");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  waitForConnection();

  // Hostname defaults to esp8266-[ChipID]
  ArduinoOTA.setHostname("Yusuf_Maulana");

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

  // tunda program anjen didieu...
}
