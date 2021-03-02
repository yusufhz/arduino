#include "Nextion.h"

NexText textNumber = NexText(0, 3, "textNumber");

NexButton buttonPlus = NexButton(0, 4, "buttonPlus");

NexButton buttonMinus = NexButton (0, 5, "buttonMinus");

int number = 50;
char buffer [10] = {0};

/* 
 *  Register object
 */
NexTouch *nex_listen_list[] =
{
 &tetxNumber,
 &buttonPlus,
 &buttonMinus,
 NULL 
};

/*
 * Button0 componen pop callback functon.
 */

void buttonPlusPopCallback(void *ptr){
  dbSerialPrintln("buttonPlusPopCallback");

  if (number < 100) number+=1;

  memset(buffer, 0, sizeof(buffer));// clear buffer
  itoa(number, buffer, 10);
  textNumber.setText(buffer);
}
void buttonMinusPushCallback(void *ptr){
  dbSerialPrintln("buttonMinusPushCallback");

  if (number < 100) number-=1;

  memset(buffer, 0, sizeof(buffer));// clear buffer
  itoa(number, buffer, 10);
  textNumber.setText(buffer);
 }
 
void setup() {
  // put your setup code here, to run once:
  nexInit();

  Serial.begin(115200);

  buttonPlus.attachPop(buttonPlusPopCallback);

  buttonMinus.attachPush(buttonMinusPushCallback);

  dbSerialPrintln("Setup done");
}

void loop() {
  // put your main code here, to run repeatedly:
  nexLoop(nex_listen_list);
}
