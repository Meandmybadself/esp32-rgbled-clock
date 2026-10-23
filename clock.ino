#include "Calendar.h"
#include "DailyEvent.h"
#include "NeoPixelPixel.h"
#include "wifi-credentials.h"
#include <Arduino.h>
#include <HTTPClient.h>
#include <WiFi.h>
#include <ezTime.h>

#define NEOPIXEL_PIN 13
#define NUM_PIXELS 12

Adafruit_NeoPixel neopixel =
    Adafruit_NeoPixel(NUM_PIXELS, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);

Calendar calendar;

NeoPixelPixel *pixels[NUM_PIXELS];

void setup() {
  Serial.begin(115200);
  WiFi.begin(AP_SSID, AP_PASSWORD);

  waitForSync();

  Serial.println("UTC: " + UTC.dateTime());

  Timezone Minnetonka;
  Minnetonka.setLocation("America/Chicago");
  Serial.println("Minnetonka time: " + Minnetonka.dateTime());

  calendar.addEvent("Brooks Bus Depart", 7, 22, 0, 0b0111110);
  calendar.addEvent("Charlie Ali School", 8, 00, 0, 0b0111110);
  calendar.addEvent("Ali Pickup", 11, 30, 0, 0b0111110);
  calendar.addEvent("Brooks Bus Return", 14, 52, 0, 0b0111110);
  calendar.addEvent("Bedtime", 19, 00, 0, 0b0111110);
}

void loop() {
  delay(1000);
  int minutesToNextEvent = calendar.minutesToNextEvent();
  Serial.print("Minutes to next event: ");
  Serial.println(minutesToNextEvent);
}