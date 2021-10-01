#include <Arduino.h>
#include <WiFi.h>
#include "SinricPro.h"
#include "SinricProSwitch.h"
#include "Iot.h"
#include "Globals.h"
#include "Write.h"
#include "Relays.h"

#ifdef ENABLE_DEBUG
#define DEBUG_ESP_PORT Serial
#define NODEBUG_WEBSOCKETS
#define NDEBUG
#endif

#include "SinricPro.h"
#include "SinricProSwitch.h"

void onPowerStateButtons(String deviceId, int id, bool state)
{
    if (debug)
    {
        Serial.printf("Device %s turned %s (via SinricPro) \r\n", deviceId.c_str(), state ? "on" : "off");
    }
    if (!state)
    {
        if (id == 1)
        {
            setRelay(0xA0);
        }
        else if (id == 2)
        {
            setRelay(0xB0);
        }
        else if (id == 3)
        {
            setRelay(0xC0);
        }
        else if (id == 4)
        {
            setRelay(0xD0);
        }
    }
    else
    {
        if (id == 1)
        {
            setRelay(0xA1);
        }
        else if (id == 2)
        {
            setRelay(0xB1);
        }
        else if (id == 3)
        {
            setRelay(0xC1);
        }
        else if (id == 4)
        {
            setRelay(0xD1);
        }
    }
}

bool onPowerStateButton_1(const String &deviceId, bool &state)
{
    onPowerStateButtons(deviceId, 1, state);
    return true;
}

bool onPowerStateButton_2(const String &deviceId, bool &state)
{
    onPowerStateButtons(deviceId, 2, state);
    return true;
}

bool onPowerStateButton_3(const String &deviceId, bool &state)
{
    onPowerStateButtons(deviceId, 3, state);
    return true;
}

bool onPowerStateButton_4(const String &deviceId, bool &state)
{
    onPowerStateButtons(deviceId, 4, state);
    return true;
}

void setupIoT()
{

    if (String(device_id_1) != String(""))
    {
        SinricProSwitch &IotButton_1 = SinricPro[device_id_1];
        IotButton_1.onPowerState(onPowerStateButton_1);
    }

    if (String(device_id_2) != String(""))
    {
        SinricProSwitch &IotButton_2 = SinricPro[device_id_2];
        IotButton_2.onPowerState(onPowerStateButton_2);
    }

    if (String(device_id_3) != String(""))
    {
        SinricProSwitch &IotButton_3 = SinricPro[device_id_3];
        IotButton_3.onPowerState(onPowerStateButton_3);
    }

    if (String(device_id_4) != String(""))
    {
        SinricProSwitch &IotButton_4 = SinricPro[device_id_4];
        IotButton_4.onPowerState(onPowerStateButton_4);
    }

    if (String(app_key) != "" && String(app_secret) != "")
    {
        SinricPro.onConnected([]()
                              { Serial.printf("Connected to SinricPro\r\n"); });
        SinricPro.onDisconnected([]()
                                 { Serial.printf("Disconnected from SinricPro\r\n"); });
        SinricPro.begin(app_key, String(app_secret));
        SinricPro.restoreDeviceStates(true);
    }
}

void loopIoT()
{
    SinricPro.handle();
}

void setPowerState(String id, bool status)
{
    if (id != "")
    {
        SinricProSwitch &IotButton = SinricPro[id];
        IotButton.sendPowerStateEvent(status);
    }
}