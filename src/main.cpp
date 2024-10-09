#include "wifi/wifi.h"
#include "webserver/webserver.h"
#include "led/led.h"
void setup(void)
{
  preSetupLed();
  setupWifi();
  setupWebserver();
  setupLed();

  addHttpApi("/format",
             [](ESP8266WebServer *server)
             {
               LittleFS.begin();
               LittleFS.format();
               server->send(200, "application/json", "ok");
             });

  addHttpApi("/reset",
             [](ESP8266WebServer *server)
             {
               server->send(200, "application/json", "ok");
               ESP.restart();
             });
  addHttpApi("/readFile",
             [](ESP8266WebServer *server)
             {
               String path = server->arg("value");

               File file = LittleFS.open(path, "r");
               if (!file)
               {
                 server->send(200, "text", "faile");
                 return;
               }
               server->send(200, "text", file.readString());
               file.close();
             });
}

void loop(void)
{
  loopWifi();
  loopWebserver();
  loopLed();
}