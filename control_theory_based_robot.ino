#include "ElectricRay.h"
#define TOO_CLOSE 10
#define MAX_DISTANCE (TOO_CLOSE * 20)

Motor motor;
// left, right wheel encoders
WheelEncoder wheelEncoder = WheelEncoder(A2, A3); 
// left proximity sensor
ProximitySensor leftSensor = ProximitySensor(12, 13);
// right proximity sensor
ProximitySensor rightSensor = ProximitySensor(10, 11);
// middle proximity sensor
ProximitySensor middleSensor = ProximitySensor(A5, A4);
// Pose
Pose p = Pose(0, 0, 0);
// Electric Ray Robot
ElectricRay eray = ElectricRay(p, 3.25, 4, 16);


void setup()
{
  Serial.begin(9600);
  wheelEncoder.clearEnc(BOTH);
  float wl = eray.uni2diffwl(100, 100);
  float wr = eray.uni2diffwr(100, 100);
  Serial.println(wl);
  Serial.println(wr);
}

void loop()
{
  
}

