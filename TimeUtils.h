#include "wifi-credentials.h"
#include <Arduino.h>
#include <TimeLib.h>
#include <WiFi.h>
#include <time.h>

class TimeUtils {
public:
  TimeUtils(int gmtOffsetSeconds) { this->gmtOffset_sec = gmtOffsetSeconds; }
  void syncTime() {
    // Connect to Wi-Fi
    Serial.println("Connecting to Wi-Fi");
    WiFi.begin(AP_SSID, AP_PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
      delay(1000);
    }
    Serial.println("Connected to Wi-Fi");
    configTime(this->gmtOffset_sec, 0, "pool.ntp.org");
    delay(1000);

    // // Disconnect from Wi-Fi
    // Serial.println("Disconnecting from Wi-Fi");
    // WiFi.disconnect(true);
    // WiFi.mode(WIFI_OFF);
  }

  bool isWeekend() {
    time_t now;
    struct tm timeinfo;
    time(&now);
    localtime_r(&now, &timeinfo);

    return (timeinfo.tm_wday == 0 || timeinfo.tm_wday == 6);
  }

  int getHour() {
    time_t now;
    struct tm timeinfo;
    time(&now);
    localtime_r(&now, &timeinfo);

    return timeinfo.tm_hour;
  }

  int getMinute() {
    time_t now;
    struct tm timeinfo;
    time(&now);
    localtime_r(&now, &timeinfo);

    return timeinfo.tm_min;
  }

  uint8_t getDayOfWeek() {
    time_t now;
    struct tm timeinfo;
    time(&now);
    localtime_r(&now, &timeinfo);

    return timeinfo.tm_wday;
  }`

  void printLocalTime() {
    // struct tm timeinfo;
    // // This reaches out to a server to sync time.
    // // if (!getLocalTime(&timeinfo)) {
    // //   Serial.println("Failed to obtain time");
    // //   return;
    // // }
    // Serial.println("Local time: ");
    // Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");

    time_t t = now();
    // hour(t);    // returns the hour for the given time t
    // minute(t);  // returns the minute for the given time t
    // second(t);  // returns the second for the given time t
    // day(t);     // the day for the given time t
    // weekday(t); // day of the week for the given time t
    // month(t);   // the month for the given time t
    // year(t);

    // Serial.print(hour(t));
    // Serial.print(":");
    // Serial.print(minute(t));
    // Serial.print(":");
    // Serial.print(second(t));
    // Serial.print(" ");
    // Serial.print(day(t));
    // Serial.print("/");
    // Serial.print(month(t));
    // Serial.print("/");
    // Serial.print(year(t));
    // Serial.print(" ");
    // Serial.println(weekday(t));
  }

private:
  int gmtOffset_sec;
  int daylightOffset_sec;
};