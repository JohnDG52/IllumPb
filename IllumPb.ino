/*
 Name:		IllumPb.ino
 Created:	4/2/2024 2:53:18 PM
 Author:	johnd
*/
constexpr auto LEDSWPIN = 2;
int OnOffTimCntr = 0;
int OnOffPeriodCnt = 0;
unsigned long Timenowms;
boolean PbPressed, PbWasPressed;

// the setup function runs once when you press reset or power the board
void setup() {
    pinMode(LEDSWPIN, OUTPUT);
    Timenowms = millis();
    Serial.begin(9600);
}

void readPb()
    {
    pinMode(LEDSWPIN, INPUT);
    delayMicroseconds(1);
    if ( digitalRead(LEDSWPIN) == 1 ) PbPressed = true; else PbPressed = false;
    pinMode(LEDSWPIN, OUTPUT);
    }

void checkChange()
    {
    if ( PbPressed && !PbWasPressed ) Serial.println("PRESSED");

    if ( !PbPressed && PbWasPressed ) Serial.println("NOT PRESSED");

    PbWasPressed = PbPressed;
    }

// the loop function runs over and over again until power down or reset
void loop()
    {
    if ( millis() > Timenowms )
        {
        OnOffTimCntr += 1; if ( OnOffTimCntr > 100 ) OnOffTimCntr = 0;
        OnOffPeriodCnt += 1; if ( OnOffPeriodCnt > 4000 ) OnOffPeriodCnt = 0;
        checkChange();
        ShowLED();
        Timenowms = millis();
        }    
}
void ShowLED()
    {
    if ( OnOffPeriodCnt < 2000 )
        { //Off
        if ( OnOffTimCntr < 1 )
            {
            digitalWrite(LEDSWPIN, 1);
            delayMicroseconds(50);
            readPb();
            digitalWrite(LEDSWPIN, 0);
            }
        else digitalWrite(LEDSWPIN, 0);
        }
    else
        {  //On
        if ( OnOffTimCntr < 100 ) digitalWrite(LEDSWPIN, 1);
        else
            {
            readPb();
            digitalWrite(LEDSWPIN, 0);
            }
        }

    }
