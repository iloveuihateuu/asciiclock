#include "positionList.h"

class Shapes { 
  public:
    static void putAt(PositionList& list, Vei2 vec);
    static void plotLine(PositionList& list, Vei2 start, Vei2 end);
    static void plotCircle(PositionList& list, Vei2 center, int radius);
  private:
    static void circlePlotter(PositionList& list, Vei2 center, Vei2 point);
  public:
    static void plotEllipse(PositionList& list, Vei2 center, int radiusX, int radiusY); 
};
