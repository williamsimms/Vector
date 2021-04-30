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

 private:
  int GenerateNewCapacity() const;
  void MergeSort(T* array, int low, int high);
  void Merge(T* array, int low, int midpoint, int high);

 public:
  Vector() noexcept;
  Vector(int size) noexcept;
  Vector(int size, const T&) noexcept;
  Vector(const std::vector<T>&) noexcept;
  Vector(const initializer_list<T>&) noexcept;
  Vector(const Vector<T>&) noexcept;
  Vector(Vector&&) noexcept;
  ~Vector() noexcept;

  void Assign(const initializer_list<T>&);
  void Assign(const std::vector<T>&);
  void Assign(int count, const T& value);

  void PushBack(const T&);
  void PushBack(T&&);

  void PushFront(const T&);
  void PushFront(T&&);

  void PushAt(int index, const T&);
  void PushAt(int index, T&&);

  void PopFront();
  void PopBack();

  template <typename... Args>
  void EmplaceBack(Args&&... args);

  template <typename... Args>
  void EmplaceFront(Args&&... args);

  template <typename... Args>
  void EmplaceAt(Args&&... args);

  int Size() const;
  int MaxSize() const;
  int Capacity() const;

  bool Empty() const;

  void Reserve(int sizeToReserve);
  void ShrinkToFit();
  void Clear();
  void Resize(int desiredSize);

  const T& Front() const;
  const T& Back() const;
  const T& Middle() const;

  T& Front();
  T& Back();
  T& Middle();

  void Sort();
  void Reverse();

  T& At();
  const T& At() const;

  void Swap(const Vector&);
  void Swap(T*, T*);

  void RemoveIf(bool(*function(T)));

  void Print() const;

  void Erase(int index);

  void Insert(int index, const T& newData);
  void InsertMiddle(const T& newData);

  T* Data();
  const T* Data() const;

  void ForEach(T(*function(T)));
  bool Every(bool(*function(T)));
  bool Some(bool(*function(T)));

  [[nodiscard]] int GenerateRandomIndex() const;

  [[nodiscard]] int Midpoint() const;

  void Shuffle();

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
Vector<T>::Vector() noexcept : size{0}, capacity{0}, data{nullptr} {}

template <typename T>
Vector<T>::Vector(int size) noexcept
    : size{size}, capacity{size}, data{new T[capacity]} {}

template <typename T>
Vector<T>::Vector(int size, const T& fillerData) noexcept
    : size{size}, capacity{size}, data{new T[capacity]} {
  for (int i = 0; i < size; i++) {
    data[i] = fillerData;
  }
}

template <typename T>
Vector<T>::Vector(const std::vector<T>&) noexcept {
  //
}

template <typename T>
Vector<T>::Vector(const initializer_list<T>& initList) noexcept
    : size{initList.size()}, capacity{size}, data{new T[capacity]} {
  auto it = initList.begin();

  for (int i = 0; i < size; i++) {
    data[i] = *it;
    it++;
  }
}

template <typename T>
Vector<T>::Vector(const Vector<T>& otherList) noexcept
    : size{otherList.Size()}, capacity{size}, data{new T[capacity]} {
  for (int i = 0; i < size; i++) {
    data[i] = otherList.data[i];
  }
}

template <typename T>
Vector<T>::Vector(Vector&& otherList) noexcept
    : size{otherList.Size()}, capacity{size}, data{new T[capacity]} {
  data = otherList.data;
  otherList.data = nullptr;
}

template <typename T>
Vector<T>::~Vector() noexcept {
  if (this->capacity > 0) {
    delete[] data;
  }
}

template <typename T>
int Vector<T>::Size() const {
  return this->size;
}

template <typename T>
int Vector<T>::MaxSize() const {
  return this->capacity;
}

template <typename T>
int Vector<T>::Capacity() const {
  return this->capacity;
}

template <typename T>
void Vector<T>::PushBack(const T& newData) {
  if (size == capacity) {
    Resize();
  }
}

template <typename T>
void PushBack(T&& newData) {
  //
}

template <typename T>
void Vector<T>::Resize(int desiredCapacity) {
  if (desiredCapacity == capacity) {
    return;
  }

  if (desiredCapacity > capacity) {
    T newData = new T[desiredCapacity];

    for (int i = 0; i < size; i++) {
      newData[i] = move(data[i]);
    }

    delete[] data;
    data = newData;
    this->capacity = desiredCapacity;
  }

  if (desiredCapacity < capacity) {
    T newData = new T[desiredCapacity];

    for (int i = 0; i < desiredCapacity; i++) {
      newData[i] = move(data[i]);
    }

    delete[] data;
    data = newData;
    this->size = desiredCapacity;
  }
}

template <typename T>
int Vector<T>::GenerateNewCapacity() const {
  int currentCapacity = this->capacity;
  int newCapacity;

  if (currentCapacity == 0) {
    newCapacity = 1;
  } else if (currentCapacity > 1000) {
    newCapacity = currentCapacity + currentCapacity / 4;
  } else {
    newCapacity = currentCapacity * 2;
  }
  return newCapacity;
}

template <typename T>
[[nodiscard]] int Vector<T>::GenerateRandomIndex() const {
  srand((unsigned int)(time(nullptr)));
  int currentLengthOfIndices = size - 1;
  int randomIndex = rand() % currentLengthOfIndices;
  return randomIndex;
}

template <typename T>
void Vector<T>::Sort() {
  this->MergeSort(data, 0, size - 1);
}

template <typename T>
void Vector<T>::Reverse() {
  for (int i = 0; i < size / 2; i++) {
    Swap(&data[i], &data[size - i - 1]);
  }
}

template <typename T>
void MergeSort(T* array, int low, int high) {
  if (low < high) {
    int midpoint = (low + high) / 2;
    MergeSort(array, low, midpoint);
    MergeSort(array, midpoint + 1, high);
    MergeSort(array, low, midpoint, high);
  }
}

template <typename T>
void Vector<T>::Merge(T* array, int low, int midpoint, int high) {
  T temporaryStore[size];
  int i = low;
  int j = midpoint + 1;
  int k = 0;

  while (i <= midpoint && j <= high) {
    if (array[i] <= array[j]) {
      temporaryStore[k++] = array[i++];
    } else {
      temporaryStore[k++] = array[j++];
    }
  }

  while (i <= midpoint) {
    temporaryStore[k++] = array[i++];
  }

  while (j <= high) {
    temporaryStore[k++] = array[j++];
  }
  k--;
  while (k >= 0) {
    array[k + low] = temporaryStore[k];
    k--;
  }
}

template <typename T>
int Vector<T>::Midpoint() const {
  int currentLength = size;
  int midpoint = (int)floor(currentLength / 2);
  return midpoint;
}

template <typename T>
void Vector<T>::Shuffle() {
  int currentIndex = size;

  while (0 != currentIndex) {
    int randomIndex = GenerateRandomIndex();
    currentIndex--;
    Swap(&data[randomIndex], &data[currentIndex]);
  }
}

template <typename T>
void Vector<T>::Print() const {
  cout << "[";
  for (int i = 0; i < size; i++) {
    cout << data[i];

    if (i < (size - 1)) {
      cout << ", ";
    }
  }

  cout << "]" << endl;
}

template <typename T>
ostream& operator<<(ostream& os, const Vector<T>& vector) {
  vector.Print();
  return os;
}
