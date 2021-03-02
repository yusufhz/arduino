void Sultra(){
// ------ SENSOR ULTRASONIC --------//
  digitalWrite (triggerPin, LOW);
  delayMicroseconds(2);

  digitalWrite(triggerPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin,LOW);

  duration = pulseIn(echoPin,HIGH);
  distance = duration*0.034/2;
  if(distance >= 3){
    distance = distance +1; 
  }
  else if(distance==4){
    distance=4;
  }
  else if(distance < 3){
    distance = duration*0.034/2;
  }
  
  Serial.print("Distance : ");
  Serial.print(distance);
  Serial.println("cm");
  //-------- END SENSOR ULTRASONIC ------//
}
