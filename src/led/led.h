#include "../env.h"
#include "../webserver/webserver.h"
#include "secondHand.h"
#include "minuteHand.h"
#include "hourHand.h"
#include <WiFiUdp.h>
#include <NTPClient.h>
#include <ArduinoJson.h>
#include <FastLED.h>
#include "LittleFS.h"
#include "RTClib.h"

void preSetupLed();
void setupLed();
void loopLed();
