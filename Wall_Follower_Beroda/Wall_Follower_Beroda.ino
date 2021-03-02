// Trigger //
#define TrigKan 2
#define TrigSKan 3
#define TrigDep 4

// Ech0 //
#define EchoKan 7
#define EchoSKan 8
#define EchoDep 9

// pin Motor (PWM) //
#define mkanan_maju 5
#define mkanan_mundur 6
#define mkiri_maju 10
#define mkiri_mundur 11

#define pinLed 13

byte nilai_makanan = 0;
byte nilai_mukanan = 0;
byte nilai_makiri = 0;
byte nilai_mukiri = 0;

unsigned long disKanan, duration;
unsigned long disSKanan, duration2;
unsigned long disDepan, duration3;

unsigned long waktuS;
unsigned long waktuL1 = 0;
unsigned long waktuL2 = 0;
unsigned long waktuL3 = 0;
int interval = 200;
int interval2 = 50;

void setup() {
  Serial.begin(9600);
  pinMode(TrigKan, OUTPUT);
  pinMode(TrigSKan, OUTPUT);
  pinMode(TrigDep, OUTPUT);

  pinMode(EchoKan, INPUT);
  pinMode(EchoSKan, INPUT);
  pinMode(EchoDep, INPUT);

  pinMode(pinLed, OUTPUT);
}

void loop() {
  waktuS = millis();
  if(waktuS - waktuL1 > interval){
    waktuL1 = waktuS;
    pingKanan();
    pingSKanan();
    pingDepan();
    Serial.print("Kanan = ");
    Serial.println(disKanan);
    Serial.print("SKanan = ");
    Serial.println(disSKanan);
    Serial.print("Depan = ");
    Serial.println(disDepan);
  }
  if(waktuS - waktuL2 > interval2){
    waktuL2 = waktuS;
    if(disDepan > 17){
      if(disKanan > 15){//sensor derong detek tembok
        if(disSKanan < 4){
          nilai_makanan = 0;
          nilai_mukanan = 50;
          nilai_makiri = 0;
          nilai_mukiri = 100;
        }
        else if(disSKanan > 300){
          nilai_makanan = 0;
          nilai_mukanan = 100;
          nilai_makiri = 0;
          nilai_mukiri = 100;
        }
        else {// sensor serong loss
          nilai_makanan = 100;
          nilai_mukanan = 0;
          nilai_makiri = 100;
          nilai_mukiri = 0;
        }
      }
      if(disKanan >= 15 && disKanan <= 17){
        if(disSKanan < 4){
          nilai_makanan = 0;
          nilai_mukanan = 50;
          nilai_makiri = 0;
          nilai_mukiri = 100;
        }
        else if(disSKanan > 300){
          nilai_makanan = 0;
          nilai_mukanan = 100;
          nilai_makiri = 0;
          nilai_mukiri = 100;
        }
        else {// sensor serong loss
          nilai_makanan = 100;
          nilai_mukanan = 0;
          nilai_makiri = 100;
          nilai_mukiri = 0;
        }
      }
      if(disKanan < 15){
        if(disSKanan < 4){
          nilai_makanan = 0;
          nilai_mukanan = 100;
          nilai_makiri = 0;
          nilai_mukiri = 100;
        }
        else if(disSKanan > 300){
          nilai_makanan = 0;
          nilai_mukanan = 100;
          nilai_makiri = 0;
          nilai_mukiri = 100;
        }
        else {// sensor serong loss
          nilai_makanan = 100;
          nilai_mukanan = 0;
          nilai_makiri = 100;
          nilai_mukiri = 0;
        }
      }
    }
    else if(disDepan <= 20){ // depan mentok
        nilai_makanan = 100;
        nilai_mukanan = 0;
        nilai_makiri = 0;
        nilai_mukiri = 100;
    }
  }
  if(waktuS - waktuL3 > interval2){
    waktuL3 = waktuS;
    motor();
  }
}

//=================================================================

void pingKanan(){
  digitalWrite (TrigKan, LOW);
  delayMicroseconds(2);

  digitalWrite(TrigKan,HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigKan,LOW);

  duration = pulseIn(EchoKan,HIGH);
  disKanan = duration*0.034/2;
  if(disKanan >= 3){
    disKanan = disKanan +1; 
  }
  else if(disKanan == 4){
    disKanan = 4;
  }
  else if(disKanan < 3){
    disKanan = duration*0.034/2;
  }
}

void pingSKanan(){
  digitalWrite (TrigSKan, LOW);
  delayMicroseconds(2);

  digitalWrite(TrigSKan,HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigSKan,LOW);
  duration2 = pulseIn(EchoSKan,HIGH);
  disSKanan = duration2*0.034/2;
  if(disSKanan >= 3){
    disSKanan = disSKanan +1; 
  }
  else if(disSKanan == 4){
    disSKanan = 4;
  }
  else if(disSKanan < 3){
    disSKanan = duration2*0.034/2;
  }
}

void pingDepan(){
  digitalWrite (TrigDep, LOW);
  delayMicroseconds(2);

  digitalWrite(TrigDep,HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigDep,LOW);

  duration3 = pulseIn(EchoDep,HIGH);
  disDepan = duration3*0.034/2;
  if(disDepan >= 3){
    disDepan = disDepan +1; 
  }
  else if(disDepan == 4){
    disDepan = 4;
  }
  else if(disDepan < 3){
    disDepan = duration3*0.034/2;
  }
}

void motor(){
  analogWrite(mkiri_maju,nilai_makiri);
  analogWrite(mkiri_mundur,nilai_mukiri);
  analogWrite(mkanan_maju,nilai_makanan);
  analogWrite(mkanan_mundur,nilai_mukanan);
  delay(1);
}
