#include <iostream>
#include <string>

#include <ncurses.h>
#include <panel.h>

#include "Vec2.h"

class Renderer { 
  public:
    Renderer();
    ~Renderer();
    void update();
    void turnOffDelay();    

    void printStringAtCenter(std::string str) const;
    void printStringAtBottomRight(std::string str) const;
    void putAt(char c, Vei2 vec) const;
    void drawLine(char c, Vei2 start, Vei2 end) const;
    void drawCircle(char c, Vei2 center, int radius) const;
  private:
    void circlePlotter(char c, Vei2 center, Vei2 point) const;
  public:
    void drawEllipse(char c, Vei2 center, int radiusX, int radiusY) const; 
    int getWidth() const;
    int getHeight() const;
};
