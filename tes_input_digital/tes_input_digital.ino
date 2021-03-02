#define pin 12
int a = 0;
void setup() {
  pinMode(pin, INPUT);
  Serial.begin(9600);
}

void loop() {
  a = digitalRead(pin);
  Serial.println(a);
  delay(300);
}
