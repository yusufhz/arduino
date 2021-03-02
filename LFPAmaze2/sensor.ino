void readsensor()
{ 
   uint8_t distance = sonar.ping_cm();
   delay(10);                     // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
//    Serial.print("Ping: ");
//    Serial.print(sonar.ping_cm()); // Send ping, get distance in cm and print result (0 = outside set distance range)
//    Serial.println("cm");
//    delay(10);
  //pembacaan sensor
  Mata0 = analogRead(S0);
  Mata1 = analogRead(S1);
  Mata2 = analogRead(S2);
  Mata3 = analogRead(S3);
  Mata4 = analogRead(S4);
  Mata5 = analogRead(S5);

 //  converting to digital
  if(Mata0 < threshold)
  {s[0] = 1;}
  else
  {s[0] = 0;}
  if(Mata1 < threshold)
  {s[1] = 1;}
  else
  {s[1] = 0;}
  if(Mata2 < threshold)
  {s[2] = 1;}
  else
  {s[2] = 0;}
  if(Mata3 < threshold)
  {s[3] = 1;}
  else
  {s[3] = 0;}
  if(Mata4 < threshold)
  {s[4] = 1;}
  else
  {s[4] = 0;}
  if(Mata5 < threshold)
  {s[5] = 1;}
  else
  {s[5] = 0;}

//  change the sensor reading into aseria of binary number
  data=(s[0]*32)+(s[1]*16)+(s[2]*8)+(s[3]*4)+(s[4]*2)+(s[5]*1);

  if(digitalRead(sensorapi) == HIGH){if(distance){error = 0; mode = Fire;}}
 else if (distance){error = 0; mode = Hall; MotorSpeed = 70;}
 else if (data == 0b0011111){error = 0; mode = Left; MotorSpeed = 60;}
 else if (data == 0b0111110){error = 0; mode = Right; MotorSpeed = 60;}
 else if (data == 0b0100001){error = 0; mode = Cross; MotorSpeed = 70;} 
 else if (data == 0b0111111){error = 0; mode = Noline; MotorSpeed = 50;}   
 //else if (data == 0b0011111){error = 5; mode = Line; MotorSpeed = 60;} 
 else if (data == 0b0000111){error = 4; mode = Line; MotorSpeed = 62;}
 else if (data == 0b0001111){error = 4; mode = Line; MotorSpeed = 62;}  
 else if (data == 0b0101111){error = 3; mode = Line; MotorSpeed = 64;}
 else if (data == 0b0100111){error = 2; mode = Line; MotorSpeed = 66;}
 else if (data == 0b0110111){error = 1; mode = Line; MotorSpeed = 68;}
 else if (data == 0b0110011 || data == 0b0100011 || data == 0b0110001){error = 0; mode = Line; MotorSpeed = 100;}
 else if (data == 0b0111011){error = -1; mode = Line; MotorSpeed = 68;}
 else if (data == 0b0111001){error = -2; mode = Line; MotorSpeed = 66;}
 else if (data == 0b0111101){error = -3; mode = Line; MotorSpeed = 64;}
 else if (data == 0b0111000){error = -4; mode = Line; MotorSpeed = 62;}
 else if (data == 0b0111100){error = -4; mode = Line; MotorSpeed = 62;}
// else if (data == 0b0111110){error = -5; mode = Line; MotorSpeed = 60;}
  Serial.print("data = ");
  Serial.println(data,BIN);











// if ((s[0]==0)&&(s[1]==1)&&(s[2]==1)&&(s[3]==1)&&(s[4]==1)&&(s[5]==1)){error = 5; mode = Line; MotorSpeed = 54;}
// else if ((s[0]==0)&&(s[1]==0)&&(s[2]==1)&&(s[3]==1)&&(s[4]==1)&&(s[5]==1)){error = 4; mode = Line; MotorSpeed = 54;}
// else if ((s[0]==1)&&(s[1]==0)&&(s[2]==1)&&(s[3]==1)&&(s[4]==1)&&(s[5]==1)){error = 3; mode = Line; MotorSpeed = 54;}
// else if ((s[0]==1)&&(s[1]==0)&&(s[2]==0)&&(s[3]==1)&&(s[4]==1)&&(s[5]==1)){error = 2; mode = Line; MotorSpeed = 56;}
// else if ((s[0]==1)&&(s[1]==1)&&(s[2]==0)&&(s[3]==1)&&(s[4]==1)&&(s[5]==1)){error = 1; mode = Line; MotorSpeed = 58;}
// else if ((s[0]==1)&&(s[1]==1)&&(s[2]==0)&&(s[3]==0)&&(s[4]==1)&&(s[5]==1)){error = 0; mode = Line; MotorSpeed = 60;}
// else if ((s[0]==1)&&(s[1]==1)&&(s[2]==1)&&(s[3]==0)&&(s[4]==1)&&(s[5]==1)){error = -1; mode = Line; MotorSpeed = 58;}
// else if ((s[0]==1)&&(s[1]==1)&&(s[2]==1)&&(s[3]==0)&&(s[4]==0)&&(s[5]==1)){error = -2; mode = Line; MotorSpeed = 56;}
// else if ((s[0]==1)&&(s[1]==1)&&(s[2]==1)&&(s[3]==1)&&(s[4]==0)&&(s[5]==1)){error = -3; mode = Line; MotorSpeed = 54;}
// else if ((s[0]==1)&&(s[1]==1)&&(s[2]==1)&&(s[3]==1)&&(s[4]==0)&&(s[5]==0)){error = -4; mode = Line; MotorSpeed = 54;}
// else if ((s[0]==1)&&(s[1]==1)&&(s[2]==1)&&(s[3]==1)&&(s[4]==1)&&(s[5]==1)){error = -5; mode = Line; MotorSpeed = 54;}
// else if ((s[0]==0)&&(s[1]==0)&&(s[2]==0)&&(s[3]==0)&&(s[4]==1)&&(s[5]==1)){error = 0; mode = Left; MotorSpeed = 50;}
// else if ((s[0]==1)&&(s[1]==1)&&(s[2]==1)&&(s[3]==1)&&(s[4]==1)&&(s[5]==1)){error = 0; mode = Back; MotorSpeed = 50;}
// else if ((s[0]==1)&&(s[1]==1)&&(s[2]==0)&&(s[3]==0)&&(s[4]==1)&&(s[5]==0)){error = 0; mode = Right; MotorSpeed = 50;}
// else if ((s[0]==0)&&(s[1]==0)&&(s[2]==0)&&(s[3]==0)&&(s[4]==0)&&(s[5]==0)){error = 0; mode = Cross; MotorSpeed = 60;}
    Serial.print(Mata0);
//  Serial.print(s[0]);
    Serial.print("\t");
    Serial.print(Mata1);
//  Serial.print(s[1]);
    Serial.print("\t");
    Serial.print(Mata2);
//  Serial.print(s[2]);
    Serial.print("\t");
    Serial.print(Mata3);
//  Serial.print(s[3]);
    Serial.print("\t");
    Serial.print(Mata4);
//  Serial.print(s[4]);
    Serial.print("\t");
    Serial.print(Mata5);
//  Serial.print(s[5]);
    Serial.println("\t");
  Serial.println(error);
//////    delay(100);
}

