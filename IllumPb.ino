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
    // This section used blue LED to show the state of the switch currently being tested -----------------------
   if ( tstcheckInterval(10))
       {
    if ( lpsw.switchIsOn(0) )
            {
            tstSweepup();
            }
    else
        tstSweepdown();
    }
   // ----------------------------------------------------------------------------------------------------------
   //tstIndeLEDJob(); // Only for independent mode
   lpsw.scanLpSw();

}

