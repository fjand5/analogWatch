#include "matrixPanel.h"
#include "systemDateTime/systemDateTime.h"
#include "webserver/webserver.h"

uint8_t step = 0;
CHSVPalette16 chsvPalette16;
CRGB scroll(int pos)
{
  CRGB color(0, 0, 0);
  if (pos < 85)
  {
    color.g = 0;
    color.r = ((float)pos / 85.0f) * 255.0f;
    color.b = 255 - color.r;
  }
  else if (pos < 170)
  {
    color.g = ((float)(pos - 85) / 85.0f) * 255.0f;
    color.r = 255 - color.g;
    color.b = 0;
  }
  else if (pos < 256)
  {
    color.b = ((float)(pos - 170) / 85.0f) * 255.0f;
    color.g = 255 - color.b;
    color.r = 1;
  }
  return color;
}
inline uint32_t rgb565Torgb888(uint16_t rgb565)
{
  uint8_t R5 = ((rgb565 & 0xF800) >> 8) * 5;
  uint8_t G6 = ((rgb565 & 0x07E0) >> 3) * 8;
  uint8_t B5 = (rgb565 & 0x001F) << 3;

  uint8_t R8 = (R5 * 527 + 23) >> 6;
  uint8_t G8 = (G6 * 259 + 33) >> 6;
  uint8_t B8 = (B5 * 527 + 23) >> 6;
  return (R8 << 16) | (G8 << 8) | B8;
}
uint16_t rgb888ToRgb565(uint8_t r, uint8_t g, uint8_t b)
{

  return ((r & 0b11111000) << 8) | ((g & 0b11111100) << 3) | (b >> 3);
}
void MatrixPanel::setTimeColor(CRGB color)
{
  _timeColor = color;
};

void MatrixPanel::setDayColor(CRGB color)
{
  _dayColor = color;
};
void MatrixPanel::setLunarDayColor(CRGB color)
{
  _lunarDayColor = color;
};
CRGB MatrixPanel::getTimeColor()
{
  return _timeColor;
};
CRGB MatrixPanel::getDayColor()
{
  return _dayColor;
};
CRGB MatrixPanel::getLunarDayColor()
{
  return _lunarDayColor;
};

void MatrixPanel::showTime(DateTime now)
{
  setTextWrap(false);

  setCursor(1, _timeCurentYCursor);
  setTextColor(rgb888ToRgb565(_timeColor.r, _timeColor.g, _timeColor.b), 0);
  if (now.hour() < 10)
    print("0");
  print(now.hour());
  if (now.second() % 2)
    print(":");
  else
    print(" ");
  if (now.minute() < 10)
    print("0");

  print(now.minute());

  setCursor(1, _dayCurentYCursor);
  setTextColor(rgb888ToRgb565(_dayColor.r, _dayColor.g, _dayColor.b), 0);

  printf("%02d/%02d", now.day(), now.month());

  setCursor(1, _lunarDayCurentYCursor);
  setTextColor(rgb888ToRgb565(_lunarDayColor.r, _lunarDayColor.g, _lunarDayColor.b), 0);
  DaysStruct lunarDayStruct;
  lunarDayStruct = cvtSun2Lunar(now.day(), now.month(), now.year() - 2000);
  printf("%02d/%02d", lunarDayStruct.day, lunarDayStruct.month);
};

CRGB *MatrixPanel::matrixPanelHandle(DateTime now)
{
  static uint32_t timer = millis();
  static uint32_t setShowTimer = millis();
  static uint32_t nextShowTime = 5000;

  static uint8_t showOffset = 0; // Màn hình bị dư 1 hàng, nên cho xê dịch để tận dụng
  if (millis() - setShowTimer > nextShowTime)
  {
    setShowTimer = millis();
    showOffset++;
    if (_show == SHOW_TIME) // Hiển thị thời gian
    {
      _show = SHOW_DAY;
      _timeYCursor = 0 + showOffset % 2;
      _dayYCursor = -8;
      _lunarDayYCursor = -8;
      nextShowTime = _timeShowTime;
    }
    else if (_show == SHOW_DAY) // Hiển thị ngày dương
    {
      _show = SHOW_LUNAR_DAY;
      _timeYCursor = -8;
      _dayYCursor = 0 + showOffset % 2;
      _lunarDayYCursor = -8;
      nextShowTime = _dayShowTime;
    }
    else if (_show == SHOW_LUNAR_DAY) // Hiển thị ngày âm
    {
      _show = SHOW_TIME;

      _timeYCursor = -8;
      _dayYCursor = -8;
      _lunarDayYCursor = 0 + showOffset % 2;
      nextShowTime = _lunarDayShowTime;
    }
  }
  if (millis() - timer > 33)
  {
    timer = millis();
    step++;
    if (_dayCurentYCursor < _dayYCursor)
      _dayCurentYCursor++;
    if (_dayCurentYCursor > _dayYCursor)
      _dayCurentYCursor--;

    if (_lunarDayCurentYCursor < _lunarDayYCursor)
      _lunarDayCurentYCursor++;
    if (_lunarDayCurentYCursor > _lunarDayYCursor)
      _lunarDayCurentYCursor--;

    if (_timeCurentYCursor < _timeYCursor)
      _timeCurentYCursor++;
    if (_timeCurentYCursor > _timeYCursor)
      _timeCurentYCursor--;
  }
  fillScreen(0);
  showTime(now);

  // xuất ảnh
  for (int16_t x = 0; x < _width; x += 2)
  {
    for (int16_t y = 0; y < _height; y++)
    {
      _matrixLayer[x * _height + y] = rgb565Torgb888(getPixel(x, y));
    }
  }
  for (int16_t x = 1; x < _width; x += 2)
  {
    for (int16_t y = 0; y < _height; y++)
    {
      _matrixLayer[(x + 1) * _height - y - 1] = rgb565Torgb888(getPixel(x, y));
    }
  }
  return _matrixLayer;
};

MatrixPanel::MatrixPanel(uint16_t w, uint16_t h) : GFXcanvas16(w, h)
{
}
