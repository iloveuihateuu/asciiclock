#include "shapes.h"

void Shapes::plotLine(PositionList& list, Vei2 start, Vei2 end) {
  //An basic implementation of the Bresenham line algorithm
  int deltaX = abs(end.x - start.x);
  int moveX = (start.x < end.x) ? 1 : -1;
  int deltaY = -abs(end.y - start.y);
  int moveY = (start.y < end.y) ? 1 : -1;

  int error = deltaX + deltaY;

  int x = start.x;
  int y = start.y;

  while(true) {
    list.add(Vei2(x,y));
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
void Shapes::plotLineAngle(PositionList& list, Vei2 start, int lenght, float angle, float xFactor) {
  int hypotenuse = lenght;

  int opposite = sin(angle * M_PI / 180.0f) * hypotenuse;
  int adjecent = cos(angle * M_PI / 180.0f) * hypotenuse * xFactor;

  Vei2 end = start + Vei2(adjecent, opposite);
 
  plotLine(list, start, end);
}
void Shapes::plotCircle(PositionList& list, Vei2 center, int radius) {
  //An implementation of Bresehham's circle algorithm.
  int x = 0;
  int y = radius;
  int decision = 3 - 2 * radius;
  circlePlotter(list, center, Vei2(x,y));
  while(y >= x) {
    if(decision > 0) {
      y--;
      decision += 4 * (x - y) + 10;
    }
    else
      decision += 4 * x + 6;

    x++;

    circlePlotter(list, center, Vei2(x,y));
  }
}
void Shapes::circlePlotter(PositionList& list, Vei2 center, Vei2 point) {
  list.add(Vei2(center.x + point.x, center.y + point.y));
  list.add(Vei2(center.x - point.x, center.y + point.y));
  list.add(Vei2(center.x + point.x, center.y - point.y));
  list.add(Vei2(center.x - point.x, center.y - point.y));
  list.add(Vei2(center.x + point.y, center.y + point.x));
  list.add(Vei2(center.x - point.y, center.y + point.x));
  list.add(Vei2(center.x + point.y, center.y - point.x));
  list.add(Vei2(center.x - point.y, center.y - point.x));
}
void Shapes::plotEllipse(PositionList& list, Vei2 center, int radiusX, int radiusY) {
  //implementation of the Mid-Point Ellipse Drawing Algorithm
  float decisionX, decisionY, decisionFirst, decisionSecond, x, y;
  x = 0;
  y = radiusY;

  decisionFirst = (radiusY * radiusY) - (radiusX * radiusX * radiusY) + (0.25 * radiusX * radiusX);

  decisionX = 2 * radiusY * radiusY * x;
  decisionY = 2 * radiusX * radiusX * y;

  while(decisionX < decisionY) {
    list.add(Vei2(x + center.x, y + center.y));
    list.add(Vei2(-x + center.x, y + center.y));
    list.add(Vei2(x + center.x, -y + center.y));
    list.add(Vei2(-x + center.x, -y + center.y));

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
    list.add(Vei2(x + center.x, y + center.y));
    list.add(Vei2(-x + center.x, y + center.y));
    list.add(Vei2(x + center.x, -y + center.y));
    list.add(Vei2(-x + center.x, -y + center.y));

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
Vei2 Shapes::getLineAngleEndPosition(Vei2 start, int lenght, float angle, float xFactor) {
  int hypotenuse = lenght;

  int opposite = sin(angle * M_PI / 180.0f) * hypotenuse;
  int adjecent = cos(angle * M_PI / 180.0f) * hypotenuse * xFactor;

  Vei2 end = start + Vei2(adjecent, opposite);
 
  return end; 
}
float Shapes::getHourHandAngle(int hour, int minute, int second) {
  float angle = 0.0f;
  float anglePerHour = 30.0f;
  float anglePerMinute = 0.5f;
  float anglePerSecond = anglePerMinute / 60.0f;

  angle += anglePerHour * hour + anglePerMinute * minute + anglePerSecond * second;
  
  angle += 270.0f;

  while(angle > 360.0f) {
    angle-=360.0f;
  }

  return angle;
}
float Shapes::getMinuteHandAngle(int minute, int second) {
  float angle = 0.0f;
  float anglePerMinute = 6.0f;
  float anglePerSecond = anglePerMinute / 60.0f;

  angle += anglePerMinute * minute + anglePerSecond * second;
  
  angle += 270.0f;

  while(angle > 360.0f) {
    angle-=360.0f;
  }

  return angle;
}
float Shapes::getSecondHandAngle(int second) {
  float angle = 0.0f;
  float anglePerSecond = 6.0f;

  angle += anglePerSecond * second;
  
  angle += 270.0f;

  while(angle > 360.0f) {
    angle-=360.0f;
  }

  return angle;
}
float Shapes::normalizeAngle(float angle) {
  while(angle > 360.0f) {
    angle -= 360.0f;
  }
  while(angle < 0.0f) {
    angle += 360.0f;
  }
  return angle;
}
float Shapes::normalizeAngle(int angle) {
  if(angle > 360) {
    angle %= 360;
  }
  while(angle < 0) {
    angle += 360;
  }
  return angle;
}
