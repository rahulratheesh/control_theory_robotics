#ifndef ELECTRICRAY_H
#define ELECTRICRAY_H

#include <Arduino.h>

// Pin aliases for the motor controller.
#define    L_CTRL_1   2
#define    L_CTRL_2   4
#define    PWM_L      3

#define    R_CTRL_1   7
#define    R_CTRL_2   5
#define    PWM_R      6

// PCINT functionality aliases. 
// Each PCINT has a value set up when the class member gets created, and the PCINT service routine 
// will handle choosing the appropriate response to the interrupt.

#define NOT_IN_USE    0
#define WHISKER       1
#define LENCODER      2
#define RENCODER      3
#define SW_SERIAL     4

#define PCINT_A0      0
#define PCINT_A1      1
#define PCINT_A2      2
#define PCINT_A3      3
#define PCINT_A4      4
#define PCINT_A5      5

enum WHEEL {LEFT, RIGHT, BOTH};

// These three functions need to work from within multiple classes.
// So keep them separate and add them as friend functions where appropriate.


// The "role" of each pin is stored in an array which is accessed in the interrupt
// handler to determine what should be done on a falling edge PC interrupt.
void setPinChangeInterrupt(int pin, byte role); 

// This is the function which actually handles the work after the interrupt has identified
//  which pin caught the interrupt.
void pinFunctionHandler(byte pinIndex); 

// Globally accessible motor brake.
void brake(void);  

void PC1Handler(byte PCTemp);

class Motor
{
  public:
    // Constructor. Mainly sets up pins.
    Motor();
  // Drive in direction given by sign, at speed given by magnitude of the parameter.      
  void drive(int speed);
  // Pivot more or less in place. Turns motors in opposite directions.
  // Positive values correspond to anti-clockwise rotation.
  void turn(int speed);  
  // Drive just the left motor, as drive().
  void rightDrive(int speed); 
  // Drive just the right motor, as drive().
  void leftDrive(int speed);  
  // Stop motors, but slow halt
  void stopMotor();      
  // Quick-stop the motors, shorting the leads.      
  void brake();  
  // Stop right motor, as with stop().         
  void rightStop();  
  // Stop left motor, as with stop().     
  void leftStop();    
  // Quick-stop left motor, as with brake().    
  void leftBrake();
  // Quick-stop right motor, as with brake().       
  void rightBrake();      
  
  private:
    
  void leftFwd(byte speed); 
  void leftRev(byte speed);
  void rightFwd(byte speed);
  void rightRev(byte speed);
};

class WheelEncoder
{
  // Needs access to lDir and rDir.
  friend class Motor;
  // Called from within the ISRs, this function increments the counts by calling wheelTick().
  friend void pinFunctionHandler(byte pinIndex); 
                                                          
  public:
    WheelEncoder(int lPin, int rPin);
    
    void clearEnc(WHEEL wheel);
    long getTicks(WHEEL wheel); 
    
  private:
    void wheelTick(WHEEL wheel); 
                            
    long lCounts;           
    long rCounts;           
    char lDir;               
    char rDir;
};

class ProximitySensor
{
  public:
    ProximitySensor(int trigPin, int echoPin);
		
    unsigned int reading();
		
  private:
    int distance;
    int trigPin;
    int echoPin;		
};

class Pose
{
  
  public:
    Pose() {}
    Pose(float xPos, float yPos, float headingAngle)
    {
      x = xPos;
      y = yPos;
      theta = headingAngle;
      
    }
    
    void setPose(float xPos, float yPos, float headingAngle)
    {
      x = xPos;
      y = yPos;
      theta = headingAngle;
      
    }
  
  private:
    float x;
    float y;
    float theta;

};

class ElectricRay
{
  public:
    
    ElectricRay(Pose pose, float radius, float ticks, float length)
    {
      p = pose;
      R = radius;
      N = ticks;
      L = length;
    }
    
    float diff2univ(float wl, float wr)
    {
    }
    
    float diff2uniw(float wl, float wr)
    {
    }
    
  private:
    Pose p;
    // diameter
    float R;
    // Number of ticks in 1 revolution
    float N;
    // length between the wheels
    float L;

};

class Supervisor
{
  public:
    float uni2diffwl(float v, float w)
    {      
      float sum = 2 * v / R;
      float dif = L * w / R;
      float wl = (sum - dif)/2;
      return wl;
    }
    
    float uni2diffwr(float v, float w)
    {      
      float sum = 2 * v / R;
      float dif = L * w / R;
      float wr = (sum + dif)/2;
      return wr;
    }
  
};


#endif
