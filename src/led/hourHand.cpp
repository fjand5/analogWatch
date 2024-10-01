#include "hourHand.h"

CRGB hourLayer[LED_COUNT];


int16_t calcHours(int16_t hours)
{
    int16_t ret;
    if (hours > 12)
    {
        ret = hours - 12;
    }
    ret = hours;
    ret = hours * 5;
    if (ret >= 60)
    {
        ret = ret - 60;
    }
    return ret;
}

CRGB *hourHandHandHandle(CRGB color, uint8_t hour)
{
  memset(hourLayer, CRGB::Black, sizeof(hourLayer));

  uint8_t currentHourIndex = LED_COUNT - calcHours(hour) - 1;

  hourLayer[currentHourIndex] = color;
  return hourLayer;
};
