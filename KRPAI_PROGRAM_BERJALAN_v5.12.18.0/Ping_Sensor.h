const int pingkan = 4;
const int pingserkan = 5;
const int pingdep = 17;
const int pingserkir = 7;
const int pingkir = 8;

unsigned long durkan, Jarak_Kanan;
unsigned long durserkan, Jarak_SKanan;
unsigned long durdep, Jarak_Depan;
unsigned long durserkir, Jarak_SKiri;
unsigned long durkir, Jarak_Kiri;

boolean Rproxykan = 1;
boolean Rproxydep = 1;

#define proxydep  30
#define proxykan A0
#define proxykir A1
//#define proxybel 12

void proxymity(){
  Rproxykan = digitalRead(proxykan);
  Rproxydep = digitalRead(proxydep);  
//  Serial.print("Proxymity depan : ");
//  Serial.println(Rproxydep);
}

long KonversiToJarak(long microseconds) {
  return microseconds / 29 / 2;
}

//====== Ping Kanan ========
void sensor_pingkan() {
  pinMode(pingkan, OUTPUT);
  digitalWrite(pingkan, LOW);
  delayMicroseconds(2);
  digitalWrite(pingkan, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingkan, LOW);

  pinMode(pingkan, INPUT);
  durkan = pulseIn(pingkan, HIGH);

  Jarak_Kanan = KonversiToJarak(durkan);

//  Serial.print("Jarak Kanan = ");
//  Serial.print(Jarak_Kanan);
//  Serial.println(" cm");
}//==== END Ping Kanan ========

//====== Ping Serong Kanan ========
void sensor_pingserkan() {
  pinMode(pingserkan, OUTPUT);
  digitalWrite(pingserkan, LOW);
  delayMicroseconds(2);
  digitalWrite(pingserkan, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingserkan, LOW);

  pinMode(pingserkan, INPUT);
  durserkan = pulseIn(pingserkan, HIGH);

  Jarak_SKanan = KonversiToJarak(durserkan);

//  Serial.print("Jarak Serong Kanan = ");
//  Serial.print(Jarak_SKanan);
//  Serial.println(" cm");
}//==== END Ping Kanan ========

//====== Ping Depan ===========
void sensor_pingdep() {
  pinMode(pingdep, OUTPUT);
  digitalWrite(pingdep, LOW);
  delayMicroseconds(2);
  digitalWrite(pingdep, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingdep, LOW);

  pinMode(pingdep, INPUT);
  durdep = pulseIn(pingdep, HIGH);

  Jarak_Depan = KonversiToJarak(durdep);
  
//    Serial.print("Jarak Depan = ");
//    Serial.print(Jarak_Depan);
//    Serial.println(" cm");
}// ==== END Ping Depan =======

//====== Ping Serong Kiri ============
void sensor_pingserkir() {
  pinMode(pingserkir, OUTPUT);
  digitalWrite(pingserkir, LOW);
  delayMicroseconds(2);
  digitalWrite(pingserkir, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingserkir, LOW);

  pinMode(pingserkir, INPUT);
  durserkir = pulseIn(pingserkir, HIGH);
  
  Jarak_SKiri = KonversiToJarak(durserkir);
  
//  Serial.print("Jarak Serong Kiri = ");
//  Serial.print(Jarak_SKiri);
//  Serial.println(" cm");
}// ==== END Ping Depan =======

//====== Ping Kiri ============
void sensor_pingkir() {
  pinMode(pingkir, OUTPUT);
  digitalWrite(pingkir, LOW);
  delayMicroseconds(2);
  digitalWrite(pingkir, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingkir, LOW);

  pinMode(pingkir, INPUT);
  durkir = pulseIn(pingkir, HIGH);
  
  Jarak_Kiri = KonversiToJarak(durkir);
  
//  Serial.print("Jarak Kiri = ");
//  Serial.print(Jarak_Kiri);
//  Serial.println(" cm");
}//===== END Ping Kiri =========
