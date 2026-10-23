#include "DailyEvent.h"

DailyEvent::DailyEvent()
    : name(nullptr), hour(0), minute(0), second(0), days(0) {}

DailyEvent::DailyEvent(const char *name, uint8_t hour, uint8_t minute,
                       uint8_t second, uint8_t days)
    : name(strdup(name)), hour(hour), minute(minute), second(second),
      days(days) {}
