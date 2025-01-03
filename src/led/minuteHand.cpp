#include "minuteHand.h"

CRGB minuteLayer[RING_CLOCK_LEDS];
CRGB *minuteHandHandle(CRGB color, uint8_t minute)
{
  memset(minuteLayer, CRGB::Black, sizeof(minuteLayer));

  uint8_t currentMinuteIndex = RING_CLOCK_LEDS - minute - 1;

  minuteLayer[currentMinuteIndex] = color;
  return minuteLayer;
};
