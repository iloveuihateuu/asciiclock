#include "renderer.h"
#include "clock.h"

using namespace std;
int main() {
  Renderer renderer;
  renderer.turnOffDelay();
  
  Clock clock(1);

  Vei2 start(0,0);
  Vei2 end(10,10); 
  
  Vei2 center(renderer.getWidth() / 2 - 1,renderer.getHeight() / 2 - 1);

  PositionList ellipse;
  PositionList line;
  
  cout << clock.getYear() << " " << clock.getMonthShort() << " " << clock.getDayShort() << " " << clock.getHours() << ":" << clock.getMinutes() << ":" << clock.getSeconds() << endl;

  bool loop = true;
  while (loop) {
    //clear the shape positionLists so there is no overdraw from previous frames.
    ellipse.clear();
    line.clear();
    
    //update center in case of screen resizing.
    center = Vei2(renderer.getWidth() / 2 - 1,renderer.getHeight() / 2 - 1);
    //line start is at ellipse center
    start = center;
    
    //plots the points to the shapes respective positionLists.
    Shapes::plotEllipse(ellipse, center, 45, 20);
    Shapes::plotLine(line, start, end);
    
    //clear the window before rendering.
    renderer.clear();
    
    renderer.printStringAtCenter("Hello!");
    renderer.printStringAtBottomRight("Press q to quit.");

    //draw the shapes from the positionLists to the window.
    renderer.drawShape(ellipse, '#');
    renderer.drawShape(line, '#');
    
    //get inputs from user.
    switch(getch()) {
      case 'q':
        loop = false;
        break;
      case 'h':
        if(end.x > 0) {
          end.x--;
        }
        break;
      case 'l':
        if(end.x < renderer.getWidth()) {
          end.x++;
        }
        break;
      case 'k':
        if(end.y > 0) {
          end.y--;
        }
        break;
      case 'j':
        if(end.y < renderer.getHeight()) {
          end.y++;
        }
        break;
      case 'H':
        if(start.x > 0) {
          start.x--;
        }
        break;
      case 'L':
        if(start.x < renderer.getWidth()) {
          start.x++;
        }
        break;
      case 'K':
        if(start.y > 0) {
          start.y--;
        }
        break;
      case 'J':
        if(start.y < renderer.getHeight()) {
          start.y++;
        }
        break;
    }
    //redraw the window.
    renderer.refresh();
  }
  return 0;
}
