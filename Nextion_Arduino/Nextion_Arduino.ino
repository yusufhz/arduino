#include <SoftwareSerial.h>
SoftwareSerial next(10,11);//RX,TX

String message = "";
void setup() {
  Serial.begin(115200);
  next.begin(115200);
}

void loop() {
  if (!next.available()) {
    if (message.length() > 14) {
      Serial.println(message);
      if (message[4] == '2') {
        Serial.println("Titip ditekan");
        message = "";
      } else if( message [4] == '4'){
        Serial.println("Ambil ditekan");
        message ="";
      } else if (message[4] == '1') {
        Serial.println("Selesai");
        message = "";
      }
    }
  }
  if (next.available()) {
    message.concat(next.read());
  }
}
