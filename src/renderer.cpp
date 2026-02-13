#include "renderer.h"

Window::Window()
  : alive(true)
{
  WINDOW *newWindow = newwin(0, 0, 0, 0);
  PANEL *panel = new_panel(newWindow);

  windowPointer = newWindow;
  panelPointer = panel;

  box(newWindow, 0, 0);

  top_panel(panelPointer);
  update_panels();
  doupdate();
}
Window::Window(WINDOW* in_windowPointer)
  : windowPointer(in_windowPointer), panelPointer(nullptr), alive(true)
{}
Window::Window(WINDOW* in_windowPointer, PANEL* in_panelPointer)
  : windowPointer(in_windowPointer), panelPointer(in_panelPointer), alive(true)
{}
Window::Window(RectI rect)
  : alive(true)
{
  int height = rect.bottomRight.y - rect.topLeft.y;
  int width = rect.bottomRight.x - rect.topLeft.x;
  int startx = rect.topLeft.x;
  int starty = rect.topLeft.y;

  WINDOW *newWindow = newwin(height, width, starty, startx);
  PANEL *panel = new_panel(newWindow);

  windowPointer = newWindow;
  panelPointer = panel;

  box(newWindow, 0, 0);

  top_panel(panelPointer);
  update_panels();
  doupdate();
}
Window::~Window() {
  remove();
}
void Window::resize(RectI rect) {
  if(!alive) return;
  int height = rect.bottomRight.y - rect.topLeft.y;
  int width = rect.bottomRight.x - rect.topLeft.x;
  int startx = rect.topLeft.x;
  int starty = rect.topLeft.y;

  wresize(windowPointer, height, width);
  mvwin(windowPointer, starty, startx);

  replace_panel(panelPointer, windowPointer);
}
void Window::refresh() {
  if(!alive) return;
  update_panels();
  doupdate();
}
void Window::erase() {
  if(!alive) return;
  werase(windowPointer);
}
void Window::bringToTop() {
  if(!alive) return;
  top_panel(panelPointer);
  refresh();
}
void Window::remove() {
  if(!alive) return;

  erase();

  hide_panel(panelPointer);
  del_panel(panelPointer);
  delwin(windowPointer);

  update_panels();
  doupdate();

  windowPointer = nullptr;
  panelPointer = nullptr;
  alive = false;
}

