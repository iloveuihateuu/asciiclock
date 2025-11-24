#include <ostream>
#include <sstream>
#include <string>

#include "renderer.h"
#include "clock.h"
#include "surface.h"
#include "input.h"

using namespace std;
int main() {
  Renderer renderer;
  renderer.turnOffDelay();

  Clock clock(1);

  Vei2 start(0,0);
  Vei2 end(10,10); 

  Vei2 center(renderer.getWidth() / 2 - 1,renderer.getHeight() / 2 - 1);

  PositionList outerEllipse;
  PositionList hourHand;
  PositionList minuteHand;
  PositionList secondHand;
  
  bool showQuit = false;
  int showQuitTimer = clock.getTimestamp();
  constexpr int showQuitFor = 1;

  wchar_t minuteHandSymbol = L':';
  wchar_t hourHandSymbol = L'#';
  wchar_t ellipseSymbol = L'█';
  ellipseSymbol = L'.';
  
  float handAngle = 0.0f;
  //x factor is for scaling the whole clock on the x axis because the terminal characters are longer on the y axis
  float xFactor = 1.0f;
  int clockRadius;
  
  Surface surface;
  
  std::string filename = "test.sch";
  Input input(filename);

  input.readSurface(surface);

  bool loop = true;
  while (loop) {
    if(renderer.getHeight() < renderer.getWidth())
    {
      clockRadius = renderer.getHeight() / 2 - 2;
    }
    else {
      clockRadius = renderer.getWidth() / 2 - 2;
    }
    //clear the shape positionLists so there is no overdraw from previous frames.
    outerEllipse.clear();
    hourHand.clear();
    minuteHand.clear();
    secondHand.clear();

    //update center in case of screen resizing.
    center = Vei2(renderer.getWidth() / 2 - 1,renderer.getHeight() / 2 - 1);
    //line start is at ellipse center
    start = center;

    //plots the points to the shapes respective positionLists.
    //Shapes::plotEllipse(outerEllipse, center, 45, 20);
    Shapes::plotEllipse(outerEllipse, center, clockRadius * xFactor, clockRadius );
    Shapes::plotLineAngle(hourHand, start, clockRadius - 10, Shapes::getHourHandAngle(clock.getHours(), clock.getMinutes(), clock.getSeconds()), xFactor);
    Shapes::plotLineAngle(minuteHand, start, clockRadius - 5, Shapes::getMinuteHandAngle(clock.getMinutes(), clock.getSeconds()), xFactor);
    //Shapes::plotLineAngle(secondHand, start, clockRadius - 5, Shapes::getSecondHandAngle(clock.getSeconds()), xFactor);
    std::ostringstream currentTime;

    currentTime << clock.getHours() << ":" << clock.getMinutes() << ":" << clock.getSeconds();

    //clear the window before rendering.
    renderer.clear();
    
    //draw the shapes from the positionLists to the window.
    //when a key that is not recognized pressed display the press q to quit message for 2 seconds
    if(showQuitTimer < clock.getTimestamp() - showQuitFor) {
      showQuit = false;
    }
    if(showQuit) renderer.printStringAtBottomRight("Press q to quit.");
    renderer.drawSurface(surface, Vei2(3,3));

    renderer.printStringAtCenter(currentTime.str());

    //renderer.drawShape(secondHand, '.');
    renderer.drawShape(minuteHand, minuteHandSymbol);
    renderer.drawLineSmoothAngle(start, clockRadius - 5, Shapes::getSecondHandAngle(clock.getSeconds()), xFactor);
    renderer.drawShape(hourHand, hourHandSymbol);

    renderer.drawClockNumbers(center, clockRadius - 2, xFactor);

    renderer.drawShape(outerEllipse, ellipseSymbol);
    
    //get inputs from user.
    switch(getch()) {
      case 'q':
        loop = false; break;
      case 'j': xFactor += 0.1f; 
                break;
      case 'k':
                xFactor -= 0.1f; 
                break;
      case 'a':
                surface.advance();
                break;
      case -1:
                break;
      default:
                showQuitTimer = clock.getTimestamp();
                showQuit = true;
                break;
    }
    //redraw the window.
    renderer.refresh();
    napms(100); 
  }
  return 0;
}
