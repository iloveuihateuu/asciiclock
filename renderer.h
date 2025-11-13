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

    void printStringAtCenter(std::string str);
    void printStringAtBottomRight(std::string str);
    void putAt(char c, Vei2 vec);
    void drawLine(char c, Vei2 start, Vei2 end);
    
    int getWidth() const;
    int getHeight() const;
};
