//The servo motor is connected to the digital 2 port, and the EMG sensor is connected to the analog 0 port.

#include <Servo.h>
#include <MsTimer2.h>
Servo myservo;  // create servo object to control a servo

#define SEV 10
#define Relax 0
#define Shrink 180

unsigned char Hand_Angle = 0;
unsigned char Num = 0;

void Hand_Relax()               //放松
{
  if (Hand_Angle==Shrink)       //如果手是紧缩的
  {
    while(Hand_Angle!=Relax)
    {
      Hand_Angle--;
      myservo.write(Hand_Angle);
      delay(SEV); 
    }      
  }
}

void Hand_Shrink()             //握拳
{
  if (Hand_Angle==Relax)       //如果手是放松的
  {
    while(Hand_Angle!=Shrink)
    {
      Hand_Angle++;
      myservo.write(Hand_Angle);
      delay(SEV); 
    }      
  }
}

void action()
{
  if(Num>0)
    Hand_Shrink();
  else Hand_Relax();

  //delay(10000);
  
  Num = 0;
}

void setup() {
  Serial.begin(9600);
  myservo.attach(2);
  MsTimer2::set(1000,action);
  MsTimer2::start();
  Num = 0;
}


void loop() {
  int sensorValue = analogRead(A0);
  //Serial.println(sensorValue);
  if(sensorValue>50)Num++;
  Serial.println(Num);
  delay(20);
}
