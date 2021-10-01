#include <Arduino.h>
#include "Globals.h"

/*Serial*/
bool debug = true;

/*Wifi*/
int ledWifi = 2;
bool shouldSaveConfig = false;
bool jsonReady = false;
int wifiReady = 0;
char ssid[32] = "";
char pass[32] = "";
char app_key[64] = "";
char app_secret[80] = "";
char device_id_1[64] = "";
char device_id_2[64] = "";
char device_id_3[64] = "";
char device_id_4[64] = "";
char bluetooth[64] = "";
char pin_bluetooth[8] = "";

/*BLUETOOTH*/
std::string nameBluetooth = "Dayis";
uint32_t pinBluetooth = 999999;
int delayBluetooth = 30;

/*Relays*/
int relay_1 = 16;
int relay_2 = 17;
int relay_3 = 5;
int relay_4 = 18;
bool status_relay_1 = false;
bool status_relay_2 = false;
bool status_relay_3 = false;
bool status_relay_4 = false;

/*Buttons*/
int button_1 = 12;
int button_2 = 14;
int button_3 = 27;
int button_4 = 26;
bool status_button_1 = false;
bool status_button_2 = false;
bool status_button_3 = false;
bool status_button_4 = false;

/*Reset*/
int pinReset = 13;
unsigned long LASTRESET = 0;
const int timeReset = 5000;