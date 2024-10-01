#define FADE_EVERY_TICK 255 / (1000 / TICK_MS)
#include "secondHand.h"

CRGB secondLayer[LED_COUNT];
uint8_t lastSecond = 0;
CRGB currentColor;
CRGB nextColor;
int16_t fadeIndex = 0;
CRGB *secondHandHandle(CRGB color, uint8_t second)
{
  memset(secondLayer, CRGB::Black, sizeof(secondLayer));

  uint8_t currentSecondIndex = LED_COUNT - second - 1;
  uint8_t nextSecondIndex = (second + 1) > 59 ? LED_COUNT - 1 : LED_COUNT - (second + 1) - 1;

  if (second != lastSecond)
  {
    currentColor = color;
    nextColor = CRGB::Black;
    fadeIndex = 255;
  }
  else
  {
    if (fadeIndex < 0)
      fadeIndex = 0;
    currentColor = blend(CRGB::Black, color, fadeIndex);
    nextColor = blend(color, CRGB::Black, fadeIndex);
    fadeIndex -= FADE_EVERY_TICK*2;
  }

  secondLayer[currentSecondIndex] = currentColor;
  secondLayer[nextSecondIndex] = nextColor;
  lastSecond = second;
  return secondLayer;
};
