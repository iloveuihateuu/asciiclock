#include "renderer.h"

using namespace std;

int main() {
  string str; 
  cout << "Write text: " << endl; 
  //getline(cin, str);
  str = "Hello World!";
  Renderer renderer;
  Vei2 start(0,0);
  Vei2 end(10,10); 

  bool loop = true;
  while (loop) {
    Vei2 center(renderer.getWidth() / 2 - 1,renderer.getHeight() / 2 - 1);
    
    start = center;
    
    renderer.printStringAtCenter(str);
    renderer.printStringAtBottomRight("Press q to quit.");
    renderer.drawLine('#', start, end);
    renderer.drawEllipse('#', center, 40, 20);
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
    renderer.update();
  }
  return 0;
}
