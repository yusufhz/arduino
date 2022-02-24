#define led1 13
#define led2 12

void setup() {
  pinMode (led1, OUTPUT);
  pinMode (led2, OUTPUT);
}

void loop() {
  //versi nyala 1
  digitalWrite (led1, HIGH);
  digitalWrite (led2, HIGH);
  delay(200);

  digitalWrite (led1, LOW);
  digitalWrite (led2, LOW);
  delay(200);

  digitalWrite (led1, HIGH);
  digitalWrite (led2, HIGH);
  delay(200);

  digitalWrite (led1, LOW);
  digitalWrite (led2, LOW);
  delay(200);
  
  //versi flip-flop
  digitalWrite (led1, HIGH);
  delay(200);
  digitalWrite (led1, LOW);
  digitalWrite (led2, HIGH);
  delay(200);
  digitalWrite (led2, LOW);
  digitalWrite (led1, HIGH);
  delay(200);
  digitalWrite (led1, LOW);
  digitalWrite (led2, HIGH);
  delay(200);
  digitalWrite (led2, LOW);
  delay(200);
}
