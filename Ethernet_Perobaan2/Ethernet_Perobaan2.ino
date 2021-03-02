#include <SPI.h>
#include <Ethernet.h>
#include <MFRC522.h>
#include <EEPROM.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "SensorS.h"

int i = 0;
// --- Ethernet Shield BEGIN ------
  String readString;
  char c;
  byte mac[] = {0x47, 0x1F, 0xD0, 0x40, 0x26, 0x6D};

  IPAddress ip(192, 168, 0, 20);
  IPAddress myDns(8, 8, 8, 8);
  IPAddress gateway(192, 168, 0, 1);
  IPAddress subnet(255, 255, 255, 0);
  EthernetServer server(80);

// --- Ethernet Shield END ------

// --- Multi Tasking BEGIN ------
unsigned long waktuL1 = 0; // suhu
unsigned long waktuL2 = 0; // ethernet
unsigned long waktuL3 = 0; // rfid
unsigned long waktuL4 = 0; // pir
int interval = 1000;

// --- Multi Tasking END ------

// --- void setup() BEGIN ---
void setup() {
  Serial.begin(9600);
  while (!Serial) { ; }
  Ethernet.begin(mac, ip, myDns, gateway, subnet);
  server.begin();
  pinMode(ledPin, OUTPUT);     // jadikan LED sebagai Output
  pinMode(inputPin, INPUT);    // jadikan Sensor sebagai Input
  pinMode(Buzzer, OUTPUT); // jadikan buzzer sebagai output
  SPI.begin();
  rfid.PCD_Init();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
}
// --- void setup() END ---


