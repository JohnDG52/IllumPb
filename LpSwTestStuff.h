// LpSwTestStuff.h

#ifndef _LpSwTestStuff_h
#define _LpSwTestStuff_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "LpSw.h"

unsigned long lastMillis = 0;

auto tstLEDPin = 3;
int tstOpmin = 0;
int tstOpmax = 150;
int tstOp = tstOpmin;
int tstOpinc = 1;

void tstSetup()
    {
    analogWrite(tstLEDPin, tstOpmin);
    pinMode(tstLEDPin, OUTPUT);
    lpsw.addLpSw(0, DIOLpSw1, modeIndep);
    lpsw.addLpSw(1, DIOLpSw2, modeLat);
    lpsw.addLpSw(2, DIOLpSw3, modeMom);
    lpsw.forceLp(0, ON);
    }

void tstSweepup()
    {
    if ( (tstOp < tstOpmax) )
        {
        tstOp += tstOpinc;
        analogWrite(tstLEDPin, tstOp);
        }
    }

void tstSweepdown()
    {
    if ( (tstOp > tstOpmin) )
        {
        tstOp -= tstOpinc;
        analogWrite(tstLEDPin, tstOp);
        }
    }

boolean tstcheckInterval(int ms) // Returns true every ms milliseconds
    {
    boolean rval = false;
    if ( (millis() - lastMillis) >= ms )
        {
        lastMillis = millis();
        rval = true;
        }
    return rval;
    }

#endif



