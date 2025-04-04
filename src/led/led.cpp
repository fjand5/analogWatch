#include "led.h"

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "europe.pool.ntp.org", 7 * 3600);

CRGB leds[LED_COUNT];

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

MatrixPanel *matrixPanel;
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

  // Matrixpanel
  setupLedJson["timeColor"] = rgbToHex(matrixPanel->getTimeColor());
  setupLedJson["dayColor"] = rgbToHex(matrixPanel->getDayColor());
  setupLedJson["lunarDayColor"] = rgbToHex(matrixPanel->getLunarDayColor());

  setupLedJson["timeShowTime"] = matrixPanel->getTimeShowTime();
  setupLedJson["dayShowTime"] = matrixPanel->getDayShowTime();
  setupLedJson["lunarDayShowTime"] = matrixPanel->getLunarDayShowTime();
  serializeJson(doc, setupLedFile);
  setupLedFile.close();
}
String getLed()
{
  JsonDocument doc;
  JsonObject setupLedJson = doc.to<JsonObject>();
  // AnalogWatch
  setupLedJson["secondHandColor"] = rgbToHex(secondHandColor);
  setupLedJson["minuteHandColor"] = rgbToHex(minuteHandColor);
  setupLedJson["hourHandColor"] = rgbToHex(hourHandColor);
  setupLedJson["brightness"] = brightness;
  setupLedJson["power"] = power;
  setupLedJson["timeStamp"] = espTime.now().unixtime();
  setupLedJson["autoSyncTime"] = autoSyncTime;
  // Matrixpanel
  setupLedJson["timeShowTime"] = matrixPanel->getTimeShowTime();
  setupLedJson["dayShowTime"] = matrixPanel->getDayShowTime();
  setupLedJson["lunarDayShowTime"] = matrixPanel->getLunarDayShowTime();

  setupLedJson["timeColor"] = rgbToHex(matrixPanel->getTimeColor());
  setupLedJson["dayColor"] = rgbToHex(matrixPanel->getDayColor());
  setupLedJson["lunarDayColor"] = rgbToHex(matrixPanel->getLunarDayColor());
  String ret;
  serializeJson(setupLedJson, ret);
  return ret;
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

  matrixPanel->setTimeShowTime(setupLedJson["timeShowTime"]);
  matrixPanel->setDayShowTime(setupLedJson["dayShowTime"]);
  matrixPanel->setLunarDayShowTime(setupLedJson["lunarDayShowTime"]);

  matrixPanel->setTimeColor(hexToRGB(setupLedJson["timeColor"]));
  matrixPanel->setDayColor(hexToRGB(setupLedJson["dayColor"]));
  matrixPanel->setLunarDayColor(hexToRGB(setupLedJson["lunarDayColor"]));

  setupLedFile.close();
}
void preSetupLed()
{

  FastLED.clear();
  FastLED.addLeds<NEOPIXEL, DAT_PIN>(leds, LED_COUNT);
  for (size_t c = 0; c < RING_CLOCK_LEDS; c++)
  {
    memset(leds, 0, sizeof(CRGB) * LED_COUNT);
    leds[c] = CRGB::Red;
    FastLED.show(32);
  }
  for (size_t c = 0; c < RING_CLOCK_LEDS; c++)
  {
    memset(leds, 0, sizeof(CRGB) * LED_COUNT);
    leds[c] = CRGB::Green;
    FastLED.show(32);
  }

  for (size_t c = 0; c < RING_CLOCK_LEDS; c++)
  {
    memset(leds, 0, sizeof(CRGB) * LED_COUNT);
    leds[c] = CRGB::Blue;
    FastLED.show(32);
  }
  memset(leds, 0, sizeof(CRGB) * LED_COUNT);

  for (size_t c = RING_CLOCK_LEDS; c < LED_COUNT; c++)
  {
    leds[c] = CRGB::Red;
  }
  FastLED.show(32);
  delay(1000);
  for (size_t c = RING_CLOCK_LEDS; c < LED_COUNT; c++)
  {
    leds[c] = CRGB::Green;
  }
  FastLED.show(32);
  delay(1000);
  for (size_t c = RING_CLOCK_LEDS; c < LED_COUNT; c++)
  {

    leds[c] = CRGB::Blue;
  }
  FastLED.show(32);
  delay(1000);
};

