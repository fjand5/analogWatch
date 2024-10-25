#include "led.h"

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "europe.pool.ntp.org", 7 * 3600);

CRGB leds[LED_COUNT];
uint16_t numLeds = LED_COUNT;

CRGB secondHandColor = CRGB::Red;
CRGB minuteHandColor = CRGB::Green;
CRGB hourHandColor = CRGB::Blue;
uint8_t brightness = 255;
uint8_t currentBrightness = 0;
bool power = true;
bool autoSyncTime = true;

TwoWire I2Cone;
RTC_DS1307 ds1307Time;

RTC_Millis espTime;
CRGB hexToRGB(String hex)
{
  hex.toLowerCase();
  uint8_t r, g, b;
  // Remove leading "#" symbol (if present)
  hex.trim();
  hex.replace("#", "");

  // Check for valid hex code length (6 characters)
  if (hex.length() != 6)
  {
    return CRGB::Black;
  }

  // Convert each hex pair to decimal (base 16) and split into RGB values
  sscanf(hex.c_str(), "%2hhx%2hhx%2hhx", &r, &g, &b);
  return CRGB(r, g, b);
}

String rgbToHex(CRGB color)
{

  char hex[8];
  hex[7] = 0;
  sprintf(hex, "#%02X%02X%02X", color.r, color.g, color.b);
  String ret = String(hex);
  ret.toLowerCase();
  return ret;
}
void updateLed()
{

  LittleFS.begin();

  File setupLedFile;
  setupLedFile = LittleFS.open("/setupLed.json", "w");
  JsonDocument doc;
  JsonObject setupLedJson = doc.to<JsonObject>();
  setupLedJson["secondHandColor"] = rgbToHex(secondHandColor);
  setupLedJson["minuteHandColor"] = rgbToHex(minuteHandColor);
  setupLedJson["hourHandColor"] = rgbToHex(hourHandColor);
  setupLedJson["brightness"] = brightness;
  setupLedJson["autoSyncTime"] = autoSyncTime;
  serializeJson(doc, setupLedFile);
  setupLedFile.close();
}
String getLed()
{
  JsonDocument doc;
  JsonObject setupLedJson = doc.to<JsonObject>();
  setupLedJson["secondHandColor"] = rgbToHex(secondHandColor);
  setupLedJson["minuteHandColor"] = rgbToHex(minuteHandColor);
  setupLedJson["hourHandColor"] = rgbToHex(hourHandColor);
  setupLedJson["brightness"] = brightness;
  setupLedJson["power"] = power;
  setupLedJson["timeStamp"] = espTime.now().unixtime();
  setupLedJson["autoSyncTime"] = autoSyncTime;
  String ret;
  serializeJson(setupLedJson, ret);
  return ret;
}
void waitLed()
{
  for (size_t i = 0; i < LED_COUNT; i++)
  {
    leds[i] = CRGB(random8(), random8(), random8());
  }
  FastLED.show(127);
}
void loadSetupLed()
{

  LittleFS.begin();

  File setupLedFile;

  // Nếu chưa thiết lập thông tin thì dung thông số mặc định
  if (!LittleFS.exists("/setupLed.json"))
  {
    setupLedFile = LittleFS.open("/setupLed.json", "w");
    setupLedFile.print(DEFAULT_SETUP_LED);
    setupLedFile.close();
  }

  JsonDocument doc;
  setupLedFile = LittleFS.open("/setupLed.json", "r");
  deserializeJson(doc, setupLedFile);
  JsonObject setupLedJson = doc.as<JsonObject>();
  secondHandColor = hexToRGB(setupLedJson["secondHandColor"]);
  minuteHandColor = hexToRGB(setupLedJson["minuteHandColor"]);
  hourHandColor = hexToRGB(setupLedJson["hourHandColor"]);
  brightness = setupLedJson["brightness"].as<uint8_t>();
  autoSyncTime = setupLedJson["autoSyncTime"].as<boolean>();
  setupLedFile.close();
}
void preSetupLed()
{

  FastLED.clear();
  FastLED.addLeds<NEOPIXEL, DAT_PIN>(leds, LED_COUNT);
  for (size_t c = 0; c < LED_COUNT; c++)
  {
    memset(leds, 0, sizeof(CRGB) * LED_COUNT);
    leds[c] = CRGB::Red;
    FastLED.show(255);
    delay(10);
  }
  for (size_t c = 0; c < LED_COUNT; c++)
  {
    memset(leds, 0, sizeof(CRGB) * LED_COUNT);
    leds[c] = CRGB::Green;

    FastLED.show(255);
    delay(10);
  }
  for (size_t c = 0; c < LED_COUNT; c++)
  {

    memset(leds, 0, sizeof(CRGB) * LED_COUNT);
    leds[c] = CRGB::Blue;

    FastLED.show(255);
    delay(10);
  }
};

