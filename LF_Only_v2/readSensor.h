int data;

int S0 = A6;
int S1 = A5;
int S2 = A4;
int S3 = A3;
int S4 = A2;
int S5 = A1;

int Mata0; 
int Mata1; 
int Mata2; 
int Mata3; 
int Mata4;
int Mata5;

boolean debugsensor = 0;

int threshold = 950;

unsigned char s[6];

void readsensor(){
  Mata0 = analogRead(S0);
  Mata1 = analogRead(S1);
  Mata2 = analogRead(S2);
  Mata3 = analogRead(S3);
  Mata4 = analogRead(S4);
  Mata5 = analogRead(S5);

//  if (data == 0b0000011)
//     {error = 100; MotorSpeed = 70;}
//  else if ( data == 0b0110000)
//    {error = 101; MotorSpeed = 70;}
//  else if ( data == 0b0100001)
//    {error = 102; MotorSpeed = 70;}  
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

  
 if (data == 0b0011111)
   {error = 5; MotorSpeed = 70;} 
 else if (data == 0b0001111)
   {error = 4; MotorSpeed = 70;}  
 else if (data == 0b0101111)
   {error = 3; MotorSpeed = 70;}
 else if (data == 0b0100111)
   {error = 2; MotorSpeed = 70;}
 else if (data == 0b0110111)
   {error = 1; MotorSpeed = 70;}
 else if (data == 0b0110011)
   {error = 0; MotorSpeed = 70;}
 else if (data == 0b0111011)
   {error = -1; MotorSpeed = 70;}
 else if (data == 0b0111001)
   {error = -2; MotorSpeed = 70;}
 else if (data == 0b0111101)
   {error = -3; MotorSpeed = 70;}
 else if (data == 0b0111100)
 {error = -4; MotorSpeed = 70;} 
 else if (data == 0b0111110)
 {error = -5; MotorSpeed = 70;}
  
  if(debugsensor == true){
  Serial.print("Sensor : ");
  Serial.println(data,BIN);  
  Serial.print("Sensor 1 : ");
  Serial.println(analogRead(A1));
  Serial.print("Sensor 2 : ");
  Serial.println(analogRead(A2));
  Serial.print("Sensor 3 : ");
  Serial.println(analogRead(A3));
  Serial.print("Sensor 4 : ");
  Serial.println(analogRead(A4));
  Serial.print("Sensor 5 : ");
  Serial.println(analogRead(A5));
  Serial.print("Sensor 6 : ");
  Serial.println(analogRead(A6));
  delay(500);
  }
}
