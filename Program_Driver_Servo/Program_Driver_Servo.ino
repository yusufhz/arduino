/*
 * Arduino_Serial_Servo.ino
 * Copyright (c) 2014-2017 Rtrobot. <admin@rtrobot.org>
 *  <http://rtrobot.org>
 */

void wait_serial_return_ok()
{
  int num=0;
  char c[16];
  while(1)
  {
    while(Serial.available() > 0)
    {
      c[num]=Serial.read();
      num++;
      if(num>=15)
        num=0;
    }
    if(c[num-2]=='O'&&c[num-1]=='K')
      break; 
  }
}

void setup() {
  Serial.begin(9600);
  delay(1000);
}

void loop() {
  Serial.print("#3P500T2000\r\n");
  wait_serial_return_ok();
  Serial.print("#3P1500T2000\r\n");  
  wait_serial_return_ok();
  Serial.print("#3P2500T2000D1555\r\n");  
  wait_serial_return_ok();
  Serial.print("#3P1500T2000\r\n");
  wait_serial_return_ok();
}
