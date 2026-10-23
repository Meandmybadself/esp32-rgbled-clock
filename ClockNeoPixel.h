#include <Adafruit_NeoPixel.h>

class NeoPixelPixel {
private:
  Adafruit_NeoPixel *strip;
  uint16_t pixelIndex;
  uint32_t color;
  uint8_t currentBrightness;

public:
  NeoPixelPixel(Adafruit_NeoPixel *strip, uint16_t pixelIndex, uint32_t color) {
    this->strip = strip;
    this->pixelIndex = pixelIndex;
    this->color = color;
    this->currentBrightness = 0;
    strip->setPixelColor(pixelIndex, color);
    strip->show();
  }

  uint8_t getCurrentBrightness() { return this->currentBrightness; }

  void scheduleAnimation(uint8_t startTime, uint8_t endTime, bool start_on,
                         float iterations) {}
};