Renderer::Renderer() {
  setlocale(LC_ALL, "");
  initscr();
  raw();
  noecho();
  curs_set(0);
  keypad(stdscr, TRUE);
  turnOffDelay();

  idlok(stdscr, TRUE);
  scrollok(stdscr, FALSE);
  leaveok(stdscr, TRUE);
  nonl();
}
Renderer::~Renderer() {
  endwin();
}
void Renderer::refresh() { 
  wnoutrefresh(stdscr);
  doupdate();
}
void Renderer::clear() {
  werase(stdscr);
}
void Renderer::turnOffDelay() {
  nodelay(stdscr, TRUE);
}
void Renderer::printStringAtCenter(const std::string& str) const {
  int screenHeight, screenWidth;
  getmaxyx(stdscr, screenHeight, screenWidth);

  move(screenHeight / 2, (screenWidth-str.size()) / 2);

  printw("%s", str.c_str());
}
void Renderer::printStringAtBottomRight(const std::string& str) const {
  int screenHeight, screenWidth;
  getmaxyx(stdscr, screenHeight, screenWidth);

  move(screenHeight - 1, screenWidth - str.size() - 1);

  printw("%s", str.c_str());
}
void Renderer::putAt(char c, Vei2 vec) const {
  mvaddch(vec.y, vec.x, c);
}
void Renderer::putAt(wchar_t c, Vei2 vec) const {
  wchar_t temp[2] = {c, L'\0'}; 
  mvaddwstr(vec.y, vec.x, temp);
}
void Renderer::setPosition(Vei2 pos) {
  move(pos.y, pos.x);
} 
void Renderer::putStringAt(const std::string& str, Vei2 vec, Shapes::Allignment allignment) const {
  Vei2 pos = Shapes::getTextStartPosition(str, vec, allignment);
  mvaddstr(pos.y, pos.x, str.c_str());
}
void Renderer::putStringAt(const std::wstring& str, Vei2 vec, Shapes::Allignment allignment) const {
  Vei2 pos = Shapes::getTextStartPosition(str, vec, allignment);
  const wchar_t* c_wstr = str.c_str();
  mvaddwstr(pos.y, pos.x, c_wstr);
}
void Renderer::putStringAt(Window* w, const std::string& str, Vei2 vec, Shapes::Allignment allignment) {
  Vei2 pos = Shapes::getTextStartPosition(str, vec, allignment);
  mvwaddstr(w->windowPointer, pos.y, pos.x, str.c_str());
}
void Renderer::putStringAt(Window* w, const std::wstring& str, Vei2 vec, Shapes::Allignment allignment) {
  Vei2 pos = Shapes::getTextStartPosition(str, vec, allignment);
  const wchar_t* c_wstr = str.c_str();
  mvwaddwstr(w->windowPointer, pos.y, pos.x, c_wstr);
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
  int deltaX = end.x - start.x;
  int moveX = (start.x < end.x) ? 1 : -1;
  int deltaY = end.y - start.y;
  int moveY = (start.y < end.y) ? 1 : -1;

  int angle = atan2(deltaY, deltaX) * 180.0f / M_PI;
  angle = Shapes::normalizeAngle(angle);

  wchar_t primary;
  wchar_t secondary;

  if(angle >= 0 && angle < 45) {
    primary = L'_';
    secondary = L'\\';
  }
  if(angle >= 45 && angle < 90) {
    primary = L'│';
    secondary = L'\\';
  }
  if(angle >= 90 && angle < 135) {
    primary = L'│';
    secondary = L'/';
  }
  if(angle >= 135 && angle < 180) {
    primary = L'_';
    secondary = L'/';
  }
  if(angle >= 180 && angle < 225) {
    primary = L'‾';
    secondary = L'\\';
  }
  if(angle >= 225 && angle < 270) {
    primary = L'│';
    secondary = L'\\';
  }
  if(angle >= 270 && angle < 315) {
    primary = L'│';
    secondary = L'/';
  }
  if(angle >= 315 && angle <= 360) {
    primary = L'‾';
    secondary = L'/';
  }

  deltaX = abs(deltaX);
  deltaY = -abs(deltaY);

  wchar_t c = primary;

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
      c = primary;
    }
    else {
      c = secondary;
    }
  }
}
void Renderer::drawLineAngle(char c, Vei2 start, int lenght, float angle, float xFactor) const {
  angle = Shapes::normalizeAngle(angle);
  int hypotenuse = lenght;
  int opposite = sin(angle * M_PI / 180.0f) * hypotenuse;
  int adjecent = cos(angle * M_PI / 180.0f) * hypotenuse * xFactor;

  Vei2 end = start + Vei2(adjecent, opposite);

  drawLine(c, start, end);
}
void Renderer::drawLineSmoothAngle(Vei2 start, int lenght, float angle, float xFactor) const {
  angle = Shapes::normalizeAngle(angle);
  int hypotenuse = lenght;
  int opposite = sin(angle * M_PI / 180.0f) * hypotenuse;
  int adjecent = cos(angle * M_PI / 180.0f) * hypotenuse * xFactor;

  Vei2 end = start + Vei2(adjecent, opposite);

  drawLineSmooth(start, end); 
}
void Renderer::drawCircle(wchar_t c, Vei2 center, int radius) const {
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
void Renderer::circlePlotter(wchar_t c, Vei2 center, Vei2 point) const {
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
int Renderer::getCenterX() const {
  return getmaxx(stdscr) / 2;
}
int Renderer::getCenterY() const {
  return getmaxy(stdscr) / 2;
}
Vei2 Renderer::getCenter() const {
  return Vei2(getmaxx(stdscr) / 2, getmaxy(stdscr) / 2);
}
int Renderer::getWidth(Window *w) const {
  return getmaxx(w->windowPointer);
}
int Renderer::getHeight(Window *w) const {
  return getmaxy(w->windowPointer);
}
int Renderer::getCenterX(Window *w) const {
  return getmaxx(w->windowPointer) / 2;
}
int Renderer::getCenterY(Window *w) const {
  return getmaxy(w->windowPointer) / 2;
}
Vei2 Renderer::getCenter(Window *w) const {
  return Vei2(getmaxx(w->windowPointer) / 2, getmaxy(w->windowPointer) / 2);
}
void Renderer::drawEllipse(wchar_t c, Vei2 center, int radiusX, int radiusY) const {
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
void Renderer::drawShape(PositionList& list, wchar_t c) {
  for(auto it = list.begin(); it != list.end(); ++it) {
    putAt(c, *it);
  } 
}
void Renderer::drawSurface(Surface& surface, Vei2 pos, RectI clip) {
  int surfaceWidth = surface.getWidth();
  int surfaceHeight = surface.getHeight();

  Vei2 halfSurface = Vei2(surfaceWidth, surfaceHeight) / 2;
  RectI surfaceArea(pos - halfSurface, pos + halfSurface);

  //these are surface coordinates
  Vei2 start{0, 0};
  Vei2 end{surfaceWidth, surfaceHeight};

  if(surfaceArea.topLeft.x < clip.topLeft.x) {
    start -= Vei2(surfaceArea.topLeft.x - clip.topLeft.x, 0);
  }
  if(surfaceArea.topLeft.y < clip.topLeft.y) {
    start -= Vei2(0, surfaceArea.topLeft.y - clip.topLeft.y);
  }
  if(surfaceArea.bottomRight.x > clip.bottomRight.x) {
    end -= Vei2(surfaceArea.bottomRight.x-clip.bottomRight.x, 0);
  }
  if(surfaceArea.bottomRight.y > clip.bottomRight.y) {
    end -= Vei2(0, surfaceArea.bottomRight.y-clip.bottomRight.y);
  }

  for(int x = start.x; x < end.x; x++) {
    for(int y = start.y; y < end.y; y++) {
      Vei2 surfacePos(x,y);
      Vei2 screenPos = surfacePos + Vei2(pos.x, pos.y) - halfSurface;
      wchar_t value = surface.valueAt(surfacePos);
      if(value != L' ') {
        putAt(value, screenPos);
      }
    }
  }
}
