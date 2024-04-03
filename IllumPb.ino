/*
 Name:		IllumPb.ino
 Created:	4/2/2024 2:53:18 PM
 Author:	johnd
*/
constexpr auto LEDSWPIN = 2;
int OnOffTimCntr = 0;
int OnOffPeriodCnt = 0;
unsigned long Timenow;


// the setup function runs once when you press reset or power the board
void setup() {
    pinMode(LEDSWPIN, OUTPUT);
    Timenow = millis();
}

// the loop function runs over and over again until power down or reset
void loop()
    {
    if ( millis() > Timenow )
        {
        OnOffTimCntr += 1; if ( OnOffTimCntr > 100 ) OnOffTimCntr = 0;
        OnOffPeriodCnt += 1; if ( OnOffPeriodCnt > 2000 ) OnOffPeriodCnt = 0;
        ShowLED();
        Timenow = millis();
        }    
}
void ShowLED()
    {
    if ( OnOffPeriodCnt < 1000 )
        { //ON
        if ( OnOffTimCntr < 1 ) digitalWrite(LEDSWPIN, 1);
        else digitalWrite(LEDSWPIN, 0);
        }
    else
        {  //OFF
        if ( OnOffTimCntr < 99 ) digitalWrite(LEDSWPIN, 1);
        else digitalWrite(LEDSWPIN, 0);
        }

    }