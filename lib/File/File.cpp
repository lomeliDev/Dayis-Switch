#include <Arduino.h>
#include <FS.h>
#include "SPIFFS.h"
#include <ArduinoJson.h>
#include "Globals.h"
#include "Write.h"
#include "File.h"

void readJson()
{
    jsonReady = false;

    if (SPIFFS.begin())
    {
        if (SPIFFS.exists("/wifi.json"))
        {
            File configFile = SPIFFS.open("/wifi.json", "r");
            if (configFile)
            {
                size_t size = configFile.size();
                std::unique_ptr<char[]> buf(new char[size]);
                configFile.readBytes(buf.get(), size);
                String myJson = buf.get();
                String jsonRead = "";

                if (myJson.indexOf("{") >= 0 && myJson.indexOf("}") >= 0)
                {
                    int n = myJson.length();
                    char jsonCH[n + 1];
                    strcpy(jsonCH, myJson.c_str());
                    for (int i = 0; i < n; i++)
                    {
                        jsonRead += String(myJson[i]);
                        if (myJson[i] == '}')
                        {
                            break;
                        }
                    }
                }
                else
                {
                    logS(F("no JSON "));
                    return;
                }

                StaticJsonDocument<1024> doc;
                DeserializationError error = deserializeJson(doc, jsonRead);
                if (error)
                {
                    logS(F("deserializeJson() failed: "));
                    return;
                }

                strcpy(ssid, doc["ssid"]);
                strcpy(pass, doc["pass"]);
                strcpy(app_key, doc["app_key"]);
                strcpy(app_secret, doc["app_secret"]);
                strcpy(device_id_1, doc["device_id_1"]);
                strcpy(device_id_2, doc["device_id_2"]);
                strcpy(device_id_3, doc["device_id_3"]);
                strcpy(device_id_4, doc["device_id_4"]);
                strcpy(bluetooth, doc["bluetooth"]);
                strcpy(pin_bluetooth, doc["pin_bluetooth"]);

                nameBluetooth = bluetooth;
                pinBluetooth = doc["pin_bluetooth"];

                jsonReady = true;
            }
            else
            {
                logS("failed to load json config");
            }
            configFile.close();
        }
        else
        {
            logS("failed json config not exists");
        }
    }
    else
    {
        logS("failed to mount FS");
    }
}

void writeJson()
{
    logS("");
    logS("writeJson...");
    jsonReady = false;
    DynamicJsonDocument json(1024);
    json["ssid"] = ssid;
    json["pass"] = pass;
    json["app_key"] = app_key;
    json["app_secret"] = app_secret;
    json["device_id_1"] = device_id_1;
    json["device_id_2"] = device_id_2;
    json["device_id_3"] = device_id_3;
    json["device_id_4"] = device_id_4;
    json["bluetooth"] = bluetooth;
    json["pin_bluetooth"] = pin_bluetooth;

    File configFile = SPIFFS.open("/wifi.json", "w");
    if (!configFile)
    {
        logS("failed to open config file for writing");
    }
    else
    {
        serializeJsonPretty(json, Serial);
        serializeJson(json, configFile);
        shouldSaveConfig = false;
        jsonReady = true;
    }
    configFile.close();
}

void resetJson()
{
    logS("");
    logS("resetJson...");
    jsonReady = false;
    DynamicJsonDocument json(1024);
    json["ssid"] = "";
    json["pass"] = "";
    json["app_key"] = "";
    json["app_secret"] = "";
    json["device_id_1"] = "";
    json["device_id_2"] = "";
    json["device_id_3"] = "";
    json["device_id_4"] = "";
    json["bluetooth"] = "";
    json["pin_bluetooth"] = "";

    File configFile = SPIFFS.open("/wifi.json", "w");
    if (!configFile)
    {
        logS("failed to open config file for writing");
    }
    else
    {
        serializeJsonPretty(json, Serial);
        serializeJson(json, configFile);
        shouldSaveConfig = false;
        jsonReady = true;
    }
    configFile.close();
}

