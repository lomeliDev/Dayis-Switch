#include <Arduino.h>
#include <FS.h>
#include "SPIFFS.h"
#include "Esp.h"
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <ESPAsyncWebServer.h>
#include <ESPAsyncWiFiManager.h>
#include <DNSServer.h>
#include "Globals.h"
#include "Network.h"
#include "File.h"
#include "Write.h"

AsyncWebServer server(80);
DNSServer dns;
AsyncWiFiManager wifiManager(&server, &dns);

void saveConfigCallback()
{
    logS("Should save config");
    shouldSaveConfig = true;
}

void setupWifi()
{
    wifiReady = 0;
    shouldSaveConfig = false;
    pinMode(ledWifi, OUTPUT);
    digitalWrite(ledWifi, LOW);
    readJson();

    String mySSID = String(ssid);

    logS(ssid);
    logS(pass);
    logS(app_key);
    logS(app_secret);
    logS(device_id_1);
    logS(device_id_2);
    logS(device_id_3);
    logS(device_id_4);
    logS(bluetooth);
    logS(pin_bluetooth);

    if (mySSID != "")
    {
        delay(3000);
        Serial.printf("\r\n[Wifi]: Connecting");
        WiFi.begin(ssid, pass);

        while (WiFi.status() != WL_CONNECTED)
        {
            Serial.printf(".");
            delay(250);
        }

        digitalWrite(ledWifi, HIGH);
        Serial.printf("connected!\r\n[WiFi]: IP-Address is %s\r\n", WiFi.localIP().toString().c_str());
        wifiReady = 1;
    }
    else
    {
        AsyncWiFiManagerParameter custom_app_key("app_key", "app_key", app_key, 64);
        AsyncWiFiManagerParameter custom_app_secret("app_secret", "app_secret", app_secret, 80);
        AsyncWiFiManagerParameter custom_device_id_1("device_id_1", "device_id_1", device_id_1, 64);
        AsyncWiFiManagerParameter custom_device_id_2("device_id_2", "device_id_2", device_id_2, 64);
        AsyncWiFiManagerParameter custom_device_id_3("device_id_3", "device_id_3", device_id_3, 64);
        AsyncWiFiManagerParameter custom_device_id_4("device_id_4", "device_id_4", device_id_4, 64);
        AsyncWiFiManagerParameter custom_bluetooth("bluetooth", "bluetooth", bluetooth, 64);
        AsyncWiFiManagerParameter custom_pin_bluetooth("pin_bluetooth", "pin_bluetooth", pin_bluetooth, 8);

        wifiManager.setSaveConfigCallback(saveConfigCallback);

        wifiManager.setAPStaticIPConfig(IPAddress(10, 0, 1, 1), IPAddress(10, 0, 1, 1), IPAddress(255, 255, 255, 0));

        wifiManager.addParameter(&custom_app_key);
        wifiManager.addParameter(&custom_app_secret);
        wifiManager.addParameter(&custom_device_id_1);
        wifiManager.addParameter(&custom_device_id_2);
        wifiManager.addParameter(&custom_device_id_3);
        wifiManager.addParameter(&custom_device_id_4);
        wifiManager.addParameter(&custom_bluetooth);
        wifiManager.addParameter(&custom_pin_bluetooth);

        if (!wifiManager.autoConnect("Dayis-Electronics", "password"))
        {
            logS("failed to connect and hit timeout");
            delay(3000);
            ESP.restart();
            delay(5000);
        }

        logS("connected Wifi :)");

        strcpy(ssid, String(WiFi.SSID()).c_str());
        strcpy(pass, String(WiFi.psk()).c_str());
        strcpy(app_key, custom_app_key.getValue());
        strcpy(app_secret, custom_app_secret.getValue());
        strcpy(device_id_1, custom_device_id_1.getValue());
        strcpy(device_id_2, custom_device_id_2.getValue());
        strcpy(device_id_3, custom_device_id_3.getValue());
        strcpy(device_id_4, custom_device_id_4.getValue());
        strcpy(bluetooth, custom_bluetooth.getValue());
        strcpy(pin_bluetooth, custom_pin_bluetooth.getValue());

        if (shouldSaveConfig)
        {
            writeJson();
            readJson();
            delay(5000);
            ESP.restart();
        }

        digitalWrite(ledWifi, HIGH);
        Serial.printf("connected!\r\n[WiFi]: IP-Address is %s\r\n", WiFi.localIP().toString().c_str());
        wifiReady = 1;
    }
}

void resetNetwork()
{
    resetJson();
    delay(3000);
    logS("Restart esp32");
    WiFi.disconnect(true);
    WiFi.disconnect(true, true);
    WiFi.begin("0", "0");
    wifiManager.resetSettings();
    delay(3000);
    ESP.restart();
    delay(5000);
}