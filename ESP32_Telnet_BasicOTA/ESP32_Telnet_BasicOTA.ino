#include <WiFi.h>
#include <ESPmDNS.h>
//#include <WiFiUdp.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <TelnetSpy.h>
//#include <SoftwareSerial.h>

//SoftwareSerial datain(D18, D19);//RX,TX

const char* ssid = "ReNo7";
const char* password = "12345678zx";

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
  Serial.begin(115200);
  //datain.begin(115200);
  
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
  
  SERIAL.println("Ready");
  SERIAL.print("IP address: ");
  SERIAL.println(WiFi.localIP());
  
}
String dataserial;
void loop() {
  SerialAndTelnet.handle();
  ArduinoOTA.handle();
  
  if (Serial.available()) {
    dataserial = Serial.readString();
    SERIAL.println(dataserial);
  }//end serial telnet
}//end loop
