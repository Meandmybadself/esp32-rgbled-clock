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

  void turnOn() {
    if (this->getCurrentBrightness() == 0) {
      this->fade(255, 300);
    } else {
      this->setBrightness(255);
    }
  }

  void turnOff() {
    if (this->getCurrentBrightness() == 1) {
      this->fade(0, 300);
    }
  }

  void fade(uint8_t targetBrightness, unsigned long timeMS) {

    int steps = 100;
    int delayTime = timeMS / steps;
    float brightnessStep =
        (float)(targetBrightness - this->currentBrightness) / steps;

    for (int i = 0; i < steps; i++) {
      this->currentBrightness += brightnessStep;
      uint8_t r = (color >> 16) & 0xFF;
      uint8_t g = (color >> 8) & 0xFF;
      uint8_t b = color & 0xFF;
      uint32_t newColor =
          strip->Color(strip->gamma8(r * currentBrightness / 255),
                       strip->gamma8(g * currentBrightness / 255),
                       strip->gamma8(b * currentBrightness / 255));
      strip->setPixelColor(pixelIndex, newColor);
      strip->show();
      delay(delayTime);
    }
  }

  void setBrightness(uint8_t brightness) {

    this->currentBrightness = brightness;
    uint8_t r = (color >> 16) & 0xFF;
    uint8_t g = (color >> 8) & 0xFF;
    uint8_t b = color & 0xFF;
    uint32_t newColor =
        strip->Color(strip->gamma8(r * currentBrightness / 255),
                     strip->gamma8(g * currentBrightness / 255),
                     strip->gamma8(b * currentBrightness / 255));
    strip->setPixelColor(pixelIndex, newColor);
  }
};