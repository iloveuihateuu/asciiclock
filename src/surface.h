#pragma once
#include <vector>

#include "shapes.h"

class Surface {
  public:
    Surface(int inWidth, int inHeight, int inFrames);
    Surface();
    ~Surface() {};
    void putAt(wchar_t c, Vei2 pos, int frame);
    void putAt(wchar_t c, Vei2 pos);
    wchar_t valueAt(Vei2 pos, int frame);
    wchar_t valueAt(Vei2 pos);
    void clear();
    int getWidth();
    int getHeight();
    int getFrames();
    void resize(Vei2 size);
    void setFrames(int inFrames);
    void advance();
    void advance(int n);
    void scale(int newWidth, int newHeight);
    void scale(float factor);
    Surface getScaled(int newWidth, int newHeight);
    Surface getScaled(float factor);
  private:
    int width;
    int height;
    int frames;
    int currentFrame = 1;
    std::vector<std::vector<wchar_t>> data;
};
