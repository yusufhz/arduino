//inisialisasi sensor
#include <NewPing.h>
#define trigPin 2
#define echoPin 3
#define DISTANCE 8
#define sensorapi 7
#define Left 1
#define Right 2
#define Back 3
#define Line 4
#define Cross 5
#define Hall 6 
#define Fire 7
#define Noline 8
#define starter 12

boolean robot_run = false;

NewPing sonar(trigPin, echoPin, DISTANCE);
//sensor define
int mode;

int S0 = A1;
int S1 = A2;
int S2 = A3;
int S3 = A4;
int S4 = A5;
int S5 = A6;

int Mata0;
int Mata1;
int Mata2;
int Mata3;
int Mata4;
int Mata5;
int Mata6;
int Mata7;

//Array Sensor
int data;
unsigned char s[7];

//threshold sensor
int threshold = 250;

//delay times
#define checkTime 30
#define timeBeforeTurn 200

//inisialisasi motor
#define motorkiF 9
#define motorkiB 6
#define motorkaF 11
#define motorkaB 10
//Inisialisasi kecepatan motor
int MotorSpeed = 100;

unsigned int status1 = 0;
unsigned int status2 = 0;
unsigned int finish = 0;
boolean padam = false;
//inisialisasi maze
//max size of the path
#define pathSize 100
boolean mazeSolved;

//stores all the turns that the robot takes when it is solving the maze
char path[pathSize] = {};

//stores the path after it has been optimized
char optimizedPath[pathSize] = {};
char a1[pathSize] = {};
char a2[pathSize] = {};
char a3[pathSize] = {};
char a4[pathSize] = {};
int tempLength;
int pathLength;
int optimizedPathLength;
int pathIndex = 0;

// PID
float Kp;
float Ki;
float Kd;

float error = 0, P = 0, I = 0, D = 0, PID_value = 0;
float previous_error = 0, previous_I = 0;

float left_motor_speed;
float right_motor_speed;
float powermotor;

//robot output
#define kipas 4
#define buzzer 8
