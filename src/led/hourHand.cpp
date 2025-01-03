#include "hourHand.h"

CRGB hourLayer[RING_CLOCK_LEDS];

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
int16_t calcMinute(int16_t minute)
{
    int16_t ret;
    ret = minute / 12;
    return ret;
}

CRGB *hourHandHandle(CRGB color, uint8_t hour, uint8_t minute)
{
    memset(hourLayer, CRGB::Black, sizeof(hourLayer));

    uint8_t currentHourIndex = RING_CLOCK_LEDS - calcHours(hour) - calcMinute(minute) - 1;

    hourLayer[currentHourIndex] = color;
    return hourLayer;
};
