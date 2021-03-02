int ledPin = 22;     // Memilih pin indikator LED
int inputPin = 23;   // Memilih input PIR Sensor
int pirState = LOW;  // Pada saat mulai, Matikan sensor
int val = 0;         // Variable pembaca status pin
int Buzzer = 24;     // Memilih pin buzzer, dengan pin PWM
void setup() {
  pinMode(ledPin, OUTPUT);     // jadikan LED sebagai Output
  pinMode(inputPin, INPUT);// jadikan Sensor sebagai Input
  pinMode(pinSpeaker, OUTPUT);
  // jadikan buzzer sebagai output
  Serial.begin(9600);
}
void loop(){
  val = digitalRead(inputPin);
  if (val == HIGH) {
    digitalWrite(ledPin, HIGH);
    playTone(300, 160);
    delay(150);
 
    if (pirState == LOW) {
      Serial.println("Terdeteksi suatu pergerakan!");
      pirState = HIGH;
    }
  } else {
      digitalWrite(ledPin, LOW);
      playTone(0, 0);
      delay(300);  
      if (pirState == HIGH){
      Serial.println("Motion ended!");
      pirState = LOW;
    }
  }
}
void playTone(long duration, int freq) {
    duration *= 1000;
    int period = (1.0 / freq) * 1000000;
    long elapsed_time = 0;
    while (elapsed_time < duration) {
        digitalWrite(pinSpeaker,HIGH);
        delayMicroseconds(period / 2);
        digitalWrite(pinSpeaker, LOW);
        delayMicroseconds(period / 2);
        elapsed_time += (period);
    }
}
