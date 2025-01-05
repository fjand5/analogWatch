#include "../env.h"
#include "RTClib.h"
#include <FastLED.h>
#include <Adafruit_GFX.h>

#define SHOW_TIME 1
#define SHOW_DAY 2
#define SHOW_LUNAR_DAY 3

class MatrixPanel : public GFXcanvas16
{
private:
  CRGB _matrixLayer[MATRIX_PANEL_LEDS];
  uint32_t _matrixTimer = millis();

  int _lunarDayCurentYCursor = -8;
  int _lunarDayYCursor = -8;

  int _dayCurentYCursor = -8;
  int _dayYCursor = -8;

  int _timeCurentYCursor = 0;
  int _timeYCursor = 0;

  int _show = SHOW_TIME;

  uint32_t _timeShowTime = 15000;
  uint32_t _dayShowTime = 5000;
  uint32_t _lunarDayShowTime = 5000;

  CRGB _timeColor = CRGB::White;
  CRGB _dayColor = CRGB::Red;
  CRGB _lunarDayColor = CRGB::Blue;

public:
  void showTime(DateTime now);
  MatrixPanel(uint16_t w, uint16_t h);
  CRGB *matrixPanelHandle(DateTime now);
  void setTimeColor(CRGB color);
  void setDayColor(CRGB color);
  void setLunarDayColor(CRGB color);

  CRGB getTimeColor();
  CRGB getDayColor();
  CRGB getLunarDayColor();

  uint32_t getTimeShowTime() const
  {
    return _timeShowTime;
  }

  void setTimeShowTime(uint32_t time)
  {
    _timeShowTime = time;
  }

  uint32_t getDayShowTime() const
  {
    return _dayShowTime;
  }

  void setDayShowTime(uint32_t time)
  {
    _dayShowTime = time;
  }

  uint32_t getLunarDayShowTime() const
  {
    return _lunarDayShowTime;
  }

  void setLunarDayShowTime(uint32_t time)
  {
    _lunarDayShowTime = time;
  }
};
