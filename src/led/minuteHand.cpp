#include "minuteHand.h"

CRGB minuteLayer[LED_COUNT];
CRGB *minuteHandHandHandle(CRGB color, uint8_t minute)
{
  memset(minuteLayer, CRGB::Black, sizeof(minuteLayer));

  uint8_t currentMinuteIndex = LED_COUNT - minute - 1;

  minuteLayer[currentMinuteIndex] = color;
  return minuteLayer;
};
