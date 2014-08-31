/*
  Author: Alberto Tam Yong
  Date: 08-30-14

  Robot Board with Bluefruit EZ-Link - Serial, Bluetooth Module
  Two DC motors and one servo motor (attached to A5)
*/

#include <Servo.h>

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

void manualControlBluetooth(char command)
{
  if(command == 'F')
  {
    //Forward
    motor(0,1,speedStraight);
    motor(1,1,speedStraight);
    Serial.println("Forward");
  }
  else if(command == 'B')
  {
    //Back
    motor(0,0,speedStraight);
    motor(1,0,speedStraight);
    Serial.println("Backward");
  }
  else if(command == 'L')
  {
    //Left
    motor(0,0,speedTurn);
    motor(1,1,speedTurn);
  }
  else if(command == 'R')
  {
    //Right
    motor(0,1,speedTurn);
    motor(1,0,speedTurn);
  }
  else if(command == 'I')
  {
    //Forward Right
    motor(0,1,speedStraight);
    motor(1,1,speedTurn);
  }
  else if(command == 'G')
  {
    //Forward Left
    motor(0,1,speedTurn);
    motor(1,1,speedStraight);
  }
  else if(command == 'J')
  {
    //Back Right
    motor(0,0,speedStraight);
    motor(1,0,speedTurn);
  }
  else if(command == 'H')
  {
    //Back Left
    motor(0,0,speedTurn);
    motor(1,0,speedStraight);
  }
  else if(command == 'S')
  {
    //Stop
    motor(0,0,0);
    motor(1,0,0);
  }
  else if(command == '0')
  {
    servo1.write(180);
    delay(15);
  }
  else if(command == '1')
  {
    servo1.write(165);
    delay(15);
  }
  else if(command == '2')
  {
    servo1.write(150);
    delay(15);
  }
  else if(command == '3')
  {
    servo1.write(135);
    delay(15);
  }
  else if(command == '4')
  {
    servo1.write(120);
    delay(15);
  }
  else if(command == '5')
  {
    servo1.write(105);
    delay(15);
  }
  else if(command == '6')
  {
    servo1.write(90);
    delay(15);
  }
  else if(command == '7')
  {
    servo1.write(75);
    delay(15);
  }
  else if(command == '8')
  {
    servo1.write(50);
    delay(15);
  }
  else if(command == '9')
  {
    servo1.write(25);
    delay(15);
  }
  else if(command == 'q')
  {
    servo1.write(0);
    delay(15);
  }
  else
  {
    //Stop
    motor(0,0,0);
    motor(1,0,0);
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
  motor(0,0,0);
  motor(1,0,0);
  delay(100);
  
  digitalWrite(en1,HIGH);
  digitalWrite(en2,HIGH);
  
  servo1.attach(A5);
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
