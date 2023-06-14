/*

This project is based on 3 ultrasonic distance sensors that measure the velocity
of a fast moving car and then rotate two servos that activate or deactivate a speed breaker.

Activate or deactivate speed breaker means rotate the speed breaker cylinder by 180 degree
Activate means: the cylinder is in such a way that the road and speed breaker are at the same level such that there is no effect of it
Deactivate means: the cylinder is in such a way that the speed breaker level is above the road level and there is strong effect of the speed breaker


Ultrasonic Distance Sensor 1 :
Position: starting extreme
trig pin=7
echo pin=8

Ultrasonic Distance Sensor 2 :
Position: middle
trig pin=6
echo pin=5

Ultrasonic Distance Sensor 3 :
Position: ending extreme
trig pin=11
echo pin=12

Left servo output pin = 9
Right servo output pin = 10
*/

// include the servo library
#include <Servo.h>

// define the pin numbers and the variables used for calculation
const int trigPin1 = 7;
const int echoPin1 = 8;
const int trigPin2 = 6;
const int echoPin2 = 5;
const int trigPin3 = 11;
const int echoPin3 = 12;
const int out1 = 13;
const int out2 = 13;
Servo servol;
Servo servor;
const int servolpin = 9;
const int servorpin = 10;
unsigned long mil;
long duration1;
double distance1;
long duration2;
double distance2;
long duration3;
double distance3;
double trigDistance;
double timePeriod;
double velocity;
double m1,m2,m3;
boolean isActivated = false;

// set the trigger velocity according to your need
const double triggerVelocity=0.7; // in m/s

void setup() {
  pinMode(trigPin1, OUTPUT); 
  pinMode(echoPin1, INPUT); 
  pinMode(trigPin2, OUTPUT); 
  pinMode(echoPin2, INPUT); 
  pinMode(trigPin3, OUTPUT); 
  pinMode(echoPin3, INPUT); 
  pinMode(LED_BUILTIN,OUTPUT);
  digitalWrite(LED_BUILTIN,LOW);
  servol.attach(servolpin);
  servor.attach(servorpin);
  servol.write(0);
  servor.write(180);
  trigDistance = 20.0;
  delay(100);
} 
 
 
double measure1() {
  //Measure the distance by the first sensor
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  duration1 = pulseIn(echoPin1, HIGH);
  distance1 = duration1*0.034/2;
  return distance1;
}
 

double measure2() {
  //Measure the distance by the second sensor
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  duration2 = pulseIn(echoPin2, HIGH);
  distance2 = duration2*0.034/2;
  return distance2;
}




double measure3() {
  //Measure the distance by the third sensor
  digitalWrite(trigPin3, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin3, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin3, LOW);
  duration3 = pulseIn(echoPin3, HIGH);
  distance3 = duration3*0.034/2;
  return distance3;
}


void activate()
{
  // Do whatever you have to do once condition is met
  servol.write(180);
  servor.write(0);
  isActivated = true;
  digitalWrite(LED_BUILTIN,HIGH);
  digitalWrite(out1,HIGH);
  digitalWrite(out2,HIGH);
  
  
}

void deactivate()
{
  //Revert all the changes made in the activate function
  servol.write(0);
  servor.write(180);
  isActivated = false;
  digitalWrite(LED_BUILTIN,LOW);
  digitalWrite(out1,LOW);
  digitalWrite(out2,LOW);
  
}

void loop()
{
  //defining a goto tag
  start:
  m3 = measure3();
  if(m3 <= trigDistance)
  {
   deactivate();
  }
  
  do
  {
    m1=measure1();
  }while(m1>=1900)

  
  
  if(m1 <= trigDistance)
  {
    mil = millis();
    while(isActivated == false)
    {
      m1 = measure1();
      if(m1 <= trigDistance)
      {
        mil = millis();
      }
      m2 = measure2();
      m2tag:
      if(m2 >= 1900)
      {
       m2 = measure2();
       goto m2tag;
      }
      
      if(m2 <= trigDistance)
      {
      
        timePeriod = millis() - mil;
        timePeriod = timePeriod/1000;
        
        velocity = 0.17/(timePeriod);
        if(velocity >= triggerVelocity)
        {
          activate();
        }
        goto start;
      }
    }
  }
}
