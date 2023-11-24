void setup() 
{
    DDRD |= B11111111; //Set D0-D7 as outputs
    DDRB |= B00001111; //Set D8-D11 as outputs
}

void loop() 
{
  // 1
  PORTD = B10110011;
  PORTB = B00001101;
  delay(100);
  //2
  PORTD = B10101101;
  PORTB = B11111101;
  delay(100);
  //3
  PORTD = B10011110;
  PORTB = B11111101;
  delay(100);
  //4
  PORTD = B01101110;
  PORTB = B11111101;
  delay(100);
  //5
    PORTD = B11110110;
  PORTB = B11111100;
  delay(100);
  //6
    PORTD = B01110110;
  PORTB =B11111011;
  delay(100);
  //7
    PORTD = B10110110;
  PORTB = B11110111;
  delay(100);
  //8
    PORTD = B10110101;
  PORTB = B11111011;
  delay(100);  
}
