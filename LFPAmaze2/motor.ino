void calculate_pid(void)
{ 
  //int MotorSpeedKa = 100;
  //int MotorSpeedKi = 110;

  Kp = 150;
  Ki = 30;
  Kd = 170;

  P = error;
  I = I + previous_I;
  D = error - previous_error;

  PID_value = (Kp * P) + (Ki * I) + (Kd * D);

  left_motor_speed = MotorSpeed - PID_value;
  right_motor_speed = MotorSpeed + PID_value;
  powermotor = MotorSpeed - PID_value;
  

  // The motor speed should not exceed the max PWM value
  left_motor_speed = constrain(left_motor_speed, 0, 100);
  right_motor_speed = constrain(right_motor_speed, 0, 100);
  powermotor = constrain(powermotor, 0, 100);

//    Serial.print(PID_value);
//    Serial.print("\t");
//    Serial.print(left_motor_speed);
//    Serial.print("\t");
//    Serial.println(right_motor_speed);
  forward();
  previous_I = I;
  previous_error = error;
}

void forward(){
  analogWrite(motorkiF, left_motor_speed);
  analogWrite(motorkiB, 0);
  analogWrite(motorkaF, right_motor_speed);
  analogWrite(motorkaB, 0);   
}

void left(){
  analogWrite(motorkiF, 0);
  analogWrite(motorkiB, MotorSpeed);
  analogWrite(motorkaF, MotorSpeed);
  analogWrite(motorkaB, 0);
}

void right(){
  analogWrite(motorkiF, MotorSpeed);
  analogWrite(motorkiB, 0);
  analogWrite(motorkaF, 0);
  analogWrite(motorkaB, MotorSpeed);
}

void back(){
  analogWrite(motorkiF, 0);
  analogWrite(motorkiB, MotorSpeed);
  analogWrite(motorkaF, MotorSpeed);
  analogWrite(motorkaB, 0);
}

void stopbot(){
  analogWrite(motorkiF, 0);
  analogWrite(motorkiB, 0);
  analogWrite(motorkaF, 0);
  analogWrite(motorkaB, 0);
}
