void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode (2, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int i = digitalRead(2);
  delay(200);
  if(i!=0){
    Serial.println("Tidak Ada Objek");
  }
  else {
    Serial.println("Ada Objek");
  }
}
