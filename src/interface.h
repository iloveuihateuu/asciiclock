#include <sstream>
#include <string>

#include "renderer.h"
#include "clock.h"
#include "surface.h"
#include "input.h"

class Interface {
  public:
    Interface()
    {
      const std::string filename = "config";
      if(io::fileExists(filename)) {
        int selectedTimezone;
        values.input.readConfig(values.xFactor, selectedTimezone);
        std::vector<Timezone> timezones = Timezone::getTimezones();
        values.clock.setTimezone(timezones[selectedTimezone]);
        initSurfaces();
      }
      else {
        setup();
      }

    };
    void draw();
    void drawClock();
    void processInputs();
    void setup();
  public:
    enum class Styles {
      Basic,
      Word,
      Minimal,
      Minimalest,
      Skeleton
    };
  private:
    void initValues();
    void initSurfaces();
    void updateSurfaces();
    void drawClockHands(int radius);
    void drawSecondHand(int radius);
    void drawMinuteHand(int radius);
    void drawHourHand(int radius);
    void drawClockBezel();
    void drawClockNumbers(Vei2 center, int radius, std::vector<std::string> numberSymbols, float xFactor) const;
    void drawBackground();
    void printTime();
    void drawArrows();
    void cycleStyles();
    void printTimezoneDescription(Timezone timezone, Vei2 pos);
  private:
    std::vector<Surface> surfaces{};
    struct Values {
      Values() 
        :   showQuitFor(1), xFactor(1.0f), loop(true), showQuit(false)
      {};
      int width;
      int height;

      Clock clock{};
      io input{};

      Vei2 center;
      int clockRadius;
      //x factor is for scaling the whole clock on the x axis because the terminal characters are longer on the y axis
      float xFactor;

      Styles style = Styles::Minimal;

      wchar_t minuteHandSymbol;
      wchar_t hourHandSymbol;
      wchar_t ellipseSymbol;
      wchar_t leftArrowSymbol;
      wchar_t rightArrowSymbol;

      bool showQuit;
      int showQuitTimer; 
      const int showQuitFor;

      bool loop;
      int loopCount = 0;
    };
  private:
    Renderer renderer;
    Values values; 
};                
