#include "matrixPanel.h"
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
void MatrixPanel::showTime(DateTime now)
{
  CRGB color = CRGB::Chocolate;

  setCursor(0, curentYTime);
  setTextColor(rgb888ToRgb565(color.r, color.g, color.b), 0);

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
};

CRGB *MatrixPanel::matrixPanelHandle(DateTime now)
{
  static uint32_t timer = millis();
  // static bool isInit = false;
  // if (!isInit)
  // {
  //   isInit = true;

  //   for (uint16_t i = 0; i < 16; i++)
  //   {
  //     chsvPalette16[i].setHue(i * 255 / (16 - 1) + millis() / 8);
  //     delay(1);
  //   }
  // }
  if (millis() - timer > 100)
  {
    timer = millis();
    step++;
    curentYTime++;
    if (curentYTime > 16)
      curentYTime = 0;
  }
  // CHSV hsv(step % 255, 255, 255);
  // hsv2rgb_rainbow(hsv, color);
  fillScreen(0);
  showTime(now);
  return _matrixLayer;
};

MatrixPanel::MatrixPanel(uint16_t w, uint16_t h) : GFXcanvas16(w, h)
{
}
