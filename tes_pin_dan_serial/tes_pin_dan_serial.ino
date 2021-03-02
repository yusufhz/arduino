int pin[]={2,3,4,5,6,7,8,13};

void setup() {
  // put your setup code here, to run once:
  for(int i = 0; i < 8; i++){
    pinMode (pin[i], OUTPUT);
  }
  Serial.begin(9600);
  Serial.println("Mulai");
  delay(400);
}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i = 0; i < 8; i++){
    digitalWrite (pin[i], 1);
    Serial.print("Led nyala ");
    Serial.println(pin[i]);    
    delay(100);
    digitalWrite (pin[i], 0);
    delay(100);    
  }
}
