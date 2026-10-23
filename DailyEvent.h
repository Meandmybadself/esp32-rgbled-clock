#include <Arduino.h>

class DailyEvent {
public:
  DailyEvent(); // Add this default constructor
  DailyEvent(const char *name, uint8_t hour, uint8_t minute, uint8_t second,
             uint8_t days);
  bool occursOnDay(uint8_t day) { return (days & (1 << day)) != 0; }
  uint8_t hour;
  uint8_t minute;
  uint8_t second;

private:
  char *name;
  uint8_t days;
};