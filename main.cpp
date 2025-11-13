#include "renderer.h"

using namespace std;

int main() {
  string str; 
  getline(cin, str);
  Renderer renderer;
  while (true) {
    renderer.printStringAtCenter(str);
    renderer.printStringAtBottomRight("Press q to quit.");
    if (getch() == 'q') break;
  }
  return 0;
}
