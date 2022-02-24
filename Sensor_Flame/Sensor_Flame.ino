int pinSensor = A0;
int pinLED = 13;
int nilaiSensor = 0;
void setup() {
  Serial.begin(9600);
  pinMode(pinLED, OUTPUT);
}

void loop() {
  nilaiSensor = analogRead(pinSensor);
  Serial.print("Nilai = ");
  Serial.println(nilaiSensor);
  if (nilaiSensor > 100){
    digitalWrite(pinLED, HIGH);
  } 
  else {
    digitalWrite(pinLED, LOW);
  }
  delay(200);
}
