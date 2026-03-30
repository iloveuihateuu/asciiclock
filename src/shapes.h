#include <vector>
#include <string>

#include "vec2.h"

class PositionList {
  public:
    Vei2& operator[](size_t index);
    class Iterator {
      public:
        Iterator(std::vector<Vei2>::iterator inIterator);
        Vei2 operator*() const;
        Iterator& operator++();
        Iterator& operator--();
        bool operator==(const Iterator& other) const;
        bool operator!=(const Iterator& other) const;
      private:
        std::vector<Vei2>::iterator iterator;
    };
    Iterator begin();
    Iterator end();
  public:
    void clear();
    void add(Vei2 position);
    size_t size();
  private:
    std::vector<Vei2> list;
};

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
    static Vei2 getTextStartPosition(const std::string& str, Vei2 vec, Shapes::Allignment allignment);
    static Vei2 getTextStartPosition(const std::wstring& str, Vei2 vec, Shapes::Allignment allignment);
  private:
    static void circlePlotter(PositionList& list, Vei2 center, Vei2 point);
  public:
    static void plotEllipse(PositionList& list, Vei2 center, int radiusX, int radiusY); 
};
