#include "led.h"

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "europe.pool.ntp.org", 7 * 3600);
CLEDController *CLEDController_NEOPIXEL;
CLEDController *CLEDController_SM16703;
CLEDController *CLEDController_TM1829;
CLEDController *CLEDController_TM1812;
CLEDController *CLEDController_TM1809;
CLEDController *CLEDController_TM1804;
CLEDController *CLEDController_TM1803;
CLEDController *CLEDController_UCS1903;
CLEDController *CLEDController_UCS1903B;
CLEDController *CLEDController_UCS1904;
CLEDController *CLEDController_UCS2903;
CLEDController *CLEDController_WS2812;
CLEDController *CLEDController_WS2852;
CLEDController *CLEDController_WS2812B;
CLEDController *CLEDController_GS1903;
CLEDController *CLEDController_SK6812;
CLEDController *CLEDController_SK6822;
CLEDController *CLEDController_APA106;
CLEDController *CLEDController_PL9823;
CLEDController *CLEDController_WS2811;
CLEDController *CLEDController_WS2813;
CLEDController *CLEDController_APA104;
CLEDController *CLEDController_WS2811_400;
CLEDController *CLEDController_GE8822;
CLEDController *CLEDController_GW6205;
CLEDController *CLEDController_GW6205_400;
CLEDController *CLEDController_LPD1886;
CLEDController *CLEDController_LPD1886_8BIT;
CLEDController *CLEDController_LPD6803;
CLEDController *CLEDController_LPD8806;
CLEDController *CLEDController_WS2801;
CLEDController *CLEDController_WS2803;
CLEDController *CLEDController_SM16716;
CLEDController *CLEDController_P9813;
CLEDController *CLEDController_DOTSTAR;
CLEDController *CLEDController_APA102;
CLEDController *CLEDController_SK9822;

CLEDController *CLEDController_current;

CRGB leds[LED_COUNT];
uint16_t numLeds = LED_COUNT;

CRGB secondHandColor = CRGB::Red;
CRGB minuteHandColor = CRGB::Green;
CRGB hourHandColor = CRGB::Blue;

RTC_DS1307 ds1307Time;
// TwoWire I2Cone = TwoWire(1);

RTC_Millis espTime;
CRGB hexToRGB(String hex)
{
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
  return String(hex);
}
void updateProp(String key, String value)
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
  setupLedFile = LittleFS.open("/setupLed.json", "r");
  JsonDocument doc;
  deserializeJson(doc, setupLedFile);
  JsonObject setupLedJson = doc.as<JsonObject>();
  setupLedJson[key] = value;
  setupLedFile.close();

  setupLedFile = LittleFS.open("/setupLed.json", "w");
  serializeJson(doc, setupLedFile);
  setupLedFile.close();
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
  setupLedFile.close();
}

