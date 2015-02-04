/*
  Author: Alberto Tam Yong
  Date: 09-09-14

  Two DC motors and one servo motor (attached to A3)
*/

#include <Servo.h>

#define servo A3
#define M1 0
#define M2 1
#define straight 1
#define reverse 0

Servo servo1;

//Setup motor speeds
int speedStraight = 255;
int speedTurn = 150;

//Setup motor controller pins
int en1 = 7;
int en2 = 8;
int motorPin[4]={9,10,3,11};

//Function to control the motor controller
//motor(<motor selection>,<motor direction>,<motor speed>);
//Motor selection: 0 or 1.
//Motor direction: 0 or 1.
//Motor speed: 0 to 255.
void motor(int motorSelect, int motorDirection, int motorSpeed)
{
  if(motorSelect == 0)
  {
    if(motorDirection == 0)
    {
      digitalWrite(motorPin[0],0);
      digitalWrite(motorPin[1],0);
      delay(20);
      analogWrite(motorPin[0],motorSpeed);
    }
    else if(motorDirection == 1)
    {
      digitalWrite(motorPin[0],0);
      digitalWrite(motorPin[1],0);
      delay(20);
      analogWrite(motorPin[1],motorSpeed);
    }
  }
  else if(motorSelect == 1)
  {
    if(motorDirection == 0)
    {
      digitalWrite(motorPin[2],0);
      digitalWrite(motorPin[3],0);
      delay(50);
      analogWrite(motorPin[2],motorSpeed);
    }
    else if(motorDirection == 1)
    {
      digitalWrite(motorPin[2],0);
      digitalWrite(motorPin[3],0);
      delay(50);
      analogWrite(motorPin[3],motorSpeed);
    }
  }
}

void setup()
{
  for(int i = 0; i < 4; i++)
  {
    pinMode(motorPin[i],OUTPUT);
  }
  pinMode(en1,OUTPUT);
  pinMode(en2,OUTPUT);
  
  Serial.begin(9600);
  
  //initiate motors stopped
  motor(M1,0,0);
  motor(M2,0,0);
  delay(100);
  
  digitalWrite(en1,HIGH);
  digitalWrite(en2,HIGH);
  
  servo1.attach(servo);
  delay(20);
  servo1.write(180); //initiate servo motor at 180 degrees
  Serial.println("Started");
}

void loop()
{
  if(Serial.available() > 0)
  {
    char reading = Serial.read();
    manualControlBluetooth(reading);
    delay(20);
  }
}
