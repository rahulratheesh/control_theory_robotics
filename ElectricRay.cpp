#include "ElectricRay.h"
#include <avr/interrupt.h>
#include <Arduino.h>

// To track what the prior state of our pins for various PCINTS
// This varies by interrupt. These values are initialized to the "all high"
// No low-to-high transitions at beginning of code execution are to be caught.
// For pins A0-A5/14-19, PC0-5
volatile byte lastPC1PinState = 0x3F;  

// We need some way to exclude short transients on the encoder inputs
// we'll do that by capturing the most recent rise time with millis() and ignoring
// falling edges that happen within 20ms of a rise.
volatile unsigned long lastRRise = 0;
volatile unsigned long lastLRise = 0;
#define  ENC_HIGH_DELAY   10

byte PCMask = 0;

// Store the currently assigned fucntion
// of the PCINT associated with each pin
// in this array. Array indices are of
//  the type "PCINT_pinname".
volatile byte pinFunction[6];     

extern WheelEncoder *encoder;

// set pin change interrupts for A2, A3
void setPinChangeInterrupt(int pin, byte role)
{
  switch(pin)
  {
    // PCINT 10: PCMSK1, bit 2, PC2
    case A2:
      // Enable the pin change interrupt for this pin.  
      PCMSK1 |= 0x04;  
      // Enable pin change interrupts for this group.
      PCICR |= 0x02;   
      // Set the role for this pin (LENCODER) 
      pinFunction[PCINT_A2] = role; 
      // Add this pin to our mask bits for Port C.
      PCMask |= 0x04;  
      break;
    // PCINT 11: PCMSK1, bit 3, PC3
    case A3: 
      // Enable the pin change interrupt for this pin.   
      PCMSK1 |= 0x08; 
      // Enable pin change interrupts for this group. 
      PCICR |= 0x02;
      // Set the role for this pin (RENCODER)   
      pinFunction[PCINT_A3] = role;
      // Add this pin to our mask bits for Port C.
      PCMask |= 0x08;  
      break;
  }
}

// Interrupt Service routine for C port which has analog pins
ISR(PCINT1_vect)
{
	// check for a low-to-high transition by masking out the pins on Port C   
	// Capture the state of the pins-of-interest now before they have a chance to change.
	byte PCTemp = PINC & PCMask;  
                       
	PC1Handler(PCTemp);
}

void PC1Handler(byte PCTemp)
{
  // We have to figure out what changed, and if the change was a
  // high-to-low or a low-to-high transition. All these if() statements check
  // for a high-to-low transition; we want to ignore the low-to-highs.

  // Was it pin A2/16, AKA PC2?
  if ((lastPC1PinState & 0x04) && !(PCTemp & 0x04))
  {
    pinFunctionHandler(PCINT_A2);
  }
  else if (!(lastPC1PinState & 0x04) && (PCTemp & 0x04))
  {
    if (pinFunction[PCINT_A2] == LENCODER) lastLRise = millis();
    if (pinFunction[PCINT_A2] == RENCODER) lastRRise = millis();
  }
  // Was it pin A3/17, AKA PC3?
  if ((lastPC1PinState & 0x08) && !(PCTemp & 0x08))
  {
    pinFunctionHandler(PCINT_A3);
  }
  else if (!(lastPC1PinState & 0x08) && (PCTemp & 0x08))
  {
    if (pinFunction[PCINT_A3] == LENCODER) lastLRise = millis();
    if (pinFunction[PCINT_A3] == RENCODER) lastRRise = millis();
  }

  lastPC1PinState = PCTemp;
}

void pinFunctionHandler(byte pinIndex)
{
	switch(pinFunction[pinIndex])
	{
		case LENCODER:
			if (lastLRise + ENC_HIGH_DELAY < millis()) encoder->wheelTick(LEFT);
			break;
		case RENCODER:
			if (lastRRise + ENC_HIGH_DELAY < millis()) encoder->wheelTick(RIGHT);
			break;
		case WHISKER:
		case SW_SERIAL:
		case NOT_IN_USE:
			break;
	}
}
