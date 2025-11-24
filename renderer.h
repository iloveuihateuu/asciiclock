#define _XOPEN_SOURCE_EXTENDED
#include <iostream>
#include <string>
#include <cmath>

#include <locale.h>
#include <ncursesw/ncurses.h>
#include <panel.h>

#include "surface.h"

class Renderer {
  public:
    Renderer();
    ~Renderer();
    void clear();
    void refresh();
    void turnOffDelay();

    void printStringAtCenter(std::string str) const;
    void printStringAtBottomRight(std::string str) const;
    void putAt(char c, Vei2 vec) const;
    void putAt(wchar_t c, Vei2 vec) const;
    void putStringAt(std::string str, Vei2 vec, Shapes::Allignment allignment) const;
    void drawLine(char c, Vei2 start, Vei2 end) const;
    void drawLineSmooth(Vei2 start, Vei2 end) const;
    void drawLineAngle(char c, Vei2 start, int lenght, float angle, float xFactor) const;
    void drawLineSmoothAngle(Vei2 start, int lenght, float angle, float xFactor) const;
    void drawCircle(wchar_t c, Vei2 center, int radius) const;
    void drawClockNumbers(Vei2 center, int radius, float xFactor) const;
  private:
    void circlePlotter(wchar_t c, Vei2 center, Vei2 point) const;
  public:
    void drawEllipse(wchar_t c, Vei2 center, int radiusX, int radiusY) const; 
    void drawShape(PositionList& list, wchar_t c);
    void drawSurface(Surface& surface, Vei2 pos);
    int getWidth() const;
    int getHeight() const;
    int getCenterX() const;
    int getCenterY() const;
};
