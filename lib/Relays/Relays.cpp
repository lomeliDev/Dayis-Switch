#include <Arduino.h>
#include "Relays.h"
#include "Globals.h"
#include "Write.h"
#include "Iot.h"

void setupRelays()
{
    pinMode(relay_1, OUTPUT);
    pinMode(relay_2, OUTPUT);
    pinMode(relay_3, OUTPUT);
    pinMode(relay_4, OUTPUT);
    digitalWrite(relay_1, HIGH);
    digitalWrite(relay_2, HIGH);
    digitalWrite(relay_3, HIGH);
    digitalWrite(relay_4, HIGH);
}

void setRelay(byte _byte)
{
    if (_byte == 0xA0)
    {
        write(0xAA);
        digitalWrite(relay_1, HIGH);
        status_relay_1 = false;
        setPowerState(device_id_1, false);
    }
    else if (_byte == 0xA1)
    {
        write(0xAA);
        digitalWrite(relay_1, LOW);
        status_relay_1 = true;
        setPowerState(device_id_1, true);
    }
    else if (_byte == 0xB0)
    {
        write(0xBB);
        digitalWrite(relay_2, HIGH);
        status_relay_2 = false;
        setPowerState(device_id_2, false);
    }
    else if (_byte == 0xB1)
    {
        write(0xBB);
        digitalWrite(relay_2, LOW);
        status_relay_2 = true;
        setPowerState(device_id_2, true);
    }
    else if (_byte == 0xC0)
    {
        write(0xCC);
        digitalWrite(relay_3, HIGH);
        status_relay_3 = false;
        setPowerState(device_id_3, false);
    }
    else if (_byte == 0xC1)
    {
        write(0xCC);
        digitalWrite(relay_3, LOW);
        status_relay_3 = true;
        setPowerState(device_id_3, true);
    }
    else if (_byte == 0xD0)
    {
        write(0xDD);
        digitalWrite(relay_4, HIGH);
        status_relay_4 = false;
        setPowerState(device_id_4, false);
    }
    else if (_byte == 0xD1)
    {
        write(0xDD);
        digitalWrite(relay_4, LOW);
        status_relay_4 = true;
        setPowerState(device_id_4, true);
    }
}