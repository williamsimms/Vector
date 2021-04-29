#include <ctime>
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <ostream>
#include <utility>
#include <vector>

using std::cout;
using std::endl;
using std::forward;
using std::initializer_list;
using std::move;
using std::ostream;

template <typename T>
class Vector {
  using ValueType = T;
  using PointerType = T*;
  using ConstPointer = const T*;
  using ReferenceType = T&;
  using ConstReferenceType = const T&;

 private:
  int size;
  int capacity;
  T* data;

 public:
  Vector();
  Vector(T);
  Vector(vector<T>);
  Vector(initializer_list<T>);
  Vector(const Vector&);
  Vector(Vector&&);
  ~Vector();

  void Assign();

  void PushBack(const T&);
  void PushBack(T&&);

  void PushFront(const T&);
  void PushFront(T&&);

  void PushAt(int index, const T&);
  void PushAt(int index, T&&);

  void PopFront();
  void PopBack();

  void EmplaceBack();
  void EmplaceFront();
  void EmplaceAt();

  int Size();
  int MaxSize();
  int Capacity();

  bool Empty();

  void Reserve();
  void ShrinkToFit();
  void Clear();

  T Front();
  T Back();
  T Middle();

  void Sort();
  void Reverse();

  void At();

  void Swap();

  void RemoveIf();

  void Print();

  ostream& operator<<(ostream& os, const Vector<T>& vector);
};