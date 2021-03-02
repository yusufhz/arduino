/*
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp32-esp8266-mysql-database-php/
  
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.
  
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

*/

#ifdef ESP32
  #include <WiFi.h>
  #include <HTTPClient.h>
#else
  #include <ESP8266WiFi.h>
  #include <ESP8266HTTPClient.h>
  #include <WiFiClient.h>
#endif

#include <Wire.h>
//#include <Adafruit_Sensor.h>
//#include <Adafruit_BME280.h>

// Replace with your network credentials
const char* xssid[]     = {"zx0_plus","ReNo7","TP-Link_B7DA"};
const char* xpass[] = {"zxuan000","12345678zx","robotic123"};

const char* ssid     = "TP-Link_B7DA";
const char* password = "robotic123";
// REPLACE with your Domain name and URL path or IP address with path
const char* serverName = "http://192.168.137.1/rumah/post-esp-data.php";

// Keep this API Key value to be compatible with the PHP code provided in the project page. 
// If you change the apiKeyValue value, the PHP file /post-esp-data.php also needs to have the same key 
String apiKeyValue = "tPmAT5Ab3j7F9";

String sensorName = "BME280";
String sensorLocation = "Office";

/*#include <SPI.h>
#define BME_SCK 18
#define BME_MISO 19
#define BME_MOSI 23
#define BME_CS 5*/

#define SEALEVELPRESSURE_HPA (1013.25)

//Adafruit_BME280 bme;  // I2C
//Adafruit_BME280 bme(BME_CS);  // hardware SPI
//Adafruit_BME280 bme(BME_CS, BME_MOSI, BME_MISO, BME_SCK);  // software SPI
int temp = 30;
int humi = 20;
int prea = 10;
bool wificon = false;
String wifiid;

void setup() {
  Serial.begin(115200);
//  for(int i = 3; i > 0; i--){
//    WiFi.begin(ssid[i], password[i]);
//    for(int j = 0; j < 9 ; j++){
//      delay(100);
//      Serial.print(".");
//    }
//    Serial.println();
//    if(WiFi.status() == WL_CONNECTED){
//      Serial.println("Terhubung : " + String(ssid[i]));
//      goto next;
//    }else{
//      Serial.println("Tidak Terhubung : " + String(ssid[i]));
//    }
//  }
//  
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) { 
    delay(500);
    Serial.print(".");
  }
//  Serial.println("");
//  Serial.print("Connected to WiFi network with IP Address: ");
//  Serial.println(WiFi.localIP());
//  next:
  Serial.println("");
  Serial.print("Terhubung dengan : ");
  Serial.println(ssid);
  Serial.print("\n");
  Serial.print("IP address : ");
  Serial.print(WiFi.localIP());
  Serial.print("\n");
  Serial.print("MAC : ");
  Serial.println(WiFi.macAddress());
  Serial.println("");
  delay(100); 

  // (you can also pass in a Wire library object like &Wire2)
//  bool status = bme.begin(0x76);
//  if (!status) {
//    Serial.println("Could not find a valid BME280 sensor, check wiring or change I2C address!");
//    while (1);
//  }
}

void loop() {
  int angka = millis();
  temp = (angka % 50) + 26;
  humi = (angka % 25) + 10;
  prea = (angka % 10) + 5;
  
  //Check WiFi connection status
  Serial.println("");
  Serial.print("Terhubung dengan : ");
  Serial.println(ssid);
  Serial.print("\n");
  Serial.print("IP address : ");
  Serial.println(WiFi.localIP());
  if(WiFi.status()== WL_CONNECTED){
    HTTPClient http;
    
    // Your Domain name with URL path or IP address with path
    http.begin(serverName);
    
    // Specify content-type header
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    
    // Prepare your HTTP POST request data
    String httpRequestData = "api_key=" + apiKeyValue + "&sensor=" + sensorName
                          + "&location=" + sensorLocation + "&value1=" + String(temp)
                          + "&value2=" + String(humi) + "&value3=" + String(prea) + "";
    Serial.print("httpRequestData: ");
    Serial.println(httpRequestData);
    
    // You can comment the httpRequestData variable above
    // then, use the httpRequestData variable below (for testing purposes without the BME280 sensor)
    //String httpRequestData = "api_key=tPmAT5Ab3j7F9&sensor=BME280&location=Office&value1=24.75&value2=49.54&value3=1005.14";

    // Send HTTP POST request
    int httpResponseCode = http.POST(httpRequestData);
     
    // If you need an HTTP request with a content type: text/plain
    //http.addHeader("Content-Type", "text/plain");
    //int httpResponseCode = http.POST("Hello, World!");
    
    // If you need an HTTP request with a content type: application/json, use the following:
    //http.addHeader("Content-Type", "application/json");
    //int httpResponseCode = http.POST("{\"value1\":\"19\",\"value2\":\"67\",\"value3\":\"78\"}");
        
    if (httpResponseCode>0) {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
    }
    else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
    }
    // Free resources
    http.end();
  }
  else {
    Serial.println("WiFi Disconnected");
  }
  //Send an HTTP POST request every 30 seconds
  delay(30000);  
}
