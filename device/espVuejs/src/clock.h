
#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPUpdateServer.h>
#include <WS2812FX.h>

#define LED_PIN D1   // digital pin used to drive the LED strip
#define LED_COUNT 60 // number of LEDs on the strip
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "europe.pool.ntp.org", 7 * 3600);
WS2812FX ws2812fx = WS2812FX(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

ESP8266WebServer httpServer(80);
ESP8266HTTPUpdateServer httpUpdater;

// hàm getSeconds có lỗi.
uint32_t mySeconds;
uint32_t myMinutes;
uint32_t myHours;
WiFiEventHandler stationConnectedHandler;
WiFiEventHandler stationDisconnectedHandler;
volatile bool stopTick = false;

uint16_t myCustomEffect(void);
void onStationConnected(const WiFiEventSoftAPModeStationConnected &evt);
void onStationDisconnected(const WiFiEventSoftAPModeStationDisconnected &evt);
int32_t splitTowPhase(int32_t range, int32_t val);
int16_t mapHours(int16_t hours, int16_t min);
String macToString(const unsigned char *mac);
int16_t calcHours(int16_t hours);
int16_t calcMins(int16_t mins);

void setup()
{
    Serial.begin(115200);

    ws2812fx.init();
    ws2812fx.setBrightness(255);
    ws2812fx.setCustomMode(myCustomEffect);

    ws2812fx.start();

    WiFi.mode(WIFI_STA);
    WiFi.begin("Vong Cat 3", "78787878");

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(100);
        Serial.print(".");
    }

    timeClient.begin();
    ws2812fx.setMode(FX_MODE_CHASE_RAINBOW);
    while (millis()<30000)
    {
        ws2812fx.service();
    }
    while (!timeClient.update())
    {
        delay(500);
        ws2812fx.service();
        if(millis()> 180000)
            break;
    }
    if(timeClient.update())
        ws2812fx.setSegment(0, 0, LED_COUNT - 1, FX_MODE_CUSTOM, RED, 0);
    timeClient.end();
    

    Serial.println(timeClient.getFormattedTime());
    mySeconds = timeClient.getSeconds();
    myMinutes = timeClient.getMinutes();
    myHours = timeClient.getHours();

    stationConnectedHandler = WiFi.onSoftAPModeStationConnected(&onStationConnected);
    stationDisconnectedHandler = WiFi.onSoftAPModeStationDisconnected(&onStationDisconnected);
    WiFi.mode(WIFI_AP);
    WiFi.softAP("analog watch", "12345679");
    httpUpdater.setup(&httpServer);
    httpServer.begin();
}
uint32_t timer = millis();
uint32_t lastHous = 0;
void loop()
{
    if (!stopTick)
    {
        ws2812fx.service();
        // if (lastHous != timeClient.getHours()) {
        //   lastHous = timeClient.getHours();
        //   if (lastHous > 0 && lastHous < 6) {
        //     ws2812fx.setBrightness(64);
        //   }
        //   else if (lastHous < 16) {
        //     ws2812fx.setBrightness(255);
        //   }
        //   else {
        //     ws2812fx.setBrightness(128);
        //   }
        // }
        if (millis() - timer > 1000)
        {
            timer = millis();
            mySeconds++;
            if (mySeconds >= 60)
            {
                mySeconds = 0;
                myMinutes = timeClient.getMinutes();
                myHours = timeClient.getHours();
            }
        }
    }
    else
    {
        httpServer.handleClient();
    }
}

