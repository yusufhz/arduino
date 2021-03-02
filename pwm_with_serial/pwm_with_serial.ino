#define lampu 6
// 10 kaB
// 11 kaF
// 9 kaF
// 6 kaB
String inputString;
int nilai_pwm = 0;
int lang;
void setup() {
  Serial.begin(9600);
}

void loop() {
  if(Serial.available()){
    nilai_pwm = Serial.parseInt();
  }
  Serial.print("Nilai PWM = ");
  Serial.println(nilai_pwm);
  if(nilai_pwm >0 && nilai_pwm <= 255){
  analogWrite(lampu,nilai_pwm);    
  Serial.print("Nilai PWM = ");
  Serial.println(nilai_pwm);
  }
  else {
    nilai_pwm = 0;//
  }
  delay(500);
}
