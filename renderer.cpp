#include "renderer.h"
#include <string>

Renderer::Renderer() {
  initscr();
  cbreak();
  noecho();
}
Renderer::~Renderer() {
  endwin();
}
void Renderer::refresh() {
  ::refresh();
}
void Renderer::clear() {
  ::clear();
}
void Renderer::turnOffDelay() {
  nodelay(stdscr, TRUE);
}
void Renderer::printStringAtCenter(std::string str) const {
  int screenHeight, screenWidth;
  getmaxyx(stdscr, screenHeight, screenWidth);

  move(screenHeight/2, (screenWidth-str.size())/2);

  printw(str.c_str());
}
void Renderer::printStringAtBottomRight(std::string str) const {
  int screenHeight, screenWidth;
  getmaxyx(stdscr, screenHeight, screenWidth);

  move(screenHeight - 1, screenWidth - str.size() - 1);

  printw(str.c_str());
}
void Renderer::putAt(char c, Vei2 vec) const {
  move(vec.y, vec.x);

  addch(c);
}
void Renderer::putStringAt(std::string str, Vei2 vec, Shapes::Allignment allignment) const {
  Vei2 pos(0,0);
  int deviation;
  switch(allignment) {
    case(Shapes::Allignment::Left):
      pos = vec;
      break;
    case(Shapes::Allignment::Center):
      deviation = -str.size() / 2 + 1;
      pos = vec - Vei2(deviation, 0);
      break;
    case(Shapes::Allignment::Right):
      deviation = -str.size();
      pos = vec - Vei2(deviation, 0);
      break;
  }
  move(pos.y, pos.x);

  printw(str.c_str());
}
void Renderer::drawLine(char c, Vei2 start, Vei2 end) const {
  //An basic implementation of the Bresenham line algorithm
  int deltaX = abs(end.x - start.x);
  int moveX = (start.x < end.x) ? 1 : -1;
  int deltaY = -abs(end.y - start.y);
  int moveY = (start.y < end.y) ? 1 : -1;

  int error = deltaX + deltaY;

  int x = start.x;
  int y = start.y;

  while(true) {
    putAt(c, Vei2(x,y));
    if(x == end.x && y == end.y) break; 
    int errorTwice = 2 * error;
    if(errorTwice >= deltaY) {
      error += deltaY;
      x += moveX;
    }
    if(errorTwice <= deltaX) {
      error += deltaX;
      y += moveY;
    }
  }
}
void Renderer::drawLineSmooth(Vei2 start, Vei2 end) const {
  //An basic implementation of the Bresenham line algorithm
  int deltaX = abs(end.x - start.x);
  int moveX = (start.x < end.x) ? 1 : -1;
  int deltaY = -abs(end.y - start.y);
  int moveY = (start.y < end.y) ? 1 : -1;

  char straight;
  char angled;

  if(deltaX >= deltaY) {
    straight = '|';
  }
  else {
    straight = '-';
  }
  if (start.x >= end.x) {
    angled = '\\';
  }
  else {
    angled = '/';
  }

  char c = straight;

  int error = deltaX + deltaY;

  int x = start.x;
  int y = start.y;
  
  int nMove;

  while(true) {
    putAt(c, Vei2(x,y));
    nMove = 0;
    if(x == end.x && y == end.y) break; 
    int errorTwice = 2 * error;
    if(errorTwice >= deltaY) {
      error += deltaY;
      x += moveX;
      nMove++;
    }
    if(errorTwice <= deltaX) {
      error += deltaX;
      y += moveY;
      nMove++;
    }
    if(nMove < 2) {
      c = straight;
    }
    else {
      c = angled;
    }
      
  }
}
void Renderer::drawLineAngle(char c, Vei2 start, int lenght, float angle, float xFactor) const {
  int hypotenuse = lenght;
  int opposite = sin(angle * M_PI / 180.0f) * hypotenuse;
  int adjecent = cos(angle * M_PI / 180.0f) * hypotenuse * xFactor;

  Vei2 end = start + Vei2(adjecent, opposite);

  drawLine(c, start, end);
}
void Renderer::drawLineSmoothAngle(Vei2 start, int lenght, float angle, float xFactor) const {
  int hypotenuse = lenght;
  int opposite = sin(angle * M_PI / 180.0f) * hypotenuse;
  int adjecent = cos(angle * M_PI / 180.0f) * hypotenuse * xFactor;

  Vei2 end = start + Vei2(adjecent, opposite);

  drawLineSmooth(start, end);
}
void Renderer::drawCircle(char c, Vei2 center, int radius) const {
  //An implementation of Bresehham's circle algorithm.
  int x = 0;
  int y = radius;
  int decision = 3 - 2 * radius;
  circlePlotter(c, center, Vei2(x,y));
  while(y >= x) {
    if(decision > 0) {
      y--;
      decision += 4 * (x - y) + 10;
    }
    else
      decision += 4 * x + 6;

    x++;

    circlePlotter(c, center, Vei2(x,y));
  }
}
void Renderer::circlePlotter(char c, Vei2 center, Vei2 point) const {
  putAt(c, Vei2(center.x + point.x, center.y + point.y));
  putAt(c, Vei2(center.x - point.x, center.y + point.y));
  putAt(c, Vei2(center.x + point.x, center.y - point.y));
  putAt(c, Vei2(center.x - point.x, center.y - point.y));
  putAt(c, Vei2(center.x + point.y, center.y + point.x));
  putAt(c, Vei2(center.x - point.y, center.y + point.x));
  putAt(c, Vei2(center.x + point.y, center.y - point.x));
  putAt(c, Vei2(center.x - point.y, center.y - point.x));
}
int Renderer::getWidth() const {
  return getmaxx(stdscr);
}
int Renderer::getHeight() const {
  return getmaxy(stdscr);
}
void Renderer::drawEllipse(char c, Vei2 center, int radiusX, int radiusY) const {
  //implementation of the Mid-Point Ellipse Drawing Algorithm
  float decisionX, decisionY, decisionFirst, decisionSecond, x, y;
  x = 0;
  y = radiusY;

  decisionFirst = (radiusY * radiusY) - (radiusX * radiusX * radiusY) + (0.25 * radiusX * radiusX);

  decisionX = 2 * radiusY * radiusY * x;
  decisionY = 2 * radiusX * radiusX * y;

  while(decisionX < decisionY) {
    putAt(c, Vei2(x + center.x, y + center.y));
    putAt(c, Vei2(-x + center.x, y + center.y));
    putAt(c, Vei2(x + center.x, -y + center.y));
    putAt(c, Vei2(-x + center.x, -y + center.y));

    if(decisionFirst < 0) {
      x++;
      decisionX += 2 * radiusY * radiusY;
      decisionFirst += decisionX + (radiusY * radiusY);
    }
    else {
      x++;
      y--;
      decisionX += 2 * radiusY * radiusY;
      decisionY -= 2 * radiusX * radiusX;

      decisionFirst += decisionX - decisionY + (radiusY * radiusY);
    }
  }

  decisionSecond = ((radiusY * radiusY) * ((x + 0.5f) * (x + 0.5f))) + ((radiusX * radiusX) * ((y - 1) * (y - 1))) - (radiusX * radiusX * radiusY * radiusY);
  while(y >= 0) {
    putAt(c, Vei2(x + center.x, y + center.y));
    putAt(c, Vei2(-x + center.x, y + center.y));
    putAt(c, Vei2(x + center.x, -y + center.y));
    putAt(c, Vei2(-x + center.x, -y + center.y));

    if(decisionSecond > 0) {
      y--;
      decisionY -= 2 * radiusX * radiusX;
      decisionSecond += (radiusX * radiusX) - decisionY;
    }
    else {
      y--;
      x++;
      decisionX += 2 * radiusY * radiusY;
      decisionY -= 2 * radiusX * radiusX;
      decisionSecond += decisionX - decisionY + (radiusX * radiusX);
    }
  }
}
void Renderer::drawShape(PositionList& list, char c) {
  for(auto it = list.begin(); it != list.end(); ++it) {
    putAt(c, *it);
  } 
}
void Renderer::drawClockNumbers(Vei2 center, int radius, float xFactor) const {
  float anglePerHour = 30.0f;
  for(int i = 0; i < 12; i++) {
    int hour = i + 3;
    if(hour > 12) hour -= 12;
    putStringAt(std::to_string(hour), Shapes::getLineAngleEndPosition(center, radius, anglePerHour * i, xFactor), Shapes::Allignment::Center);
  }
}
