#include "renderer.h"

Renderer::Renderer() {
  initscr();
  cbreak();
  noecho();
}
Renderer::~Renderer() {
  endwin();
}
void Renderer::refresh() {
  clear(); 
  refresh();
}
void Renderer::turnOffDelay() {
  nodelay(stdscr, TRUE);
}
void Renderer::printStringAtCenter(std::string str) {
  int screenHeight, screenWidth;
  getmaxyx(stdscr, screenHeight, screenWidth);

  move(screenHeight/2, (screenWidth-str.size())/2);

  printw(str.c_str());
}
void Renderer::printStringAtBottomRight(std::string str) {
  int screenHeight, screenWidth;
  getmaxyx(stdscr, screenHeight, screenWidth);

  move(screenHeight - 1, screenWidth - str.size() - 1);

  printw(str.c_str());
}
void Renderer::putAt(char c, Vei2 vec)
{
  move(vec.y, vec.x);

  addch(c);
}
void Renderer::drawLine(char c, Vei2 start, Vei2 end) {
  //An basic implementation of the Bresenham line algorithm
  int deltaX = abs(end.x - start.x);
  int moveX = (start.x < end.x) ? 1 : -1;
  int deltaY = -abs(end.y - start.y);
  int moveY = (start.y < end.y) ? 1 : -1;

  int error = deltaX + deltaY;

  int x = start.x;
  int y = start.y;

  while(true) {
    if (x == end.x && y == end.y) break; 
    putAt(c, Vei2(x, y));

    if (2 * error >= deltaY) {
      error += deltaY;
      x += moveX;
    }
    if (2 * error <= deltaX) {
      error += deltaX;
      y += moveY;
    }
  }
}
int Renderer::getWidth() const {
  return getmaxx(stdscr);
}
int Renderer::getHeight() const {
  return getmaxy(stdscr);
}