// --- void loop() BEGIN ---
void loop() {
  unsigned long waktu = millis();
  if(waktu - waktuL1 > interval){
    waktuL1 =waktu;
    suhu();
    if(ReadSuhu < 50){
      SSuhu = true;
    } else{
      SSuhu = false;
    }
  }
  if(waktu - waktuL3 > interval){
    waktuL3 = waktu;
    rfid_card();
  }
  if(waktu - waktuL4 > interval){
    waktuL4 = waktu;
    pirmotion();
  }
  if(waktu - waktuL2 > interval){
  waktuL2 = waktu;
  EthernetClient client = server.available();
  if (client) {
    while (client.connected()) {   
      if (client.available()) {
        c = client.read(); 
        if (readString.length() < 100) {
          readString += c;
        }
  if (c == '\n') {
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println();     
  client.println("<HTML>");
  client.println("<HEAD>");
  client.println("<meta http-equiv=\"Refresh\" content=\"1; url=/Yuma\" />");
  client.println("<meta http-equiv=\"Content-Type\" content=\"application/vnd.wap.xhtml+xml; charset=utf-8\" />");
  client.println("<style type=\"text/css\">");
  client.println("body {");
  client.println("background-color:#00676B;");
  client.println("background: linear-gradient(top, #CAE5E8 0%, #00676B 100%);");
  client.println("background:-o-linear-gradient(top, #CAE5E8 #00676B);");
  client.println("background:-moz-linear-gradient(top, #CAE5E8, #00676B);");
  client.println("background:-webkit-gradient(linear, left top, left bottom, from(#CAE5E8), to(#00676B));");
  client.println("filter: progid:DXImageTransform.Microsoft.gradient( startColorstr ='#CAE5E8', endColorstr ='#00676B');");
  client.println("background: -ms-linear-gradient(top, #CAE5E8, #00676B);");
  client.println("background-attachment: fixed;");
  client.println("border: 0px; margin: 0px; padding: 0px; color: #000000;");
  client.println("font-family: Sans Serif, Arial Western, Verdana;");
  client.println("font-size: small; text-align: center; align: center; }");
  client.println("}");
  client.println("table {");
  client.println("border: 0px; width: 40%; align: center; text-align: center; padding: 0px;");
  client.println("vertical-align: middle; border-spacing: 0px;");
  client.println("box-shadow: 15px 15px 15px #666666;");
  client.println("-moz-box-shadow: 15px 15px 15px #666666;");
  client.println("-webkit-box-shadow: 15px 15px 15px #666666; }");
  client.println("tr { height: 40px; }");
  client.println("th { background-color: #C8E2B1; height: 50px; }");
  client.println(".trh1 { background-color: #CAE5E8; }");
  client.println(".trh1:hover { background-color: #E6F1D8; }");
  client.println(".trh2 { background-color: #99D1D3; }");
  client.println(".trh2:hover { background-color: #E6F1D8; }");
  client.println("h1 { margin: 25px; " );
  client.println("font-family: Arial Western, Verdana;");
  client.println("text-shadow: 5px 3px 3px #999999;");
  client.println("font-size: 20pt;font-weight: bold;");
  client.println("color: #000; border: 0px; }");
  client.println("h6 {");
  client.println("font-size: 10pt;");
  client.println("font-weight: normal;");
  client.println("text-shadow: 1px 1px 1px #999999;");
  client.println("color: #000; margin: 20px; }");
  client.println(".bogoc {");
  client.println("background-color: #ECECEC;");
  client.println("-moz-border-radius: 10px;");
  client.println("webkit-border-radius: 10px");
  client.println("border-radius: 10px;");
  client.println("box-shadow: 10px 10px 10px #666666;");
  client.println("-moz-box-shadow: 10px 10px 10px #666666;");
  client.println("-webkit-box-shadow: 10px 10px 10px #666666; }");
  client.println(".shadow {");
  client.println("border: 1px solid #00676B;");
  client.println("box-shadow: 10px 10px 10px #666666;");
  client.println("-moz-box-shadow: 10px 10px 10px #666666;");
  client.println("-webkit-box-shadow: 10px 10px 10px #666666; }");
  client.println("td {");
  client.println("color: #000; text-align: center; margin: 0px;");
  client.println("font-family: Arial Western, sans-serif;");
  client.println("font-weight: bold;");
  client.println("text-decoration: none;");
  client.println("-moz-border-radius: 5px;");
  client.println("-webkit-border-radius: 5px; }");
  client.println(".aktif {");
  client.println("background-color: red;");
  client.println("color: #FFFFFF;");
  client.println("padding: 4px 35px 4px 35px;");
  client.println("text-align: center;");
  client.println("margin: 0px;");
  client.println("font-family: Arial Western, sans-serif;");
  client.println("font-weight: bold;");
  client.println("text-decoration: none;");
  client.println("-moz-border-radius: 5px;");
  client.println("-webkit-border-radius: 5px;");
  client.println("-o-border-radius: 5px;");
  client.println("border-radius: 5px;");
  client.println("border-color:black;");
  client.println("border-top:2px solid;");
  client.println("border-bottom:2px solid;");
  client.println("border-right:2px solid;");
  client.println("border-left:2px solid; }");
  client.println(".aman { ");
  client.println("background-color: green;");
  client.println("color: #FFFFFF;");
  client.println("padding: 4px 35px 4px 35px;");
  client.println("text-align: center;");
  client.println("margin: 0px;");
  client.println("font-family: Arial Western, sans-serif;");
  client.println("font-weight: bold;");
  client.println("text-decoration: none;");
  client.println("-moz-border-radius: 5px;");
  client.println("-webkit-border-radius: 5px;");
  client.println("-o-border-radius: 5px;");
  client.println("border-radius: 5px;");
  client.println("border-color:black;");
  client.println("border-top:2px solid;");
  client.println("border-bottom:2px solid;");
  client.println("border-right:2px solid;");
  client.println("border-left:2px solid; }");
  client.println("</style>");
  client.println("<TITLE>SCURITY STATION MONITORING</TITLE>");
  client.println("</HEAD>");
  client.println("<BODY align=\"center\">");
  client.println("<br />"); 
  client.println("<br />");
  client.println("<hr />");
  client.println("<h1 align=\"center\">KEAMANAN GUDANG PT. TIISUK </h1>");
  client.println("<hr />"); 
  client.println("<br />"); 
  client.println("<br />"); 
  client.println("<table align=\"center\" width=\"40%\"><tr>");
  client.println("<th width=\"5%\">MONITORING</th>");
  client.println("<th width=\"10%\">STATUS</th>");
  client.println("<tr class=\"trh1\"><td align=\"left\">");
  client.println(" ");
  client.println(" ");
  client.println("SUHU");
  client.println("</td><td align=\"center\">");
  if (SSuhu == false) {
    client.println("<b class=\"aman\">Aman</b>");
  } else {
    client.println("<b class=\"aktif\">Berbahaya</b>");
    client.println("<audio src=\"https://drive.google.com/uc?export=download&id=11BWwoKBez5xAxk8oSLYetSjKXQw0YgMG\" autoplay type=\"audio/mpeg\"></audio>");
  }
  client.println("</td></tr>");
  client.println();
  client.println("<tr class=\"trh2\"><td align=\"left\">");
  client.println(" ");
  client.println(" ");
  client.println("PINTU");
  client.println("</td><td align=\"center\">");
  if (SPintu == false) {
    client.println("<b class=\"aman\">Tertutup</b>");
  } else {
    client.println("<b class=\"aktif\">Terbuka</b>");
  }
  client.println("</td></tr>");
  client.println();
  client.println("<tr class=\"trh1\"><td align=\"left\">");
  client.println(" ");
  client.println(" ");
  client.println("PERGERAKAN");
  client.println("</td><td align=\"center\">");
  if (SMotion == false) {
    client.println("<b class=\"aman\">Tidak Ada</b>");
  } else {
    client.println("<b class=\"aktif\">Ada</b>");
  }
  client.println("</td></tr>");
  client.println();
  client.println("</table></BODY>");  
  delay(1);
  client.stop();
  }
  }
  }
  }
  }
}
// --- void loop() END ---
