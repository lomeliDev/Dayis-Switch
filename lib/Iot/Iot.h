#ifndef IOT_H
#define IOT_H

#include <Arduino.h>
#include "Globals.h"

void setupIoT();
void loopIoT();
void setPowerState(String id, bool status);

#endif