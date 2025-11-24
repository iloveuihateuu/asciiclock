#include "positionList.h"

class Shapes { 
  public:
    enum class Allignment {
      Left,
      Center,
      Right,
    };
  public:
    static void putAt(PositionList& list, Vei2 vec);
    static void plotLine(PositionList& list, Vei2 start, Vei2 end);
    static void plotLineAngle(PositionList& list, Vei2 start, int lenght, float angle, float xFactor);
    static void plotCircle(PositionList& list, Vei2 center, int radius);
    static Vei2 getLineAngleEndPosition(Vei2 start, int lenght, float angle, float xFactor);
    static float getHourHandAngle(int hour, int minute, int second);
    static float getMinuteHandAngle(int minute, int second);
    static float getSecondHandAngle(int second);
    static float normalizeAngle(float angle);
    static float normalizeAngle(int angle);
  private:
    static void circlePlotter(PositionList& list, Vei2 center, Vei2 point);
  public:
    static void plotEllipse(PositionList& list, Vei2 center, int radiusX, int radiusY); 
};
