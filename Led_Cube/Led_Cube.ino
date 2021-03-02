void setup() {
}

void loop() {
  for(int i=0; i<=255;i++)
  {
    analogWrite(10,i);
    delay(100);
    i=i+5;
    analogWrite(11,i);
    delay(100);
  }
}
