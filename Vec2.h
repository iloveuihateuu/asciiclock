#include <cmath>

template <typename T>
class _Vec2 {
  public:
    _Vec2(T inputX, T inputY)
      : x(inputX), y(inputY)
    {}
    _Vec2 operator+(const _Vec2 rhs) const {
      _Vec2 result(x + rhs.x, y + rhs.y);

      return result;
    }
    _Vec2 operator-(const _Vec2 rhs) const {
      _Vec2 result(x - rhs.x, y - rhs.y);

      return result;
    }
    _Vec2 operator*(const int factor) const {
      _Vec2 result(x * factor, y * factor);

      return result;
    }
    _Vec2 operator/(const int factor) const {
      _Vec2 result(x / factor, y / factor);

      return result;
    }
    float getLenght() const {
      float hypotenuse = sqrt(x*x + y*y);
      
      return hypotenuse;
    }
    float getLenghtSquared() const {
      float hypotenuseSquared = x*x + y*y;
      
      return hypotenuseSquared;
    }
  public:
    T x;
    T y;
};

using Vei2 = _Vec2<int>;
using Vec2 = _Vec2<float>;