void setupLed()
{

  loadSetupLed();
  int8_t res = WiFi.waitForConnectResult(15000);
  if (autoSyncTime && res == WL_CONNECTED)
  {
    timeClient.begin();
    for (size_t i = 0; i < 3; i++)
    {
      if (timeClient.forceUpdate())
        break;
      waitLed();
    }
  }
  I2Cone.begin(DS1307_SDA, DS1307_CLK);
  for (size_t i = 0; i < 3; i++)
  {
    if (!ds1307Time.begin(&I2Cone))
    {
      break;
    }
    delay(1000);
  }
  ds1307Time.begin();
  if (!ds1307Time.isrunning())
    ds1307Time.adjust(DateTime(F(__DATE__), F(__TIME__)));

  if (autoSyncTime && timeClient.isTimeSet())
  {
    // Nếu lấy được thời gian từ internet thì cập nhật cho cả ds1307 luôn
    espTime.begin(DateTime(timeClient.getEpochTime()));
    ds1307Time.adjust(DateTime(timeClient.getEpochTime()));
  }
  else
  {
    // Nếu không thì lấy từ ds1307
    if (ds1307Time.isrunning())
      espTime.begin(ds1307Time.now());
    else
      espTime.begin(DateTime(0, 0, 0, 0, 0, 0));
  }
  if (autoSyncTime)
    timeClient.end();

// Lấy thời gian xong thì tắt sta wifi
#ifndef DEVELOPMENT
  WiFi.mode(WIFI_AP);
#endif
  addHttpApi("/setAutoSyncTime",
             [](ESP8266WebServer *server)
             {
               JsonDocument doc;
               JsonObject obj = doc.to<JsonObject>();
               String value = server->arg("value");
               obj["oldValue"] = autoSyncTime;
               autoSyncTime = value == "true";
               updateLed();
               obj["newValue"] = autoSyncTime;
               String ret;
               serializeJson(obj, ret);
               server->send(200, "application/json", ret.c_str());
             });
  addHttpApi("/setSecondHandColor",
             [](ESP8266WebServer *server)
             {
               JsonDocument doc;
               JsonObject obj = doc.to<JsonObject>();
               String value = server->arg("value");
               obj["oldValue"] = rgbToHex(secondHandColor);
               secondHandColor = hexToRGB(value);
               updateLed();
               obj["newValue"] = rgbToHex(secondHandColor);
               String ret;
               serializeJson(obj, ret);
               server->send(200, "application/json", ret.c_str());
             });
  addHttpApi("/setMinuteHandColor",
             [](ESP8266WebServer *server)
             {
               JsonDocument doc;
               JsonObject obj = doc.to<JsonObject>();
               String value = server->arg("value");
               obj["oldValue"] = rgbToHex(minuteHandColor);
               minuteHandColor = hexToRGB(value);
               updateLed();

               obj["newValue"] = rgbToHex(minuteHandColor);
               String ret;
               serializeJson(obj, ret);
               server->send(200, "application/json", ret.c_str());
             });
  addHttpApi("/setHourHandColor",
             [](ESP8266WebServer *server)
             {
               JsonDocument doc;
               JsonObject obj = doc.to<JsonObject>();
               String value = server->arg("value");
               obj["oldValue"] = rgbToHex(hourHandColor);
               hourHandColor = hexToRGB(value);
               updateLed();
               obj["newValue"] = rgbToHex(hourHandColor);
               String ret;
               serializeJson(obj, ret);
               server->send(200, "application/json", ret.c_str());
             });
  addHttpApi("/setDateTime",
             [](ESP8266WebServer *server)
             {
               JsonDocument doc;
               JsonObject obj = doc.to<JsonObject>();
               String value = server->arg("value");
               obj["oldValue"] = espTime.now().unixtime();

               TimeSpan offset(0, 7, 0, 0);
               espTime.adjust(DateTime(value.toInt()) + offset);
               ds1307Time.adjust(espTime.now());

               obj["newValue"] = espTime.now().unixtime();
               String ret;
               serializeJson(obj, ret);
               server->send(200, "application/json", ret.c_str());
             });
  addHttpApi("/setBrightness",
             [](ESP8266WebServer *server)
             {
               JsonDocument doc;
               JsonObject obj = doc.to<JsonObject>();
               String value = server->arg("value");
               obj["oldValue"] = brightness;
               brightness = value.toInt();
               updateLed();
               obj["newValue"] = brightness;
               String ret;
               serializeJson(obj, ret);
               server->send(200, "application/json", ret.c_str());
             });
  addHttpApi("/setPower",
             [](ESP8266WebServer *server)
             {
               JsonDocument doc;
               JsonObject obj = doc.to<JsonObject>();
               String value = server->arg("value");
               obj["oldValue"] = power;
               power = value == "true";
               updateLed();
               obj["newValue"] = power;
               String ret;
               serializeJson(obj, ret);
               server->send(200, "application/json", ret.c_str());
             });
  addHttpApi("/getLed",
             [](ESP8266WebServer *server)
             {
               server->send(200, "application/json", getLed());
             });
  addHttpApi("/getDs1307",
             [](ESP8266WebServer *server)
             {
               String s = ds1307Time.isrunning() ? "y" : "n";
               server->send(200, "application/json", String(ds1307Time.now().hour()) + "-" + String(ds1307Time.now().minute()) + "-" + String(ds1307Time.now().second()) + "  " + s);
             });
}
void loopLed()
{
  static uint32_t timer = millis();
  if (millis() - timer > TICK_MS)
  {
    timer = millis();
    CRGB *secondLayer = secondHandHandle(secondHandColor, espTime.now().second());
    CRGB *minuteLayer = minuteHandHandHandle(minuteHandColor, espTime.now().minute());
    CRGB *hourLayer = hourHandHandHandle(hourHandColor, espTime.now().hour(), espTime.now().minute());
    for (size_t i = 0; i < LED_COUNT; i++)
    {
      leds[i] = CRGB::Black;
      if (
          secondLayer[i] == CRGB::Black &&
          minuteLayer[i] == CRGB::Black &&
          hourLayer[i] == CRGB::Black

      )
        continue;
      if (
          secondLayer[i] != CRGB::Black &&
          minuteLayer[i] == CRGB::Black &&
          hourLayer[i] == CRGB::Black

      )
        leds[i] = secondLayer[i];
      if (
          secondLayer[i] == CRGB::Black &&
          minuteLayer[i] != CRGB::Black &&
          hourLayer[i] == CRGB::Black

      )
        leds[i] = minuteLayer[i];
      if (
          secondLayer[i] == CRGB::Black &&
          minuteLayer[i] == CRGB::Black &&
          hourLayer[i] != CRGB::Black

      )
        leds[i] = hourLayer[i];
      if (
          secondLayer[i] != CRGB::Black &&
          minuteLayer[i] != CRGB::Black &&
          hourLayer[i] == CRGB::Black

      )
        leds[i] = secondLayer[i] / 2 + minuteLayer[i] / 2;
      if (
          secondLayer[i] != CRGB::Black &&
          minuteLayer[i] == CRGB::Black &&
          hourLayer[i] != CRGB::Black

      )
        leds[i] = secondLayer[i] / 2 + hourLayer[i] / 2;
      if (
          secondLayer[i] == CRGB::Black &&
          minuteLayer[i] != CRGB::Black &&
          hourLayer[i] != CRGB::Black

      )
        leds[i] = minuteLayer[i] / 2 + hourLayer[i] / 2;
      if (
          secondLayer[i] != CRGB::Black &&
          minuteLayer[i] != CRGB::Black &&
          hourLayer[i] != CRGB::Black

      )
        leds[i] = secondLayer[i] / 3 + minuteLayer[i] / 3 + hourLayer[i] / 3;
    }
    if (currentBrightness < brightness)
      currentBrightness++;
    if (currentBrightness > brightness)
      currentBrightness--;

    if (power)
      FastLED.show(currentBrightness);
    else
      FastLED.show(0);
  }
}
