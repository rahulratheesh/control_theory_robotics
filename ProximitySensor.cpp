#include "ElectricRay.h"

/******************************************************************************
Public functions for Proximity Sensor
******************************************************************************/

ProximitySensor::ProximitySensor(int trig, int echo)
{
  trigPin = trig;
  echoPin = echo;
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  distance = 0;
}

unsigned int ProximitySensor::reading()
{
  int duration;
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  return distance;
}

