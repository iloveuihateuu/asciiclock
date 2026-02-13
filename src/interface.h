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
      if(io::fileExists(input.getConfigPath())) {
        int selectedTimezone;
        input.readConfig(xFactor, updateInterval, selectedTimezone);
        std::vector<Timezone> timezones = Timezone::getTimezones();
        clock.setTimezone(timezones[selectedTimezone]);
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
      Floats,
      Hybrid,
      Minimal,
      Minimaler,
      Minimalest,
      Skeleton,
      Count
    };
  private:
    void initValues();
    void initSurfaces();
    void updateSurfaces();
    void drawClockHands(int radius);
    void drawSecondHand(int radius);
    void drawMinuteHand(int radius);
    void drawHourHand(int radius);
    void drawClockBezel() const;
    void drawClockNumbers(Vei2 center, int radius, int segments, const std::vector<std::string>& symbols, float xFactor) const;
    void drawClockNumbers(Vei2 center, int radius, int segments, const std::string& symbol, float xFactor) const;
    void drawQuitMessage() const;
    void drawStyleInfo();
    void drawBackground();
    void printTime();
    void drawArrows();
    void cycleStyles(int n);
    void printTimezoneDescription(const Timezone& timezone, Vei2 pos);

    RectI getInfoRect(int width, int height);

    int screenWidth;
    int screenHeight;

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
    wchar_t centerSymbol;

    int updateInterval = 200;

    int loopCount = 0;

    Renderer renderer;
    std::vector<Surface> surfaces{};

    int styleInfoLength = 20;
    int styleInfoHeight = 4;
    Window styleInfoWindow;

    Timer showQuitTimer;
    Timer showStyleInfoTimer;
    Timer showArrowsTimer;

    bool loop = true;
};
