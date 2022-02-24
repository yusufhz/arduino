#define Vlame_Kanan A1
#define Vlame_SKanan A2
#define Vlame_Depan A3
#define Vlame_SKiri A4
#define Vlame_Kiri A5

#define UVtron 2
String Vlamed[5]={"Kanan ","S Kanan ","Depan ","S Kiri ","Kanan "}; 
int Read_Vlame[5]={0,0,0,0,0};
boolean Read_UVtron = false;

void setup() {
  pinMode (UVtron, INPUT);
  Serial.begin(9600);
}

void loop() {
  Read_UVtron = digitalRead(UVtron);
  Read_Vlame[0]= analogRead(Vlame_Kanan);
  Read_Vlame[1]= analogRead(Vlame_SKanan);
  Read_Vlame[2]= analogRead(Vlame_Depan);
  Read_Vlame[3]= analogRead(Vlame_SKiri);
  Read_Vlame[4]= analogRead(Vlame_Kiri);
  for(int i = 0; i < 5; i++){
    Serial.print("Flame ");
    Serial.print(Vlamed[i]);
    Serial.print(" ");
    Serial.println(Read_Vlame[i]);
  }
  Serial.print("UVtron ");
  Serial.println(Read_UVtron);
  delay(500);
}
