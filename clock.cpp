#include "clock.h"
#include <string>

void Clock::update() {
  auto now = std::chrono::system_clock::now();
  timeCurrent = std::chrono::system_clock::to_time_t(now);
}
void Clock::setTimezone(int inTimezone) {
  timezone = inTimezone;  
}
int Clock::getYear() {
  update();
  int year = timeCurrent / 31536000 + 1970;
  return year;
}
int Clock::getMonthNumber() {
  int month = (timeCurrent / 2592000 + 4) % 7;
  return month + 1;
}
std::string Clock::getMonth() {
  switch(getDayNumber()) {
    case(1):
      return "January";
    case(2):
      return "February";
    case(3):
      return "March";
    case(4):
      return "April";
    case(5):
      return "May";
    case(6):
      return "June";
    case(7):
      return "July";
    case(8):
      return "August";
    case(9):
      return "Semptember";
    case(10):
      return "October";
    case(11):
      return "November";
    case(12):
      return "December";
  }
  return "Unknown";
}
std::string Clock::getMonthShort() {
  std::string month = getMonth();
  return month.substr(0,3);
}
int Clock::getDayNumber() {
  int dayOfTheWeek = (timeCurrent / 86400 + 4) % 7;
  return dayOfTheWeek + 1;
}
std::string Clock::getDay() {
  switch(getDayNumber()) {
    case(1):
      return "Monday";
    case(2):
      return "Tuesday";
    case(3):
      return "Wednesday";
    case(4):
      return "Thursay";
    case(5):
      return "Friday";
    case(6):
      return "Saturday";
    case(7):
      return "Sunday";
  }
  return "Unknown";
}
std::string Clock::getDayShort() {
  std::string dayOfTheWeek = getDay();
  return dayOfTheWeek.substr(0,3);
}
int Clock::getHours() {
  update();
  int hour = ( timeCurrent / 3600 ) % 24;
  return hour + timezone;
}
int Clock::getMinutes() {
  update();
  int hour = ( timeCurrent / 60 ) % 60;
  return hour;
}
int Clock::getSeconds() {
  update();
  int hour = timeCurrent % 60;
  return hour;
}
