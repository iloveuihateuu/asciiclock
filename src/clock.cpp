#include "clock.h"
#include <string>

Timezone::Timezone(char in_differenceHours, char in_differenceMinutes, std::string in_abbreviation, std::wstring in_fullname)
  : differenceHours(in_differenceHours), differenceMinutes(in_differenceMinutes), abbreviation(in_abbreviation), fullname(in_fullname)
{}
Timezone::Timezone() {
  Timezone(0, 0, "UTC+0:00", L"London, Dublin, Lisbon, Abidjan, Accra, Dakar");
}
Clock::Clock(Timezone in_timezone)
  : timezone(in_timezone)
{
  auto now = std::chrono::system_clock::now();
  timeCurrent = std::chrono::system_clock::to_time_t(now);
  timeOfCreation = timeCurrent;
}
Clock::Clock()
{
  Clock(Timezone());
}
//  I would eat some raw steak rn
void Clock::update() {
  auto now = std::chrono::system_clock::now();
  timeCurrent = std::chrono::system_clock::to_time_t(now);
}
void Clock::setTimezone(Timezone in_timezone) {
  timezone = in_timezone;
}
//  These aren't working correctly but I'll leave it commented here if I want to fix it in the future but it probably doesn't matter since its not used
/*int Clock::getYear() {
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
  }*/
