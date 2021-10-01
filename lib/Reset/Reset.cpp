#include <Arduino.h>
#include "Globals.h"
#include "Reset.h"
#include "Network.h"
#include "write.h"

void setupReset()
{
    pinMode(pinReset, INPUT_PULLUP);
}

void Reset()
{
    resetNetwork();
}

void loopReset()
{
    if (digitalRead(pinReset) == LOW)
    {
        logS("Reset start");
        LASTRESET = millis();
        int x = 0;
        while (x == 0)
        {
            if (digitalRead(pinReset) == LOW)
            {
                logS("Reset...");
                delay(500);
            }
            else
            {
                logS("Reset finish");
                x = 1;
            }
        }
        if ((millis() - LASTRESET) >= timeReset)
        {
            logS("Reset initial...");
            Reset();
        }
        LASTRESET = 0;
    }
}
