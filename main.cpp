#include <ostream>
#include <sstream>

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

  PositionList outerEllipse;
  PositionList hourHand;
  PositionList minuteHand;
  PositionList secondHand;
  
  float handAngle = 0.0f;
  
  //x factor is for scaling the whole clock on the x axis because the terminal characters are longer on the y axis
  float xFactor = 1.0f;

  int clockRadius = renderer.getHeight() / 2 - 2;

  bool loop = true;
  while (loop) {
    clockRadius = renderer.getHeight() / 2 - 2;
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
    //Shapes::plotLineAngle(minuteHand, start, clockRadius - 5, Shapes::getMinuteHandAngle(clock.getMinutes(), clock.getSeconds()), xFactor);
    Shapes::plotLineAngle(secondHand, start, clockRadius - 5, Shapes::getSecondHandAngle(clock.getSeconds()), xFactor);

    handAngle+=0.1f;
    
    std::ostringstream currentTime;

    currentTime << clock.getHours() << ":" << clock.getMinutes() << ":" << clock.getSeconds();

    //clear the window before rendering.
    renderer.clear();

    //draw the shapes from the positionLists to the window.
    renderer.printStringAtBottomRight("Press q to quit.");

    renderer.printStringAtCenter(currentTime.str());

    renderer.drawShape(secondHand, '.');
    //renderer.drawShape(minuteHand, ':');
    renderer.drawLineSmoothAngle(start, clockRadius - 5, Shapes::getMinuteHandAngle(clock.getMinutes(), clock.getSeconds()), xFactor);
    renderer.drawShape(hourHand, '#');
    
    renderer.drawClockNumbers(center, clockRadius - 2, xFactor);

    renderer.drawShape(outerEllipse, '#');

    //get inputs from user.
    switch(getch()) {
      case 'q':
        loop = false; break;
      case 'j': xFactor += 0.1f; 
        break;
      case 'k':
        xFactor -= 0.1f; 
        break;
    }
    //redraw the window.
    renderer.refresh();
    napms(100); 
  }
  return 0;
}
