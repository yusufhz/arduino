#define Colour_Sensor A10
//========================
#define Relay_Ex 28
//========================
#define Vlame_Kanan A11
#define Vlame_SKanan A12
#define Vlame_Depan A13
#define Vlame_SKiri A14
#define Vlame_Kiri A15

#define pinUVtron 26
#define pinLedUV 27

String Vlamed[5]={"Kanan ","S Kanan ","Depan ","S Kiri ","Kanan "}; 
int Read_Vlame[5]={};
int Read_Colour = 0;
boolean Read_UVtron = false;
boolean KeLedUV = LOW;

void Vlame_Reading(){
  Read_Colour = analogRead(Colour_Sensor);
  Read_UVtron = digitalRead(pinUVtron);
  //Read_Vlame[0]= analogRead(Vlame_Kanan);
  Read_Vlame[1]= analogRead(Vlame_SKanan);
  Read_Vlame[2]= analogRead(Vlame_Depan);
  Read_Vlame[3]= analogRead(Vlame_SKiri);
  Read_Vlame[4]= analogRead(Vlame_Kiri);
//  for(int i = 0; i < 5; i++){
//    Serial.print("Flame ");
//    Serial.print(Vlamed[i]);
//    Serial.print(" ");
//    Serial.println(Read_Vlame[i]);
//  }
//  Serial.print("Colour ");
//  Serial.println(Colour_Sensor);
//  Serial.print("UVtron :");
//  Serial.println(Read_UVtron);
}