int Clock::getHours() {
  update();
  int hour = (timeCurrent / 3600) % 24;
  return hour + int(timezone.differenceHours);
}
int Clock::getMinutes() {
  update();
  int minute = (timeCurrent / 60) % 60;
  return minute + int(timezone.differenceMinutes);
}
int Clock::getSeconds() {
  update();
  int second = timeCurrent % 60;
  return second;
}
int Clock::getTimestamp() {
  update();
  return timeCurrent;
}
std::vector<Timezone> Timezone::getTimezones() {
  //  This most likely isn't the best solution and probably the timezone names aren't 100% correct but I've got enough bs in my life to bother.
  std::vector<Timezone> timezones;
  timezones.push_back(Timezone(-12, 0, "UTC-12:00", L"Baker Island, Howland Island"));
  timezones.push_back(Timezone(-11, 0, "UTC-11:00", L"Niue, Jarvis Island, Kingman Reef, Midway Atoll, Palmyra Atoll"));
  timezones.push_back(Timezone(-10, 0, "UTC-10:00", L"Honolulu, Cook Islands, Alaska, Hawaii, Johnston Atoll"));
  timezones.push_back(Timezone(-9, -30, "UTC-9:30", L"Marquesas Islands"));
  timezones.push_back(Timezone(-9, 0, "UTC-9:00", L"Anchorage, Gambier Islands, Alaska"));
  timezones.push_back(Timezone(-8, 0, "UTC-8:00", L"Los Angeles, Vancouver, Tijuana, San Francisco, Sacramento, San Jose"));
  timezones.push_back(Timezone(-7, 0, "UTC-7:00", L"Denver, Calgary, Ciudad Juárez and Edmonton"));
  timezones.push_back(Timezone(-6, 0, "UTC-6:00", L"Mexico City, Chicago, Guatemala City, Tegucigalpa, Winnipeg, San José, San Salvador"));
  timezones.push_back(Timezone(-5, 0, "UTC-5:00", L"New York City, Toronto, Havana, Lima, Bogotá, Kingston, Quito"));
  timezones.push_back(Timezone(-4, 0, "UTC-4:00", L"Santiago, Santo Domingo, Manaus, Caracas, La Paz, Halifax"));
  timezones.push_back(Timezone(-3, -30, "UTC-3:30", L"St. John's, Labrador, Newfoundland"));
  timezones.push_back(Timezone(-3, 0, "UTC-3:00", L"São Paulo, Buenos Aires, Montevideo"));
  timezones.push_back(Timezone(-2, 0, "UTC-2:00", L"Fernando de Noronha, Greenland, South Georgia, South Sandwich Islands"));
  timezones.push_back(Timezone(-1, 0, "UTC-1:00", L"Cape Verde, Azores"));
  timezones.push_back(Timezone(0, 0, "UTC+0:00", L"London, Dublin, Lisbon, Abidjan, Accra, Dakar"));
  timezones.push_back(Timezone(1, 0, "UTC+1:00", L"Paris, Berlin, Rome, Stockholm, Madrid, Warsaw, Lagos, Kinshasa, Algiers, Casablanca"));
  timezones.push_back(Timezone(2, 0, "UTC+2:00", L"Athens, Bucharest, Cairo, Helsinki, Jerusalem, Johannesburg, Khartoum, Kyiv, Riga, Sofia"));
  timezones.push_back(Timezone(3, 0, "UTC+3:00", L"Moscow, Istanbul, Riyadh, Baghdad, Addis Ababa, Doha, Nairobi, Kuwait City"));
  timezones.push_back(Timezone(3, 30, "UTC+3:30", L"Tehran"));
  timezones.push_back(Timezone(4, 0, "UTC+4:00", L"Dubai, Tbilisi, Yerevan, Baku, Samara"));
  timezones.push_back(Timezone(4, 30, "UTC+4:30", L"Kabul"));
  timezones.push_back(Timezone(5, 0, "UTC+5:00", L"Karachi, Astana, Tashkent, Yekaterinburg"));
  timezones.push_back(Timezone(5, 30, "UTC+5:30", L"Delhi, Mumbai, Colombo"));
  timezones.push_back(Timezone(5, 45, "UTC+5:45", L"Kathmandu"));
  timezones.push_back(Timezone(6, 0, "UTC+6:00", L"Dhaka, Bishkek, Omsk"));
  timezones.push_back(Timezone(6, 30, "UTC+6:30", L"Yangon"));
  timezones.push_back(Timezone(7, 0, "UTC+7:00", L"Bangkok, Jakarta, Ho Chi Minh City, Krasnoyarsk"));
  timezones.push_back(Timezone(8, 0, "UTC+8:00", L"Shanghai, Taipei, Kuala Lumpur, Singapore, Perth, Manila, Makassar, Irkutsk"));
  timezones.push_back(Timezone(8, 45, "UTC+8:45", L"Eucla"));
  timezones.push_back(Timezone(9, 0, "UTC+9:00", L"Tokyo, Seoul, Pyongyang, Jayapura, Chita"));
  timezones.push_back(Timezone(9, 30, "UTC+9:30", L"Adelaide"));
  timezones.push_back(Timezone(10, 0, "UTC+10:00", L"Melbourne, Port Moresby, Vladivostok"));
  timezones.push_back(Timezone(10, 30, "UTC+10:30", L"Lord Howe Island"));
  timezones.push_back(Timezone(11, 0, "UTC+11:00", L"Nouméa"));
  timezones.push_back(Timezone(12, 0, "UTC+12:00", L"Auckland, Suva, Petropavlovsk-Kamchatsky"));
  timezones.push_back(Timezone(12, 45, "UTC+12:45", L"Chatham Islands"));
  timezones.push_back(Timezone(13, 0, "UTC+13:00", L"Phoenix Islands, Tokelau, Samoa, Tonga"));
  timezones.push_back(Timezone(14, 0, "UTC+14:00", L"Line Islands"));
  return timezones;
}
Timer::Timer()
  : duration(0)
{
  update();
}
void Timer::update() {
  auto now = std::chrono::system_clock::now();
  timeCurrent = std::chrono::system_clock::to_time_t(now);
}
void Timer::setTimer(time_t in_duration) {
  update();
  timerSet = true;
  timerStart = timeCurrent;
  duration = in_duration;
}
bool Timer::timerDue() {
  if(!timerSet) return false;
  update();
  if(timeCurrent - timerStart >= duration) {
    timerSet = false;
    duration = 0;
    return false;
  }
  return true;
}
