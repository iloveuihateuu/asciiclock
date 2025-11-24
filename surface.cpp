#include "surface.h"

void Surface::putAt(wchar_t c, Vei2 pos, int frame) {
  int index = width * pos.y + pos.x;
  data[frame - 1][index] = c;
}
void Surface::putAt(wchar_t c, Vei2 pos) {
  int index = width * pos.y + pos.x;
  data[currentFrame - 1][index] = c;
}
wchar_t Surface::valueAt(Vei2 pos, int frame) {
  int index = width * pos.y + pos.x;
  return data[frame - 1][index];
}
wchar_t Surface::valueAt(Vei2 pos) {
  int index = width * pos.y + pos.x;
  return data[currentFrame - 1][index];
}
void Surface::clear() {
  width = -1;
  height = -1;

  data.clear();
}
int Surface::getWidth() {
  return width;
}
int Surface::getHeight() {
  return height;
}
void Surface::resize(Vei2 size) {
  width = size.x;
  height = size.y;
  for(auto& frame : data) {
    frame.resize(width*height); 
  }
}
void Surface::setFrames(int inFrames) {
  data.resize(inFrames);
  frames = inFrames;
}
void Surface::advance(int n) {
  currentFrame += n;
  currentFrame = (currentFrame - 1) % frames + 1;
}
void Surface::advance() {
  advance(1);
}