void setupLed()
{
  matrixPanel = new MatrixPanel(MATRIX_PANEL_WIDTH, MATRIX_PANEL_HEIGHT);
  loadSetupLed();
  uint16_t index = RING_CLOCK_LEDS;
  while (WiFi.status() != WL_CONNECTED)
  {
    // Chờ đến khi kết nối được hoặc đủ MATRIX_PANEL_LEDS
    memset(leds, 0, sizeof(CRGB) * LED_COUNT);
    leds[index] = CRGB::White;
    FastLED.show(255);
    delay(10);
    if (index >= LED_COUNT)
      break;
    index++;
  }
  int8_t res = WiFi.status();

  if (autoSyncTime && res == WL_CONNECTED)
  {
    timeClient.begin();
    for (size_t i = 0; i < 3; i++)
    {
      if (timeClient.forceUpdate())
        break;
      // waitLed();
    }
  }
  I2Cone.begin(DS1307_SDA, DS1307_CLK);
  for (size_t i = 0; i < 3; i++)
  {
    if (!ds1307Time.begin(&I2Cone))
    {
      break;
    }
    delay(555);
  }
  ds1307Time.begin();
  if (!ds1307Time.isrunning())
  {
    ds1307Time.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
  else
  {
  }
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

  // matrix panel
  addHttpApi("/setTimeShowTime",
             [](ESP8266WebServer *server)
             {
               JsonDocument doc;
               JsonObject obj = doc.to<JsonObject>();
               String value = server->arg("value");
               obj["oldValue"] = matrixPanel->getTimeShowTime();
               matrixPanel->setTimeShowTime(value.toInt());
               updateLed();
               obj["newValue"] = matrixPanel->getTimeShowTime();
               String ret;
               serializeJson(obj, ret);
               server->send(200, "application/json", ret.c_str());
             });
  addHttpApi("/setDayShowTime",
             [](ESP8266WebServer *server)
             {
               JsonDocument doc;
               JsonObject obj = doc.to<JsonObject>();
               String value = server->arg("value");
               obj["oldValue"] = matrixPanel->getDayShowTime();
               matrixPanel->setDayShowTime(value.toInt());
               updateLed();
               obj["newValue"] = matrixPanel->getDayShowTime();
               String ret;
               serializeJson(obj, ret);
               server->send(200, "application/json", ret.c_str());
             });
  addHttpApi("/setLunarDayShowTime",
             [](ESP8266WebServer *server)
             {
               JsonDocument doc;
               JsonObject obj = doc.to<JsonObject>();
               String value = server->arg("value");
               obj["oldValue"] = matrixPanel->getLunarDayShowTime();
               matrixPanel->setLunarDayShowTime(value.toInt());
               updateLed();
               obj["newValue"] = matrixPanel->getLunarDayShowTime();
               String ret;
               serializeJson(obj, ret);
               server->send(200, "application/json", ret.c_str());
             });
  addHttpApi("/setTimeColor",
             [](ESP8266WebServer *server)
             {
               JsonDocument doc;
               JsonObject obj = doc.to<JsonObject>();
               String value = server->arg("value");
               obj["oldValue"] = rgbToHex(matrixPanel->getTimeColor());
               matrixPanel->setTimeColor(hexToRGB(value));
               updateLed();
               obj["newValue"] = rgbToHex(matrixPanel->getTimeColor());
               String ret;
               serializeJson(obj, ret);
               server->send(200, "application/json", ret.c_str());
             });
  addHttpApi("/setDayColor",
             [](ESP8266WebServer *server)
             {
               JsonDocument doc;
               JsonObject obj = doc.to<JsonObject>();
               String value = server->arg("value");
               obj["oldValue"] = rgbToHex(matrixPanel->getDayColor());
               matrixPanel->setDayColor(hexToRGB(value));
               updateLed();
               obj["newValue"] = rgbToHex(matrixPanel->getDayColor());
               String ret;
               serializeJson(obj, ret);
               server->send(200, "application/json", ret.c_str());
             });
  addHttpApi("/setLunarDayColor",
             [](ESP8266WebServer *server)
             {
               JsonDocument doc;
               JsonObject obj = doc.to<JsonObject>();
               String value = server->arg("value");
               obj["oldValue"] = rgbToHex(matrixPanel->getLunarDayColor());
               matrixPanel->setLunarDayColor(hexToRGB(value));
               updateLed();
               obj["newValue"] = rgbToHex(matrixPanel->getLunarDayColor());
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
  // ------------------------------------------
  addHttpApi("/setDateTime",
             [](ESP8266WebServer *server)
             {
               JsonDocument doc;
               JsonObject obj = doc.to<JsonObject>();
               String value = server->arg("value");
               obj["oldValue"] = espTime.now().unixtime();

               TimeSpan offset(0, 7, 0, 0);
               ds1307Time.adjust(DateTime(value.toInt()) + offset);
               espTime.adjust(ds1307Time.now());

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
CRGB *handleRingClock(CRGB *secondLayer, CRGB *minuteLayer, CRGB *hourLayer)
{

  static CRGB ringClockLayer[RING_CLOCK_LEDS];
  for (size_t i = 0; i < RING_CLOCK_LEDS; i++)
  {
    ringClockLayer[i] = CRGB::Black;
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
      ringClockLayer[i] = secondLayer[i];
    if (
        secondLayer[i] == CRGB::Black &&
        minuteLayer[i] != CRGB::Black &&
        hourLayer[i] == CRGB::Black

    )
      ringClockLayer[i] = minuteLayer[i];
    if (
        secondLayer[i] == CRGB::Black &&
        minuteLayer[i] == CRGB::Black &&
        hourLayer[i] != CRGB::Black

    )
      ringClockLayer[i] = hourLayer[i];
    if (
        secondLayer[i] != CRGB::Black &&
        minuteLayer[i] != CRGB::Black &&
        hourLayer[i] == CRGB::Black

    )
      ringClockLayer[i] = secondLayer[i] / 2 + minuteLayer[i] / 2;
    if (
        secondLayer[i] != CRGB::Black &&
        minuteLayer[i] == CRGB::Black &&
        hourLayer[i] != CRGB::Black

    )
      ringClockLayer[i] = secondLayer[i] / 2 + hourLayer[i] / 2;
    if (
        secondLayer[i] == CRGB::Black &&
        minuteLayer[i] != CRGB::Black &&
        hourLayer[i] != CRGB::Black

    )
      ringClockLayer[i] = minuteLayer[i] / 2 + hourLayer[i] / 2;
    if (
        secondLayer[i] != CRGB::Black &&
        minuteLayer[i] != CRGB::Black &&
        hourLayer[i] != CRGB::Black

    )
      ringClockLayer[i] = secondLayer[i] / 3 + minuteLayer[i] / 3 + hourLayer[i] / 3;
  }
  return ringClockLayer;
}
void loopLed()
{
  static uint32_t ledTimer = millis();
  if (millis() - ledTimer > TICK_MS)
  {
    ledTimer = millis();
    CRGB *secondLayer = secondHandHandle(secondHandColor, espTime.now().second());
    CRGB *minuteLayer = minuteHandHandle(minuteHandColor, espTime.now().minute());
    CRGB *hourLayer = hourHandHandle(hourHandColor, espTime.now().hour(), espTime.now().minute());
    CRGB *ringClockLayer = handleRingClock(secondLayer, minuteLayer, hourLayer);
    CRGB *matrixPanelLayer = matrixPanel->matrixPanelHandle(espTime.now());

    memcpy(leds, ringClockLayer, sizeof(CRGB) * RING_CLOCK_LEDS);
    memcpy(leds + RING_CLOCK_LEDS, matrixPanelLayer, sizeof(CRGB) * MATRIX_PANEL_LEDS);

    // show leds

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
