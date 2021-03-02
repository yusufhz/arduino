#define triggerPin 9
#define echoPin 10

long duration;
int jarak;

void setup() {
  pinMode (8, OUTPUT);
  pinMode (11, OUTPUT);
  pinMode (triggerPin, OUTPUT);
  pinMode (echoPin, INPUT);
  Serial.begin(115200);
  digitalWrite(8, 1);
  digitalWrite(11, 0);
}

void loop() {
  digitalWrite (triggerPin, LOW);
  delayMicroseconds(2);

  digitalWrite(triggerPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin,LOW);

  duration = pulseIn(echoPin,HIGH);
  jarak = duration*0.034/2;
  if(jarak >= 3){
    jarak = jarak +1; 
  }
  else if(jarak==4){
    jarak=4;
  }
  else if(jarak < 3){
    jarak = duration*0.034/2;
  }
  Serial.print("Distance : ");
  Serial.print(jarak);
  Serial.println("cm");
}
