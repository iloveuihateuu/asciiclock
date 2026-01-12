#include <vector>
#include <chrono>

class Timezone {
  public:
    Timezone(char in_differenceHours, char in_differenceMinutes, std::string in_abbreviation, std::wstring in_fullname)
      : differenceHours(in_differenceHours), differenceMinutes(in_differenceMinutes), abbreviation(in_abbreviation), fullname(in_fullname)
    {}
    Timezone()
    {
      Timezone(0, 0, "UTC+0:00", L"London, Dublin, Lisbon, Abidjan, Accra, Dakar");
    }
    char differenceHours;
    char differenceMinutes;
    std::string abbreviation;
    std::wstring fullname;
    static std::vector<Timezone> getTimezones();
    std::wstring getDescription();
};

class Clock {
  public:
    Clock(Timezone in_timezone)
      : timezone(in_timezone)
    {
      auto now = std::chrono::system_clock::now();
      timeCurrent = std::chrono::system_clock::to_time_t(now);
      timeOfCreation = timeCurrent;
    }
    Clock()
    {
      Clock(Timezone());
    }
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
