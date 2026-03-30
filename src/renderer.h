#define _XOPEN_SOURCE_EXTENDED
#include <iostream>
#include <string>
#include <cmath>

#include <locale.h>
#if defined(__APPLE__)
#include <ncursesw/ncurses.h>
#elif defined(__linux__)
#include <cursesw.h> 
#endif
#include <panel.h>

#include "surface.h"
#include "rect.h"

class Window {
  public:
    Window();
    Window(WINDOW* in_windowPointer);
    Window(WINDOW* in_windowPointer, PANEL* in_panelPointer);
    Window(RectI rect);
    ~Window();
  public:
    void resize(RectI rect);
    void refresh();
    void erase();
    void bringToTop();
    void remove();
  public:
    WINDOW* windowPointer;
    PANEL* panelPointer;

    bool alive;
};

class Renderer {
  public:
    Renderer();
    ~Renderer();
    void clear();
    void refresh();
    void turnOffDelay();

    void printStringAtCenter(const std::string& str) const;
    void printStringAtBottomRight(const std::string& str) const;
    void putAt(char c, Vei2 vec) const;
    void putAt(wchar_t c, Vei2 vec) const;
    void setPosition(Vei2 pos);
    void putStringAt(const std::string& str, Vei2 vec, Shapes::Allignment allignment) const; 
    void putStringAt(const std::wstring& str, Vei2 vec, Shapes::Allignment allignment) const; 
    void drawLine(char c, Vei2 start, Vei2 end) const;
    void drawLineSmooth(Vei2 start, Vei2 end) const;
    void drawLineAngle(char c, Vei2 start, int lenght, float angle, float xFactor) const;
    void drawLineSmoothAngle(Vei2 start, int lenght, float angle, float xFactor) const;
    void drawCircle(wchar_t c, Vei2 center, int radius) const;
  private:
    void circlePlotter(wchar_t c, Vei2 center, Vei2 point) const;
  public:
    void drawEllipse(wchar_t c, Vei2 center, int radiusX, int radiusY) const; 
    void drawShape(PositionList& list, wchar_t c);
    void drawSurface(Surface& surface, Vei2 pos, RectI clip);
    int getWidth() const;
    int getHeight() const;
    int getCenterX() const;
    int getCenterY() const;
    Vei2 getCenter() const;
    int getWidth(Window *w) const;
    int getHeight(Window *w) const;
    int getCenterX(Window *w) const;
    int getCenterY(Window *w) const;
    Vei2 getCenter(Window *w) const;

    void putStringAt(Window* w, const std::string& str, Vei2 vec, Shapes::Allignment allignment); 
    void putStringAt(Window* w, const std::wstring& str, Vei2 vec, Shapes::Allignment allignment); 

    void refreshWindow(Window* w);
};
