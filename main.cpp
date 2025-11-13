#include "renderer.h"

using namespace std;

int main() {
  string str; 
  getline(cin, str);
  Renderer renderer;
  int x;
  while (true) {
    renderer.printStringAtCenter(str);
    renderer.printStringAtBottomRight("Press q to quit.");
    renderer.drawLine('#', Vei2(0,0), Vei2(x, 40));
    if (getch() == 'q') break;
    x++;
    renderer.update();
  }
  return 0;
}
