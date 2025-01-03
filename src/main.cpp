#include "wifi/wifi.h"
#include "webserver/webserver.h"
#include "led/led.h"
#include "valid.h"
bool isValid = false;
void setRoute()
{
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

  addHttpApi("/ad6ae84ce89ac046d242b7462c8912873056ffbb87ded9124a269351bbfaf575",
             [](ESP8266WebServer *server)
             {
               JsonDocument doc;
               JsonObject obj = doc.to<JsonObject>();
               obj["a4975c86441bcb8f2b99c2de0b9ba62c5977acda7c32f267854bac48b4526139"] = ESP.getSketchMD5();
               obj["2ca04afe5f763512bf7f9e11f27da7df5da0ba1f987d8ebb71daaeb6e1ec9936"] = ESP.getSketchSize();
               obj["0d520e852e9550510df3d48cbcb8421b5713715c1fbd5c26f0de786ba29c0723"] = WiFi.macAddress();
               String ret;
               serializeJson(obj, ret);
               server->send(200, "application/json", ret.c_str());
             });
  addHttpApi("/setToken",
             [](ESP8266WebServer *server)
             {
               String token = server->arg("token");
               writeToken(token);

               JsonDocument doc;
               JsonObject obj = doc.to<JsonObject>();
               if (valid())
                 obj["status"] = "ĐÃ KÍCH HOẠT";
               else
                 obj["status"] = "THẤT BẠI";

               String ret;
               serializeJson(obj, ret);
               server->send(200, "application/json", ret);
             });
  addHttpApi("/getToken",
             [](ESP8266WebServer *server)
             {
               JsonDocument doc;
               JsonObject obj = doc.to<JsonObject>();
               obj["token"] = getToken();
               obj["isValid"] = valid();
               obj["mac"] = WiFi.macAddress();
               String ret;
               serializeJson(obj, ret);
               server->send(200, "application/json", ret);
             });
}
void setup(void)
{
  LittleFS.begin();
  isValid = valid();
  pinMode(LED_BUILTIN, OUTPUT);
  for (size_t i = 0; i < 5; i++)
  {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(222);
    digitalWrite(LED_BUILTIN, LOW);
    delay(222);
  }

  pinMode(BUTTON_PIN, INPUT);
  if (digitalRead(BUTTON_PIN) == LOW)
  {
    setupWifi(isValid, false);
    setupWebserver();
    while (1)
    {
      loopWebserver();
    }
  }

  setupWifi(isValid, true);

#ifdef DEVELOPMENT
  if (true)
#else
  if (isValid)
#endif
  {
    // Nếu valid

    setupWebserver();
    preSetupLed();
    setupLed();
    setRoute();
  }
  else
  {

    setupWebserver();
    setRoute();

    while (1)
    {
      loopWebserver();
    }
  }
}

void loop(void)
{
  loopWebserver();
  loopLed();

#ifndef DEVELOPMENT
  if (millis() > 60000)
  {
    if (!isValid)
    {
      while (1)
      {
        loopWifi();
        loopWebserver();
      }
    }
  }
#endif
}