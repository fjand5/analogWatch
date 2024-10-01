#include "wifi/wifi.h"
#include "webserver/webserver.h"
#include "led/led.h"
void setup(void)
{

  setupWifi();
  setupWebserver();
  setupLed();
}

void loop(void)
{
  loopWifi();
  loopWebserver();
  loopLed();
}