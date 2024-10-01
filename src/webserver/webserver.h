#pragma once
#include "../dist.h"
#include "../env.h"
#include <ESP8266WebServer.h>
#include <ESP8266HTTPUpdateServer.h>

#include <ArduinoJson.h>
typedef void (Response)(ESP8266WebServer *server);
void addHttpApi(String url, Response response);

void handleIndex();
void setupWebserver();
void loopWebserver();