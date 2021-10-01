#include <Arduino.h>
#include "Buttons.h"
#include "Globals.h"
#include "Write.h"
#include "Relays.h"

void setupButtons()
{
    pinMode(button_1, INPUT_PULLUP);
    pinMode(button_2, INPUT_PULLUP);
    pinMode(button_3, INPUT_PULLUP);
    pinMode(button_4, INPUT_PULLUP);
}

void loopButtons()
{
    //Button 1
    if (digitalRead(button_1) == LOW && status_relay_1 == false && status_button_1 == false)
    {
        status_button_1 = true;
        setRelay(0xA1);
    }
    else if (digitalRead(button_1) == LOW && status_relay_1 == true && status_button_1 == false)
    {
        status_button_1 = true;
    }
    else if (digitalRead(button_1) == HIGH && status_relay_1 == true && status_button_1 == true)
    {
        status_button_1 = false;
        setRelay(0xA0);
    }

    //Button 2
    if (digitalRead(button_2) == LOW && status_relay_2 == false && status_button_2 == false)
    {
        status_button_2 = true;
        setRelay(0xB1);
    }
    else if (digitalRead(button_2) == LOW && status_relay_2 == true && status_button_2 == false)
    {
        status_button_2 = true;
    }
    else if (digitalRead(button_2) == HIGH && status_relay_2 == true && status_button_2 == true)
    {
        status_button_2 = false;
        setRelay(0xB0);
    }

    //Button 3
    if (digitalRead(button_3) == LOW && status_relay_3 == false && status_button_3 == false)
    {
        status_button_3 = true;
        setRelay(0xC1);
    }
    else if (digitalRead(button_3) == LOW && status_relay_3 == true && status_button_3 == false)
    {
        status_button_3 = true;
    }
    else if (digitalRead(button_3) == HIGH && status_relay_3 == true && status_button_3 == true)
    {
        status_button_3 = false;
        setRelay(0xC0);
    }

    //Button 4
    if (digitalRead(button_4) == LOW && status_relay_4 == false && status_button_4 == false)
    {
        status_button_4 = true;
        setRelay(0xD1);
    }
    else if (digitalRead(button_4) == LOW && status_relay_4 == true && status_button_4 == false)
    {
        status_button_4 = true;
    }
    else if (digitalRead(button_4) == HIGH && status_relay_4 == true && status_button_4 == true)
    {
        status_button_4 = false;
        setRelay(0xD0);
    }
}