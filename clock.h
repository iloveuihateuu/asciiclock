#include <chrono>

class Clock {
  public:
    Clock(int inTimezone)
      : timezone(inTimezone)
    {
      auto now = std::chrono::system_clock::now();
      timeCurrent = std::chrono::system_clock::to_time_t(now);
      timeOfCreation = timeCurrent;
    }
    Clock()
    {
      Clock(0);
    }
    void update();
    void setTimezone(int inTimezone);

    int getYear();
    int getMonthNumber();
    std::string getMonth();
    std::string getMonthShort();
    int getDayNumber();
    std::string getDay();
    std::string getDayShort();
    int getHours();
    int getMinutes();
    int getSeconds();
  private:
    std::time_t timeOfCreation;
    std::time_t timeCurrent;

    int timezone = 0;
};
