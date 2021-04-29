#include <ctime>
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <utility>
#include <vector>

using std::cout;
using std::endl;
using std::forward;
using std::initializer_list;
using std::move;

template <typename T>
class Vector {
  using ValueType = T;
  using PointerType = T*;
  using ReferenceType = T&;

 public:
  Vector();
  Vector(initializer_list<T>);
  Vector(const Vector&);
  Vector(Vector&&);
  ~Vector();

  void PushBack(const T&);
  void PushBack(T&&);
};