uint16_t myCustomEffect(void)
{                                                   // random chase
    WS2812FX::Segment *seg = ws2812fx.getSegment(); // get the current segment
    WS2812FX::Segment_runtime *segrt = ws2812fx.getSegmentRuntime();

    static uint32_t lastSeconds = 0;
    static uint32_t maxCounter = 0;
    if (mySeconds != lastSeconds)
    {
        maxCounter = segrt->counter_mode_call;
        segrt->counter_mode_call = 0;
    }
    int16_t brightSeconds = splitTowPhase(maxCounter, segrt->counter_mode_call);
    brightSeconds = ws2812fx.gamma8(brightSeconds);

    uint16_t length = seg->stop - seg->start + 1;

    ws2812fx.clear();
    for (uint16_t i = 0; i < length; i++)
    {
        int16_t hoursPosition = calcHours(myHours);
        if ((hoursPosition == 59 + calcMins(myMinutes) -i) 
        ){
            ws2812fx.setPixelColor(i, BLUE);
        }
        if (i == 59 - myMinutes)
        {
            uint32_t colors;

            colors = GREEN;

            if (myMinutes == hoursPosition)
                ws2812fx.setPixelColor(i, ws2812fx.color_blend(colors, BLUE, 128));
            else
                ws2812fx.setPixelColor(i, ws2812fx.color_blend(colors, ws2812fx.getPixelColor(i), 128));
        }
        if (i == 59 - mySeconds)
        {
            uint32_t color;
            color = ws2812fx.Color(brightSeconds, 0, 0);
            //      colors[0] = ws2812fx.Color(50 * ratio / 101, 0, 0);
            //      colors[1] = ws2812fx.Color(200 - 200 * ratio / 101, 0, 0);
            //      colors[2] = ws2812fx.Color(25 - 25 * ratio / 101, 0, 0);

            //      colors[0] = ws2812fx.Color(map(cycle, 0, interval, 0, 255), 0, 0);
            //      colors[1] = ws2812fx.Color(map(cycle, interval, 0, 0, 255), 0, 0);
            //      ws2812fx.setPixelColor(calcIndex(i - 1), ws2812fx.color_blend(colors[0], ws2812fx.getPixelColor(calcIndex(i - 1)), 64));
            if (ws2812fx.getPixelColor(i) != 0)
                color = ws2812fx.color_blend(color, ws2812fx.getPixelColor(i), 64);
            ws2812fx.setPixelColor(i, color);
            //      ws2812fx.setPixelColor(calcIndex(i + 1), ws2812fx.color_blend(colors[1], ws2812fx.getPixelColor(calcIndex(i + 1)), 64));
        }
    }
    lastSeconds = mySeconds;
    return seg->speed; // return the delay until the next animation step (in msec)
}

void onStationConnected(const WiFiEventSoftAPModeStationConnected &evt)
{
    Serial.print("Station connected: ");
    Serial.println(macToString(evt.mac));
    stopTick = true;
}

void onStationDisconnected(const WiFiEventSoftAPModeStationDisconnected &evt)
{
    Serial.print("Station disconnected: ");
    Serial.println(macToString(evt.mac));
    stopTick = false;
}
int32_t splitTowPhase(int32_t range, int32_t val)
{
    if (val < range / 2)
    {
        return val;
    }
    return range - val;
}
int16_t calcIndex(int16_t index)
{
    if (index >= 60)
    {
        return index - 60;
    }
    if (index < 0)
    {
        return 60 + index;
    }
    return index;
}
int16_t calcHours(int16_t hours)
{
    int16_t ret;
    if (hours > 12)
    {
        ret = hours - 12;
    }
    ret = hours;
    ret = hours*5;
    if(ret >= 60)
    {
        ret = ret - 60;
    }
    return ret;
}
int16_t calcMins(int16_t mins)
{
    int16_t ret;
    ret = mins/12;
    return ret;
}

// int16_t mapHours(int16_t hours, int16_t min)
// {
//     int16_t pos;
//     int16_t hour = calcHours(hours);
//     pos = hour * 5 + min*5/60;
//     return pos-1;
// }
String macToString(const unsigned char *mac)
{
    char buf[20];
    snprintf(buf, sizeof(buf), "%02x:%02x:%02x:%02x:%02x:%02x",
             mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
    return String(buf);
}
