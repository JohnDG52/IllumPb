// LpSw.h

#ifndef _LPSW_h
#define _LPSW_h


#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#define OFF false
#define ON true

// THIS SECTION MUST BE SET UP BEFORE USE -------------------------------------------------

const int numLpSws= 1;  // Number of LP/Sw pairs used

// DIO lines used for each of the LED / pushbutton pairs
const int DIOLpSw1= 2;
const int DIOLpSw2= 4;
const int DIOLpSw3= 5;
//-----------------------------------------------------------------------------------------

// Operating modes
enum LpSwmode
    {
    modeIndep,   // LED and switch operate independently
    modeMom,     // Momentary pushbutton with indication
    modeLat       // Latching pushbutton with indication
    };

// Structure to contain data for each LP/Switch pair
struct stLpSw
    {
    unsigned char DIOPin;
    unsigned char mode;
    unsigned char count; // Used for Lp On/Off period counting
    union
        {
        uint8_t boFlags;
        struct
            {
            uint8_t LEDOn : 1, blocked : 1, logicalSwOn : 1, physicalSwOn : 1,
                boF5 : 1, boF6 : 1, boF7 : 1;
            };
        };

    };

class LpSw
    {
        public:
        LpSw(); // Constructor
        void addLpSw(uint8_t ID, uint8_t Pin, uint8_t LpSwMode);
        void scanLpSw();
        bool switchIsOn(uint8_t ID);
        void forceLp(uint8_t ID, bool state);



        private:
        boolean _readSw(stLpSw* Ptr,boolean leaveLEDon);
        unsigned long _lastTimems;
        stLpSw _LpSwArray[numLpSws];
        void _scanLpSw(uint8_t ID);

};


#endif

