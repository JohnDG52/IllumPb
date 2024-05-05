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
    lpsw.addLpSw(0, DIOLpSw1, modeLat);
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



const int ID = 0; // Set to ID number of independent Lp/Sw pair

void tstIndeLEDJob()
    {
    static unsigned long lastTime = 0;
    static int counter = 0;

    if ( millis() > lastTime )
        {
        lastTime = millis();
        counter++;
        if ( counter < 1500 )
            {
            lpsw.forceLp(ID, OFF);
            }
        else
            {
            lpsw.forceLp(ID, ON);
            }
        if ( counter > 2500 ) counter = 0;
        }
    }
#endif

