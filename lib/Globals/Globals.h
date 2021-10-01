#ifndef GLOBALS_H
#define GLOBALS_H

#include <Arduino.h>

/*Serial*/
extern bool debug;

/*Wifi*/
extern int ledWifi;
extern bool shouldSaveConfig;
extern bool jsonReady;
extern int wifiReady;
extern char ssid[32];
extern char pass[32];
extern char app_key[64];
extern char app_secret[80];
extern char device_id_1[64];
extern char device_id_2[64];
extern char device_id_3[64];
extern char device_id_4[64];
extern char bluetooth[64];
extern char pin_bluetooth[8];

/*BLUETOOTH*/
extern std::string nameBluetooth;
extern uint32_t pinBluetooth;
extern int delayBluetooth;

/*Relays*/
extern int relay_1;
extern int relay_2;
extern int relay_3;
extern int relay_4;
extern bool status_relay_1;
extern bool status_relay_2;
extern bool status_relay_3;
extern bool status_relay_4;

/*Buttons*/
extern int button_1;
extern int button_2;
extern int button_3;
extern int button_4;
extern bool status_button_1;
extern bool status_button_2;
extern bool status_button_3;
extern bool status_button_4;

/*Reset*/
extern int pinReset;
extern unsigned long LASTRESET;
extern const int timeReset;

#endif