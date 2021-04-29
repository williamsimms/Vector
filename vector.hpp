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
using std::vector;

template <typename Vector>
class VectorIterator {
 public:
  using ValueType = typename Vector::ValueType;
  using PointerType = ValueType*;
  using ReferenceType = ValueType&;

  explicit VectorIterator(PointerType ptr) : data{ptr} {}

 private:
  PointerType data;

 public:
  VectorIterator& operator++() noexcept {
    data++;
    return *this;
  }

  VectorIterator operator++(int) noexcept {
    VectorIterator iterator(*this);
    ++data;
    return iterator;
  }

  VectorIterator& operator--() noexcept {
    --data;
    return *this;
  }

  VectorIterator operator--(int) noexcept {
    VectorIterator iterator(*this);
    --data;
    return iterator;
  }

  ReferenceType operator[](int index) { return *(data + index); }

  PointerType operator->() const { return data; }

  ReferenceType operator*() const { return *data; }

  bool operator==(const VectorIterator& other) const {
    return data == other.data;
  }

  bool operator!=(const VectorIterator& other) const {
    return !(data == other.data);
  }

  operator VectorIterator<const VectorIterator>() const {
    return VectorIterator<const VectorIterator>(data);
  }
};

template <typename Vector>
class ReverseVectorIterator {
 public:
  using ValueType = typename Vector::ValueType;
  using PointerType = ValueType*;
  using ReferenceType = ValueType&;

  explicit ReverseVectorIterator(PointerType ptr) : data{ptr} {}

 private:
  PointerType data;

 public:
  ReverseVectorIterator& operator++() noexcept {
    data--;
    return *this;
  }

  ReverseVectorIterator operator++(int) noexcept {
    ReverseVectorIterator iterator(*this);
    --data;
    return iterator;
  }

  ReverseVectorIterator& operator--() noexcept {
    ++data;
    return *this;
  }

  ReverseVectorIterator operator--(int) noexcept {
    ReverseVectorIterator iterator(*this);
    ++data;
    return iterator;
  }

  ReferenceType operator[](int index) { return *(data - index); }

  PointerType operator->() const { return data; }

  ReferenceType operator*() const { return *data; }

  bool operator==(const ReverseVectorIterator& other) const {
    return data == other.data;
  }

  bool operator!=(const ReverseVectorIterator& other) const {
    return !(data == other.data);
  }

  operator ReverseVectorIterator<const ReverseVectorIterator>() const {
    return ReverseVectorIterator<const ReverseVectorIterator>(data);
  }
};

template <typename T>
class Vector {
  using ValueType = T;
  using PointerType = T*;
  using ConstPointer = const T*;
  using ReferenceType = T&;
  using ConstReferenceType = const T&;
  using Iterator = VectorIterator<Vector<T>>;
  using ConstIterator = VectorIterator<const Vector<T>>;
  using ReverseIterator = ReverseVectorIterator<Vector<T>>;
  using ConstReverseIterator = ReverseVectorIterator<const Vector<T>>;

 private:
  int size;
  int capacity;
  T* data;

 public:
  Vector() noexcept;
  Vector(T fillerData) noexcept;
  Vector(int size) noexcept;
  Vector(int size, T fillerData) noexcept;
  Vector(vector<T>) noexcept;
  Vector(initializer_list<T>) noexcept;
  Vector(const Vector&) noexcept;
  Vector(Vector&&) noexcept;
  ~Vector() noexcept;

  void Assign(const initializer_list<T>&);
  void Assign(const vector<T>&);
  void Assign(int count, const T& value);

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

  int Size() const;
  int MaxSize() const;
  int Capacity() const;

  bool Empty() const;

  void Reserve();
  void ShrinkToFit();
  void Clear();

  T Front() const;
  T Back() const;
  T Middle() const;

  void Sort();
  void Reverse();

  void At() const;

  void Swap();

  void RemoveIf();

  void Print() const;

  T* Data();
  const T* Data() const;

  Iterator begin() {
    Iterator it(data);
    return it;
  }

  Iterator end() {
    Iterator it(data + size);
    return it;
  }

  ConstIterator cbegin() {
    ConstIterator it(data);
    return it;
  }

  ConstIterator cend() {
    ConstIterator it(data + size);
    return it;
  }

  ReverseIterator rbegin() {
    ReverseIterator it(data + size);
    return it;
  }

  ReverseIterator rend() {
    ReverseIterator it(data);
    return it;
  }

  ConstReverseIterator crbegin() {
    ConstReverseIterator it(data + size);
    return it;
  }

  ConstReverseIterator crend() {
    ConstReverseIterator it(data);
    return it;
  }

  friend ostream& operator<<(ostream& os, const Vector<T>& vector);

  bool operator!=(const Vector<T>&);
  bool operator==(const Vector<T>&);
  bool operator<(const Vector<T>&);
  bool operator>(const Vector<T>&);
  auto operator<=>(const Vector<T>) const;

  const T& operator[](int index) const;
  T& operator[](int index);

  Vector& operator=(const Vector<T>& otherVector);
  Vector& operator=(Vector<T>&&);
};

template <typename T>
ostream& operator<<(ostream& os, const Vector<T>& vector) {
  vector.Print();
  return os;
}
