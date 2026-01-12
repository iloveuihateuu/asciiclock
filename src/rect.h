#pragma once

#include "vec2.h"

template <typename T>
class Rect {
  public:
    Rect(Vec2<T> inTopLeft, Vec2<T> inBottomRight)
      : topLeft(inTopLeft), bottomRight(inBottomRight)
    {}
  public:
    Vec2<T> topLeft;
    Vec2<T> bottomRight;
};

using RectI = Rect<int>;
using RectF = Rect<float>;
using RectD = Rect<double>;
