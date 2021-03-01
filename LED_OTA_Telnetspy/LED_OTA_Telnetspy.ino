#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <TelnetSpy.h>

const char* ssid = "TKJ_000";
const char* password = "yesbm3ok";

TelnetSpy SerialAndTelnet;

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

void telnetConnected() {
  SERIAL.println("Telnet connection established.");
}

void telnetDisconnected() {
  SERIAL.println("Telnet connection closed.");
}

void setup() {
  SerialAndTelnet.setWelcomeMsg("Welcome to the TelnetSpy example\n\n");
  SerialAndTelnet.setCallbackOnConnect(telnetConnected);
  SerialAndTelnet.setCallbackOnDisconnect(telnetDisconnected);
  SERIAL.begin(115200);
  delay(100); // Wait for serial port
  SERIAL.setDebugOutput(false);
  SERIAL.print("\n\nConnecting to WiFi ");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  waitForConnection();
    
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
  
  pinMode(D0, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  
  
  SERIAL.println("Ready");
  SERIAL.print("IP address: ");
  SERIAL.println(WiFi.localIP());
  SERIAL.println("Ready for Work Akmal");
}

void loop() {
  SerialAndTelnet.handle();
  ArduinoOTA.handle();
//begin
  if (SERIAL.available() > 0) {
    char c = SERIAL.read();
    switch (c) {
      case '\r':
        SERIAL.println();
        break;
      case 'C':
        digitalWrite(D0, 1);
        digitalWrite(D1, 1);
        digitalWrite(D2, 1);
        digitalWrite(D3, 1);
        
        SERIAL.println("Lampu Nyala..");
        break;
      case 'D':
        digitalWrite(D0, 0);
        digitalWrite(D1, 0);
        digitalWrite(D2, 0);
        digitalWrite(D3, 0);
        SERIAL.println("Lampu Mati..");        
        break;
      default:
        SERIAL.print(c);
        break;
    }
  }
  //end
}
