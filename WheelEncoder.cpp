#include "ElectricRay.h"

// Create a local pointer to an instance of this
// class, so we can edit the counts with other
// library functions.
WheelEncoder *encoder = 0; 

/******************************************************************************
Public functions for WheelEncoder
******************************************************************************/

WheelEncoder::WheelEncoder(int lPin, int rPin)
{
	pinMode(lPin, INPUT);
	pinMode(rPin, INPUT);
	// Enable pin change interrupts for the pins, 
	// and pin change interrupts for the group that pin is a part of.
	setPinChangeInterrupt(lPin, LENCODER);
	setPinChangeInterrupt(rPin, RENCODER);
	lCounts = 0;
	rCounts = 0;
	encoder = this;
}

void WheelEncoder::wheelTick(WHEEL wheel)
{
	switch(wheel)
	{
		case LEFT:
			lCounts += (long)lDir;
			break;
		case RIGHT:
			rCounts += (long)rDir;
			break;
		case BOTH:
		break;
	}
}

void WheelEncoder::clearEnc(WHEEL wheel)
{
	switch(wheel)
	{
		case LEFT:
			lCounts = 0;
			break;
		case RIGHT:
			rCounts = 0;
			break;
		case BOTH:
			lCounts = 0;
			rCounts = 0;
			break;
	}
}

long WheelEncoder::getTicks(WHEEL wheel)
{
	switch(wheel)
	{
		case LEFT:
			return lCounts;
		case RIGHT:
			return rCounts;
		case BOTH:
			return 0;
  }
  return 0;
}
