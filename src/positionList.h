#include <vector>

#include "vec2.h"

class PositionList {
  public:
    Vei2& operator[](size_t index) {
      return list[index];
    }

    class Iterator {
      public:
        Iterator(std::vector<Vei2>::iterator inIterator)
          : iterator(inIterator)
        {}
        Vei2 operator*() const { return *iterator; }
        Iterator& operator++() { ++iterator; return *this; }
        Iterator& operator--() { --iterator; return *this; }
        bool operator==(const Iterator& other) const { return iterator == other.iterator; }
        bool operator!=(const Iterator& other) const { return iterator != other.iterator; }
      private:
        std::vector<Vei2>::iterator iterator;
    };
    
    Iterator begin() { return Iterator{ list.begin() }; }
    Iterator end() { return Iterator{ list.end() }; }
    
  public:
    void clear() {
      list.clear();
    }
    void add(Vei2 position) {
      list.push_back(position);
    }
    size_t size() {
      return list.size();
    }
  private:
    std::vector<Vei2> list;
};
