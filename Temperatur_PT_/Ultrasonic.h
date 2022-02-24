void sensorJarak() {
  digitalWrite (tPin, LOW);
  delayMicroseconds(2);

  digitalWrite(tPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(tPin,LOW);

  duration = pulseIn(ePin,HIGH);
  jarak = duration*0.034/2;
  Serial.print("Distance : "); Serial.print(jarak); Serial.println("cm");
}
