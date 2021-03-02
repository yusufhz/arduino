#define relay1 5
#define relay2 6
#define relay3 7

void setup() {
  pinMode (relay1, OUTPUT);
  pinMode (relay2, OUTPUT);
  pinMode (relay3, OUTPUT);

  digitalWrite (relay1, HIGH);
  digitalWrite (relay2, HIGH);
  digitalWrite (relay3, HIGH);
  
}

void loop() {
  digitalWrite (relay1, LOW);
  digitalWrite (relay2, LOW);
  digitalWrite (relay3, LOW);
  delay(500);
  
  digitalWrite (relay1, HIGH);
  digitalWrite (relay2, HIGH);
  digitalWrite (relay3, HIGH);
  delay(500);
}
