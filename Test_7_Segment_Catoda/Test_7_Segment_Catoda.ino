  int a = 2, b = 3, c = 4, d = 5;
  int e = 6, f = 7, g = 8, t = 9;
  int de = 1000;
  char L = LOW;
  char H = HIGH; 
void setup() {

  pinMode (a, OUTPUT);
  pinMode (b, OUTPUT);
  pinMode (c, OUTPUT);
  pinMode (d, OUTPUT);
  pinMode (e, OUTPUT);
  pinMode (f, OUTPUT);
  pinMode (g, OUTPUT);
  pinMode (t, OUTPUT);
 
}
void satu() {
  digitalWrite(a, H);
  digitalWrite(b, L);
  digitalWrite(c, L);
  digitalWrite(d, H);
  digitalWrite(e, H);
  digitalWrite(f, H);
  digitalWrite(g, H);
  delay(50);
  digitalWrite(t, L); 
  delay(50);
  digitalWrite(t, H); 
}
void dua(){
  digitalWrite(a, L);
  digitalWrite(b, L);
  digitalWrite(c, H);
  digitalWrite(d, L);
  digitalWrite(e, L);
  digitalWrite(f, H);
  digitalWrite(g, L);
  delay(50);
  digitalWrite(t, L); 
  delay(50);
  digitalWrite(t, H); 
}
void tiga() {
  digitalWrite(a, L);
  digitalWrite(b, L);
  digitalWrite(c, L);
  digitalWrite(d, L);
  digitalWrite(e, H);
  digitalWrite(f, H);
  digitalWrite(g, L);
  delay(50);
  digitalWrite(t, L); 
  delay(50);
  digitalWrite(t, H); 
}
void empat() {
  digitalWrite(a, H);
  digitalWrite(b, L);
  digitalWrite(c, L);
  digitalWrite(d, H);
  digitalWrite(e, H);
  digitalWrite(f, L);
  digitalWrite(g, L);
  delay(50);
  digitalWrite(t, L); 
  delay(50);
  digitalWrite(t, H); 
}
void lima() {
  digitalWrite(a, L);
  digitalWrite(b, H);
  digitalWrite(c, L);
  digitalWrite(d, L);
  digitalWrite(e, H);
  digitalWrite(f, L);
  digitalWrite(g, L);
  delay(50);
  digitalWrite(t, L); 
  delay(50);
  digitalWrite(t, H); 
}
void enam() {
  digitalWrite(a, L);
  digitalWrite(b, H);
  digitalWrite(c, L);
  digitalWrite(d, L);
  digitalWrite(e, L);
  digitalWrite(f, L);
  digitalWrite(g, L);
  delay(50);
  digitalWrite(t, L); 
  delay(50);
  digitalWrite(t, H); 
}
void tujuh() {
  digitalWrite(a, L);
  digitalWrite(b, L);
  digitalWrite(c, L);
  digitalWrite(d, H);
  digitalWrite(e, H);
  digitalWrite(f, H);
  digitalWrite(g, H);
  delay(50);
  digitalWrite(t, L); 
  delay(50);
  digitalWrite(t, H); 
}
void delapan() {
  digitalWrite(a, L);
  digitalWrite(b, L);
  digitalWrite(c, L);
  digitalWrite(d, L);
  digitalWrite(e, L);
  digitalWrite(f, L);
  digitalWrite(g, L);
  delay(50);
  digitalWrite(t, L); 
  delay(50);
  digitalWrite(t, H); 
}
void sembilan() {
  digitalWrite(a, L);
  digitalWrite(b, L);
  digitalWrite(c, L);
  digitalWrite(d, L);
  digitalWrite(e, H);
  digitalWrite(f, L);
  digitalWrite(g, L);
  delay(50);
  digitalWrite(t, L); 
  delay(50);
  digitalWrite(t, H); 
}
void nol() {
  digitalWrite(a, L);
  digitalWrite(b, L);
  digitalWrite(c, L);
  digitalWrite(d, L);
  digitalWrite(e, L);
  digitalWrite(f, L);
  digitalWrite(g, H);
  delay(50);
  digitalWrite(t, L); 
  delay(50);
  digitalWrite(t, H); 
}

void loop() {
  //for (int i=0; i>=10; i++)
  /*satu(); 
  delay(de);
  dua();
  delay(de);
  tiga();
  delay(de);
  empat();
  delay(de);
  lima();
  delay(de);
  enam();
  delay(de);
  tujuh();
  delay(de);
  delapan();
  delay(de);
  sembilan();
  delay(de);
  nol();
  delay(de);*/
  digitalWrite(9, H);
  delay(1000);
  digitalWrite(9, L);
  delay(1000);
}

