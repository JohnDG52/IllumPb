/*
 Name:		IllumPb.ino
 Created:	4/2/2024 2:53:18 PM
 Author:	John D Glover
*/

#include "LpSw.h"

LpSw lpsw;
#include "LpSwTestStuff.h"

// the setup function runs once when you press reset or power the board
void setup()
    {
    tstSetup();
    }


// the loop function runs over and over again until power down or reset
void loop()
    {
// This section used blue LED to show the state of sw1 ------------------------------------------------------
   if ( tstcheckInterval(10))
       {
    if ( lpsw.switchIsOn(1) )
            {
            tstSweepup();
            }
    else
        tstSweepdown();
    }
// ----------------------------------------------------------------------------------------------------------
       // If sw0 is pressed, the indicator of the lp/sw 0 pair is switched off
   if ( lpsw.switchIsOn(0) ) { lpsw.forceLp(0, OFF); }
    // If sw2 is pressed, the indicator of the lp/sw 0 pair is switched on
   if ( lpsw.switchIsOn(2) ) { lpsw.forceLp(0, ON); }
   // ----------------------------------------------------------------------------------------------------------
   lpsw.scanLpSw();

}

