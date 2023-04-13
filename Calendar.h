#include "DailyEvent.h"
#include "TimeUtils.h"
#include <Arduino.h>

const long gmtOffsetInSeconds = -18000;

TimeUtils timeUtils(gmtOffsetInSeconds);

class Calendar {
public:
  void addEvent(const char* label, const uint8_t hour, const uint8_t minute, const uint8_t seconds, const uint8_t days) {
    if (eventCount < MAX_EVENTS) {
      events[eventCount] = DailyEvent(label, hour, minute, seconds, days);
      eventCount++;
    }
  }

  DailyEvent *getEvent(uint8_t index) {
    if (index < eventCount) {
      return &events[index];
    }
    return nullptr;
  }

  int32_t minutesToNextEvent(TimeUtils &timeUtils) {
    int32_t minMinutesToNextEvent = INT32_MAX;

    for (uint8_t i = 0; i < eventCount; i++) {
      int32_t minutesToEvent = calculateMinutesToEvent(timeUtils, events[i]);
      if (minutesToEvent < minMinutesToNextEvent) {
        minMinutesToNextEvent = minutesToEvent;
      }
    }

    return (minMinutesToNextEvent == INT32_MAX) ? -1 : minMinutesToNextEvent;
  }

private:
  static const uint8_t MAX_EVENTS = 10;
  DailyEvent events[MAX_EVENTS];
  uint8_t eventCount = 0;
  int32_t calculateMinutesToEvent(TimeUtils &timeUtils, DailyEvent &event) {
    uint8_t currentDayOfWeek = timeUtils.getDayOfWeek();
    uint8_t currentHour = timeUtils.getHour();
    uint8_t currentMinute = timeUtils.getMinute();

    for (uint8_t dayOffset = 0; dayOffset < 7; dayOffset++) {
      uint8_t dayToCheck = (currentDayOfWeek + dayOffset) % 7;
      if (event.occursOnDay(dayToCheck)) {
        int32_t minutesToEvent = (24 * 60 * dayOffset) +
                                 (60 * event.hour + event.minute) -
                                 (60 * currentHour + currentMinute);
        if (minutesToEvent > 0) {
          return minutesToEvent;
        }
      }
    }

    return INT32_MAX;
  }
};
