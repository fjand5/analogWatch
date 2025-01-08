#include "Arduino.h"
#include "ArduinoJson.h"
#include "LittleFS.h"
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <CustomJWT.h>
void writeToken(String token);
String getToken();
bool valid();
void validProcess();
