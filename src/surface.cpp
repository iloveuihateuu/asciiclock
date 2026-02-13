#include "surface.h"

Surface::Surface(int inWidth, int inHeight, int inFrames)
  : width(inWidth), height(inHeight), frames(inFrames)
{
  data.resize(frames);
  for(auto &frame : data) {
    frame.resize(width * height, L' ');
  }
}
Surface::Surface()
  : width(-1), height(-1) 
{}
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
  frames = 0;
  currentFrame = 1;

  data.clear();
}
int Surface::getWidth() {
  return width;
}
int Surface::getHeight() {
  return height;
}
int Surface::getFrames() {
  return frames;
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
void Surface::scale(int newWidth, int newHeight) {
  float stepX = float(width) / float(newWidth);
  float stepY = float(height) / float(newHeight);

  Surface temp = *this;

  clear();
  setFrames(temp.getFrames());
  resize(Vei2(newWidth, newHeight));

  int frameBeingResized = 1;
  for(auto& frame : data) {
    float posX = 0.0f;
    float posY = 0.0f;
    for(int gridPosX = 0; gridPosX < newWidth; gridPosX++) {
      posX = gridPosX * stepX;
      for(int gridPosY = 0; gridPosY < newHeight; gridPosY++) {
        posY = gridPosY * stepY;
        putAt(temp.valueAt(Vei2(std::floor(posX),std::floor(posY)), frameBeingResized),Vei2(gridPosX,gridPosY), frameBeingResized); 
      }
    }
    frameBeingResized++;
  }
}
void Surface::scale(float factor) {
  scale(width * factor, height * factor);
}
Surface Surface::getScaled(int newWidth, int newHeight) {
  Surface scaled = *this;
  scaled.scale(newWidth, newHeight);
  return scaled;
}
Surface Surface::getScaled(float factor) {
  Surface scaled = *this;
  scaled.scale(factor);
  return scaled;
}
