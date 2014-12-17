#include "ElectricRay.h"
#include <Arduino.h>

extern WheelEncoder *encoder;

/******************************************************************************
Public functions for Motor
******************************************************************************/

Motor::Motor()
{
	pinMode(R_CTRL_1, OUTPUT);
	pinMode(R_CTRL_2, OUTPUT);
	pinMode(L_CTRL_1, OUTPUT);
	pinMode(L_CTRL_2, OUTPUT);
}

void Motor::stopMotor()
{
	leftStop();
	rightStop(); 
}

void Motor::brake()
{
	leftBrake();
	rightBrake(); 
}

void Motor::drive(int speed)
{
	if (speed > 0)
	{
		leftFwd((byte)(abs(speed)));
		rightFwd((byte)(abs(speed)));
	}
	else
	{
		leftRev((byte)(abs(speed)));
		rightRev((byte)(abs(speed)));
	}
}

void Motor::turn(int speed)
{
	if (speed > 0)
	{
		leftRev((byte)(abs(speed)));
		rightFwd((byte)(abs(speed)));
	}
	else
	{
		leftFwd((byte)(abs(speed)));
		rightRev((byte)(abs(speed)));
	}
}


void Motor::rightDrive(int speed)
{
	if (speed > 0)
	{
		rightFwd((byte)(abs(speed)));
	}
	else
	{
		rightRev((byte)(abs(speed)));
	}
}

void Motor::leftDrive(int speed)
{
	if (speed > 0)
	{
		leftFwd((byte)(abs(speed)));
	}
	else
	{
		leftRev((byte)(abs(speed)));
	}
}

void Motor::leftBrake()
{
	digitalWrite(L_CTRL_1, HIGH);
	digitalWrite(L_CTRL_2, HIGH);
	analogWrite(PWM_L, 0);
}

void Motor::rightBrake()
{
	digitalWrite(R_CTRL_1, HIGH);
	digitalWrite(R_CTRL_2, HIGH);
	analogWrite(PWM_R, 0);
}

void Motor::leftStop()
{
	digitalWrite(L_CTRL_1, LOW);
	digitalWrite(L_CTRL_2, LOW);
	analogWrite(PWM_L, 0);
}

void Motor::rightStop()
{
	digitalWrite(R_CTRL_1, LOW);
	digitalWrite(R_CTRL_2, LOW);
	analogWrite(PWM_R, 0);
}

/******************************************************************************
Private functions for Motor
******************************************************************************/

void Motor::leftFwd(byte spd)
{
	digitalWrite(L_CTRL_1, HIGH);
	digitalWrite(L_CTRL_2, LOW);
	analogWrite(PWM_L, spd);
	// If we have an encoder in the system, we want to make sure that it counts
	//  in the right direction when ticks occur.
	if (encoder != 0)
	{
		encoder->lDir = 1;
	}
}

void Motor::leftRev(byte spd)
{
	digitalWrite(L_CTRL_1, LOW);
	digitalWrite(L_CTRL_2, HIGH);
	analogWrite(PWM_L, spd);
	// If we have an encoder in the system, we want to make sure that it counts
	//  in the right direction when ticks occur.
	if (encoder != 0)
	{
	encoder->lDir = -1;
	}
}

void Motor::rightFwd(byte spd)
{
	digitalWrite(R_CTRL_1, HIGH);
	digitalWrite(R_CTRL_2, LOW);
	analogWrite(PWM_R, spd);
	// If we have an encoder in the system, we want to make sure that it counts
	//  in the right direction when ticks occur.
	if (encoder != 0)
	{
	encoder->rDir = 1;
	}
}

void Motor::rightRev(byte spd)
{
	digitalWrite(R_CTRL_1, LOW);
	digitalWrite(R_CTRL_2, HIGH);
	analogWrite(PWM_R, spd);
	// If we have an encoder in the system, we want to make sure that it counts
	//  in the right direction when ticks occur.
	if (encoder != 0)
	{
	encoder->rDir = -1;
	}
}
