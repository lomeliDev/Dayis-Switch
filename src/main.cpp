#include <Arduino.h>
#include "Bluetooth.h"
#include "Relays.h"
#include "Buttons.h"
#include "Network.h"
#include "Reset.h"
#include "Iot.h"

void setup()
{
  Serial.begin(38400);
  setupWifi();
  setupRelays();
  setupButtons();
  setupReset();
  setupBluetooth();
  setupIoT();
}

void loop()
{
  loopReadBluetooth();
  loopButtons();
  loopReset();
  loopIoT();
  delay(10);
}