void setupLed()
{
  loadSetupLed();
  timeClient.begin();
  while (!timeClient.update())
  {
    delay(3000);
    if (millis() > 60000)
      break;
  }

  // I2Cone.begin(DS1307_SDA, DS1307_CLK);
  // for (size_t i = 0; i < 3; i++)
  // {
  //   if (!ds1307Time.begin(&I2Cone))
  //   {
  //     break;
  //   }
  //   delay(1000);
  // }

  // if (!ds1307Time.isrunning())
  //   ds1307Time.adjust(DateTime(F(__DATE__), F(__TIME__)));

  if (timeClient.isTimeSet())
  {
    // Nếu lấy được thời gian từ internet thì cập nhật luôn
    espTime.begin(DateTime(timeClient.getEpochTime()));
  }
  else
  {
    // Nếu không thì lấy từ ds1307
    espTime.begin(ds1307Time.now());
  }

  timeClient.end();
  FastLED.clear();
  FastLED.addLeds<NEOPIXEL, DAT_PIN>(leds, LED_COUNT); // GRB ordering is assumed
  // CLEDController_SM16703 = &FastLED.addLeds<SM16703, DAT_PIN, RGB>(leds, LED_COUNT);
  // CLEDController_TM1829 = &FastLED.addLeds<TM1829, DAT_PIN, RGB>(leds, LED_COUNT);
  // CLEDController_TM1812 = &FastLED.addLeds<TM1812, DAT_PIN, RGB>(leds, LED_COUNT);
  // CLEDController_TM1809 = &FastLED.addLeds<TM1809, DAT_PIN, RGB>(leds, LED_COUNT);
  // CLEDController_TM1804 = &FastLED.addLeds<TM1804, DAT_PIN, RGB>(leds, LED_COUNT);
  // CLEDController_TM1803 = &FastLED.addLeds<TM1803, DAT_PIN, RGB>(leds, LED_COUNT);
  // CLEDController_UCS1903 = &FastLED.addLeds<UCS1903, DAT_PIN, RGB>(leds, LED_COUNT).setCorrection(Typical8mmPixel);
  // CLEDController_UCS1903B = &FastLED.addLeds<UCS1903B, DAT_PIN, RGB>(leds, LED_COUNT).setCorrection(Typical8mmPixel);
  // CLEDController_UCS1904 = &FastLED.addLeds<UCS1904, DAT_PIN, RGB>(leds, LED_COUNT);
  // CLEDController_UCS2903 = &FastLED.addLeds<UCS2903, DAT_PIN, RGB>(leds, LED_COUNT);
  // CLEDController_WS2812 = &FastLED.addLeds<WS2812, DAT_PIN, RGB>(leds, LED_COUNT);   // GRB ordering is typical
  // CLEDController_WS2852 = &FastLED.addLeds<WS2852, DAT_PIN, RGB>(leds, LED_COUNT);   // GRB ordering is typical
  // CLEDController_WS2812B = &FastLED.addLeds<WS2812B, DAT_PIN, RGB>(leds, LED_COUNT); // GRB ordering is typical
  // CLEDController_GS1903 = &FastLED.addLeds<GS1903, DAT_PIN, RGB>(leds, LED_COUNT);
  // CLEDController_SK6812 = &FastLED.addLeds<SK6812, DAT_PIN, RGB>(leds, LED_COUNT); // GRB ordering is typical
  // CLEDController_SK6822 = &FastLED.addLeds<SK6822, DAT_PIN, RGB>(leds, LED_COUNT);
  // CLEDController_APA106 = &FastLED.addLeds<APA106, DAT_PIN, RGB>(leds, LED_COUNT);
  // CLEDController_PL9823 = &FastLED.addLeds<PL9823, DAT_PIN, RGB>(leds, LED_COUNT);
  // CLEDController_WS2811 = &FastLED.addLeds<WS2811, DAT_PIN, RGB>(leds, LED_COUNT);
  // CLEDController_WS2813 = &FastLED.addLeds<WS2813, DAT_PIN, RGB>(leds, LED_COUNT);
  // CLEDController_APA104 = &FastLED.addLeds<APA104, DAT_PIN, RGB>(leds, LED_COUNT);
  // CLEDController_WS2811_400 = &FastLED.addLeds<WS2811_400, DAT_PIN, RGB>(leds, LED_COUNT);
  // CLEDController_GE8822 = &FastLED.addLeds<GE8822, DAT_PIN, RGB>(leds, LED_COUNT);
  // CLEDController_GW6205 = &FastLED.addLeds<GW6205, DAT_PIN, RGB>(leds, LED_COUNT);
  // CLEDController_GW6205_400 = &FastLED.addLeds<GW6205_400, DAT_PIN, RGB>(leds, LED_COUNT);
  // CLEDController_LPD1886 = &FastLED.addLeds<LPD1886, DAT_PIN, RGB>(leds, LED_COUNT);
  // CLEDController_LPD1886_8BIT = &FastLED.addLeds<LPD1886_8BIT, DAT_PIN, RGB>(leds, LED_COUNT);
  // CLEDController_LPD6803 = &FastLED.addLeds<LPD6803, DAT_PIN, CLK_PIN, RGB>(leds, LED_COUNT); // GRB ordering is typical
  // CLEDController_LPD8806 = &FastLED.addLeds<LPD8806, DAT_PIN, CLK_PIN, RGB>(leds, LED_COUNT); // GRB ordering is typical
  // CLEDController_WS2801 = &FastLED.addLeds<WS2801, DAT_PIN, CLK_PIN, RGB>(leds, LED_COUNT);
  // CLEDController_WS2803 = &FastLED.addLeds<WS2803, DAT_PIN, CLK_PIN, RGB>(leds, LED_COUNT);
  // CLEDController_SM16716 = &FastLED.addLeds<SM16716, DAT_PIN, CLK_PIN, RGB>(leds, LED_COUNT);
  // CLEDController_P9813 = &FastLED.addLeds<P9813, DAT_PIN, CLK_PIN, RGB>(leds, LED_COUNT);     // BGR ordering is typical
  // CLEDController_DOTSTAR = &FastLED.addLeds<DOTSTAR, DAT_PIN, CLK_PIN, RGB>(leds, LED_COUNT); // BGR ordering is typical
  // CLEDController_APA102 = &FastLED.addLeds<APA102, DAT_PIN, CLK_PIN, RGB>(leds, LED_COUNT);   // BGR ordering is typical
  // CLEDController_SK9822 = &FastLED.addLeds<SK9822, DAT_PIN, CLK_PIN, RGB>(leds, LED_COUNT);   // BGR ordering is typical
  // CLEDController_current = CLEDController_UCS1903;
  addHttpApi("/getFormattedTime",
             [](ESP8266WebServer *server)
             {
               server->send(200, "text/html", timeClient.getFormattedTime());
             });
  addHttpApi("/setSecondHandColor",
             [](ESP8266WebServer *server)
             {
               JsonDocument doc;
               JsonObject obj = doc.to<JsonObject>();
               String value = server->arg("value");
               obj["oldValue"] = rgbToHex(secondHandColor);
               secondHandColor = hexToRGB(value);
               updateProp("secondHandColor", value);
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
               updateProp("minuteHandColor", value);

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
               updateProp("hourHandColor", value);
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

               // I2Cone.begin(DS1307_SDA, DS1307_CLK);
               // for (size_t i = 0; i < 3; i++)
               // {
               //   if (!ds1307Time.begin(&I2Cone))
               //   {
               //     break;
               //   }
               //   delay(1000);
               // }

               // if (!ds1307Time.isrunning())
               //   ds1307Time.adjust(DateTime(F(__DATE__), F(__TIME__)));

               //  ds1307Time.adjust(DateTime(stamp) + offset);

               obj["newValue"] = espTime.now().unixtime();
               String ret;
               serializeJson(obj, ret);
               server->send(200, "application/json", ret.c_str());
             });
  addHttpApi("/setTimeZone",
             [](ESP8266WebServer *server)
             {
               JsonDocument doc;
               JsonObject obj = doc.to<JsonObject>();
               String value = server->arg("value");
               obj["oldValue"] = espTime.now().unixtime();

               TimeSpan offset(0, 7, 0, 0);
               espTime.adjust(DateTime(value.toInt()) + offset);
               // I2Cone.begin(DS1307_SDA, DS1307_CLK);
               // for (size_t i = 0; i < 3; i++)
               // {
               //   if (!ds1307Time.begin(&I2Cone))
               //   {
               //     break;
               //   }
               //   delay(1000);
               // }

               // if (!ds1307Time.isrunning())
               //   ds1307Time.adjust(DateTime(F(__DATE__), F(__TIME__)));

               //  ds1307Time.adjust(DateTime(stamp) + offset);

               obj["newValue"] = espTime.now().unixtime();
               String ret;
               serializeJson(obj, ret);
               server->send(200, "application/json", ret.c_str());
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
    CRGB *hourLayer = hourHandHandHandle(hourHandColor, espTime.now().hour());
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
    FastLED.show();
  }
}
