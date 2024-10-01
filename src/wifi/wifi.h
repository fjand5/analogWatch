#pragma once
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include "../env.h"
#include "../webserver/webserver.h"
#include "LittleFS.h"


// void scanWifi();
// void setWifi();
// void getWifi();

void setupWifi(void);

void loopWifi(void);
