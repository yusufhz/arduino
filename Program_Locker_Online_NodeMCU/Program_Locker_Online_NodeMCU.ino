#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>
#include <ESP8266HTTPClient.h>

SoftwareSerial node(D7, D8); // RX | TX

//const char *ssid = "BUK";
//const char *pass = "adminbuk";

//const char *ssid = "zx000";
//const char *pass = "zxcvbnm000";

//const char *ssid = "zx0_plus";
//const char *pass = "zxuan000";

const char *ssid = "TP-Link_B7DA";
const char *pass = "90134968";

//const char *ssid = "skripsian";
//const char *pass = "yusufmhz99";


//const char *ssid = "Sony";
//const char *pass = "saufika00";

String kirim;
void wifi_setup() {
  Serial.print(" Menghubungkan ke : ");
  Serial.println(ssid); 
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("....");
  }
  Serial.print("\n");
  Serial.print("IP address : ");
  Serial.print(WiFi.localIP());
  Serial.print("\n");
  Serial.print("MAC : ");
  Serial.println(WiFi.macAddress());
  Serial.println("");
  Serial.print("Terhubung dengan : ");
  Serial.println(ssid);
  delay(100);  
}

void setup() {
  Serial.begin(115200);
  node.begin(115200);
  wifi_setup();
  getdata();
  delay(100);
  node.print("\n");
  Serial.print("\n");  
}
unsigned long waktus;
unsigned long waktu1 = 0;
unsigned long waktu2 = 0;
void loop() {
  waktus = millis();
  if(waktus - waktu1 >= 3000){
    waktu1 = waktus;
    getdata();
  }
  if(waktus - waktu2 >= 3000){
    waktu2 = waktus;
    Serial.print(kirim);
    node.print(kirim);
    node.print("\n");
    Serial.print("\n");
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
}
