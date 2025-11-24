#pragma once
#include <vector>

#include "shapes.h"

class Surface {
  public:
    Surface(int in_width, int in_height)
      : width(in_width), height(in_height)
    {
      data.resize(width*height);
    }
    Surface()
      : width(-1), height(-1)
    {}
    void putAt(wchar_t c, Vei2 pos, int frame);
    void putAt(wchar_t c, Vei2 pos);
    wchar_t valueAt(Vei2 pos, int frame);
    wchar_t valueAt(Vei2 pos);
    void clear();
    int getWidth();
    int getHeight();
    void resize(Vei2 size);
    void setFrames(int inFrames);
    void advance();
    void advance(int n);
    void scale();
  private:
  private:
    int width;
    int height;
    int frames;
    int currentFrame = 1;
    std::vector<std::vector<wchar_t>>data;
};
