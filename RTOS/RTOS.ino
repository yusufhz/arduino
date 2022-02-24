#include <Arduino_FreeRTOS.h>
void Taskcontrol1(void *pvParameters );
//void Taskcontrol2(void *pvParameters );
//void Taskcontrol3(void *pvParameters );

void setup() {
  // put your setup code here, to run once:
xTaskCreate(
  Taskcontrol1
  , (const portCHAR *) "Servo1"
  , 200
  , NULL
  , 1
  , NULL  );
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

}

void Taskcontrol1 (void *pvParameters)
{
  (void) pvParameters;

   for (;;)
   {
    move(1, 1300, 500);
    delay(500);
    move(1, 1700, 500);
    delay(500);
   }
}
//
//void Taskcontrol2 (void *pvParameters)
//{
//  (void) pvParameters;
//
//   for (;;)
//   {
//    move(2, 1500, 500);
//    delay(900);
//    move(2, 1700, 500);
//    delay(900);
//   }
//}

//void Taskcontrol3 (void *pvParameters)
//{
//  (void) pvParameters;
//
//   for (;;)
//   {
//    move(3, 1300, 500);
//    delay(900);
//    move(3, 1700, 500);
//    delay(900);
//   }
//}

void move (int servo, int position, int time){
  Serial.print("#");
  Serial.print(servo);
  Serial.print("P");
  Serial.print(position);
  Serial.print("T");
  Serial.println(time);
}
