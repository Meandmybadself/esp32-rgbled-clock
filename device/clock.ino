#include <WiFi.h>
#include <HTTPClient.h>
#include <Adafruit_NeoPixel.h>
#include "NeoPixelPixel.h"
#include "wifi-credentials.h"

#define NEOPIXEL_PIN 13
#define NUM_PIXELS 12

// Replace with your network credentials
const char *ssid = "";
const char *password = "";

// Replace with the IP address or hostname of your server
const char *serverAddress = "";

Adafruit_NeoPixel neopixel = Adafruit_NeoPixel(NUM_PIXELS, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);

NeoPixelPixel *pixels[NUM_PIXELS];

void setup()
{
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("WiFi connected.  Initializing pixels.");
  neopixel.begin();

  for (uint16_t i = 0; i < NUM_PIXELS; i++)
  {
    uint32_t color = neopixel.Color(255, 0, 0);
    pixels[i] = new NeoPixelPixel(&neopixel, i, color);
  }

  neopixel.clear();
  neopixel.show();
}

void loop()
{
  if (WiFi.status() == WL_CONNECTED)
  {
    HTTPClient http;
    http.begin(serverAddress);
    int httpResponseCode = http.GET();

    if (httpResponseCode == 200)
    {
      String response = http.getString();
      int numberOfSeconds = response.toInt();
      // Serial.print("Seconds:");
      // Serial.println(numberOfSeconds);

      // const maxTime = 12 * 60;
      // // If the number of seconds is greater than 12 * 60, put the board to sleep.
      // if (numberOfSeconds > maxTime) {
      //   Serial.println("Going to sleep");
      //   const timeToSleep = numberOfSeconds - maxTime;
      //   esp_sleep_enable_timer_wakeup(timeToSleep * 1000000);
      //   esp_deep_sleep_start();
      // }

      int numberOfMinutes = floor(numberOfSeconds / 60);
      Serial.print("Minutes:");
      Serial.println(numberOfMinutes);

      if (numberOfMinutes >= 1 && numberOfMinutes <= NUM_PIXELS)
      {
        unsigned fadeTime = 500;
        for (int i = 0; i < NUM_PIXELS; i++)
        {

          if (numberOfMinutes >= i)
          {
            Serial.print("Turning on ");
            Serial.println(i);
            if (pixels[i]->getCurrentBrightness() == 0)
            {
              pixels[i]->fade(100, fadeTime);
            }
            else
            {
              pixels[i]->setBrightness(100);
            }
          }
          else
          {
            Serial.print("Turning off ");
            Serial.println(i);
            if (pixels[i]->getCurrentBrightness() == 100)
            {
              pixels[i]->fade(0, fadeTime);
            }
            else
            {
              pixels[i]->setBrightness(0);
            }
          }
        }
      }
      else
      {
        neopixel.clear();
      }
      neopixel.show();
    }
    else
    {
      Serial.print("HTTP error: ");
      Serial.println(httpResponseCode);
    }
    http.end();
  }
  else
  {
    Serial.println("WiFi not connected.  Attempting reconnection.");
    WiFi.reconnect();
  }
  delay(5000); // Wait 5 seconds before making another request
}