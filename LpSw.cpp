

#include "LpSw.h"

// Constructor
LpSw::LpSw()
    {
    }

// Add an Lp/switch pair to the array
void LpSw::addLpSw(uint8_t ID, uint8_t Pin, uint8_t LpSwMode)
    {
    stLpSw* P = &_LpSwArray[ID]; // P points to the appropriate structure in the array
    // Note that for a single Lp/Sw pair, the numLpSws is 1, but its ID is the array
    //index, 0
    P->DIOPin = Pin;
    P->mode = LpSwMode;
    P->boFlags = 0; // This clears all the boolean flags (sets them false) so we start
    //with a known state
    _lastTimems = 0;
    }

// Scan all the LEDs and switches (if it's time to scan)
void LpSw::scanLpSw()
    {
    if ( millis() <= _lastTimems ) return;
    _lastTimems = millis();
    for ( auto i = 0; i < numLpSws; i++ ) { LpSw::_scanLpSw(i); }
    }

// Scan one Lp/Sw pair
void LpSw::_scanLpSw(uint8_t ID)
    {
    stLpSw* P = &_LpSwArray[ID]; // P points to the appropriate structure in the array
    switch ( P->mode )
        {
            case modeIndep: // LED and switch are independent
                if ( !P->LEDOn )
                    {
                    if ( P->count == 1 ) { P->physicalSwOn = _readSw(P,false); }
                    }
                else
                    {
                    if ( P->count == 100 ) { P->physicalSwOn = _readSw(P,true); P->count = 0; }
                    }
                P->logicalSwOn = P->physicalSwOn;
                P->count++;
                break;
            case modeMom: // Momentary pushbutton with indicator
                if ( !P->LEDOn )
                    {
                    if ( P->count == 1 )
                        {
                        P->physicalSwOn = _readSw(P,OFF);
                        P->LEDOn = P->physicalSwOn;
                        }
                    }
                else
                    {
                    if ( P->count == 100 )
                        { 
                        P->physicalSwOn = _readSw(P,ON); P->count = 0;
                        P->LEDOn = P->physicalSwOn;
                        }
                    }
                P->logicalSwOn = P->physicalSwOn;
                P->count++;               
                break;
            case modeLat: //Latching pushbutton with indicator
                if ( !P->LEDOn )
                    {
                    if ( P->count == 1 ) { P->physicalSwOn = _readSw(P,OFF); }
                    if ( P->physicalSwOn )
                        {
                        if ( !P->blocked )
                            {
                            P->logicalSwOn = !P->logicalSwOn;
                            P->blocked = true;
                            }
                        }
                    else
                        {
                        P->blocked = false;
                        }
                    }
                else
                    {
                    if ( P->count == 100 ) { P->physicalSwOn = _readSw(P,ON); P->count = 0; }
                    if ( P->physicalSwOn )
                        {
                        if ( !P->blocked )
                            {
                            P->logicalSwOn = !P->logicalSwOn;
                            P->blocked = true;
                            }
                        }
                    else
                        {
                        P->blocked = false;
                        }
                    }
                P->LEDOn = P->logicalSwOn;
                P->count++;
                break;
        }
    }

boolean LpSw::_readSw(stLpSw* Ptr,boolean leaveLEDon)
    {
    boolean r;
    digitalWrite(Ptr->DIOPin, 1);
    pinMode(Ptr->DIOPin, OUTPUT);
    pinMode(Ptr->DIOPin, INPUT);
    r = (digitalRead(Ptr->DIOPin)==1);
    digitalWrite(Ptr->DIOPin, leaveLEDon);
    pinMode(Ptr->DIOPin, OUTPUT);
    return(r);
    }

bool LpSw::switchIsOn(uint8_t ID)
    {
    return _LpSwArray[ID].logicalSwOn;
    }

void LpSw::forceLp(uint8_t ID, bool state) 
    {
    if ( _LpSwArray[ID].mode == modeIndep ) { _LpSwArray[ID].LEDOn = state; } // Only works if in independent mode
    }


