#include "../env.h"
#include "RTClib.h"
#include <FastLED.h>
#include <Adafruit_GFX.h>

class MatrixPanel : public GFXcanvas16
{
private:
  CRGB _matrixLayer[MATRIX_PANEL_LEDS];
  uint32_t _matrixTimer = millis();

  int curentYTime = 0;



public:
  void showTime(DateTime now);
  MatrixPanel(uint16_t w, uint16_t h);
  CRGB *matrixPanelHandle(DateTime now);
};
