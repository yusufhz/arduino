// pin PWM
#define merah 2
#define hijau 3
#define biru 4
int i = 500;
byte cred = 0;
byte cgreen = 0;
byte cblue = 0;
char data;
unsigned long waktu = 0;
unsigned long waktu_last = 0;
unsigned long interval = 1;

void setup() {
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  waktu = millis();
  if(Serial.available() > 0){
    data = Serial.read();
    if(data == 'R'){
      cred+=10;
    }
    if(data == 'G'){
      cgreen+=10;
    }
    if(data == 'B'){
      cblue+=10;
    }
    if(data == 'S'){
      cred-=10;
    }
    if(data == 'H'){
      cgreen-=10;
    }
    if(data == 'C'){
      cblue-=10;
    }
    if(data == '0'){
      cred=0;
      cblue=0;
      cgreen=0;
    }
  }
  if(waktu - waktu_last > interval){
    waktu_last = waktu;
    analogWrite(merah, cred);
    analogWrite(hijau, cgreen);
    analogWrite(biru, cblue);
  }
  Serial.print("Red = ");
  Serial.println(cred);
  Serial.print("Green = ");
  Serial.println(cgreen);
  Serial.print("Blue = ");
  Serial.println(cblue);
  delay(500);
}
