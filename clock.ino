#include "Calendar.h"
#include "NeoPixelPixel.h"
#include <Adafruit_NeoPixel.h>
#include <HTTPClient.h>
#include <WiFi.h>

#define NEOPIXEL_PIN 13
#define NUM_PIXELS 12

Adafruit_NeoPixel neopixel =
    Adafruit_NeoPixel(NUM_PIXELS, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);

Calendar calendar;

NeoPixelPixel *pixels[NUM_PIXELS];

void setup() {
  Serial.begin(115200);
  timeUtils.syncTime();
  calendar.addEvent("Brooks Bus Depart", 7, 22, 0, 0b0111110);
  calendar.addEvent("Charlie Ali School", 8, 00, 0, 0b0111110);
  calendar.addEvent("Ali Pickup", 11, 30, 0, 0b0111110);
  calendar.addEvent("Brooks Bus Return", 14, 52, 0, 0b0111110);
  calendar.addEvent("Bedtime", 19, 00, 0, 0b0111110);
}

void loop() {
  timeUtils.printLocalTime();
  delay(1000);
  int minutesToNextEvent = calendar.minutesToNextEvent(timeUtils);
  Serial.print("Minutes to next event: ");
  Serial.println(minutesToNextEvent);
}