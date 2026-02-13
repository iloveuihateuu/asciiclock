#include <vector>
#include <chrono>

class Timezone {
  public:
    Timezone(char in_differenceHours, char in_differenceMinutes, std::string in_abbreviation, std::wstring in_fullname);
    Timezone();
    char differenceHours;
    char differenceMinutes;
    std::string abbreviation;
    std::wstring fullname;
    static std::vector<Timezone> getTimezones();
    std::wstring getDescription();
};

class Clock {
  public:
    Clock(Timezone in_timezone);
    Clock();
    void update();
    void setTimezone(Timezone in_timezone);
    /*  These aren't working
    int getYear();   
    int getMonthNumber();
    std::string getMonth();
    std::string getMonthShort();
    int getDayNumber();
    std::string getDay();
    std::string getDayShort();
    */
    int getHours();
    int getMinutes();
    int getSeconds();
    int getTimestamp();
  private:
    std::time_t timeOfCreation;
    std::time_t timeCurrent;

    Timezone timezone;
};

class Timer {
  public:
    Timer();
    void update();
    void setTimer(time_t in_duration);
    bool timerDue();
  private:
    std::time_t timerStart;
    std::time_t timeCurrent;

    std::time_t duration;

    bool timerSet = false;
};
