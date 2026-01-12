#pragma once

#include <cmath>

template <typename T>
class Vec2 {
  public:
    Vec2()
      : x(0), y(0)
    {}
    Vec2(T inputX, T inputY)
      : x(inputX), y(inputY)
    {}
    Vec2 operator+(const Vec2 other) const {
      Vec2 result(x + other.x, y + other.y);

      return result;
    }
    Vec2 operator-(const Vec2 other) const {
      Vec2 result(x - other.x, y - other.y);

      return result;
    }
    Vec2 operator+=(const Vec2 other) {
      *this = *this + other;

      return *this;
    }
    Vec2 operator-=(const Vec2 other) {
      *this = *this - other;

      return *this;
    }
    Vec2 operator*(const int factor) const {
      Vec2 result(x * factor, y * factor);

      return result;
    }
    Vec2 operator/(const int factor) const {
      Vec2 result(x / factor, y / factor);

      return result;
    }
    bool operator==(const Vec2 other) const {
      return x == other.x && y == other.y;
    }
    bool operator!=(const Vec2 other) const {
      return !(*this == other);
    }
    Vec2 operator=(const Vec2 other) {
      if(*this != other) {
        x = other.x;
        y = other.y;
      }
      return *this;
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

using Vei2 = Vec2<int>;
using Vef2 = Vec2<float>;
using Ved2 = Vec2<double>;

