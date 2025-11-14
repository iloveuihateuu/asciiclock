#include <vector>

#include "Vec2.h"

class PositionList {
  public:
    class Iterator {
      public:
      std::vector<Vei2>::iterator iterator;
      Vei2 operator*() const { return *iterator; }
      Iterator& operator++() { ++iterator; return *this; }
      Iterator& operator--() { --iterator; return *this; }
      bool operator==(const Iterator& other) const { return iterator == other.iterator; }
      bool operator!=(const Iterator& other) const { return iterator != other.iterator; }
    };

    Iterator begin() { return Iterator{list.begin()}; }
    Iterator end() { return Iterator{list.end()}; }
    
    void add(Vei2 position) {
      list.push_back(position);
    }
  private:
    std::vector<Vei2> list;
};
