#include <cassert>
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
  void PushMiddle(const T&);
  void PushMiddle(T&&);
  void Insert(int index, const T& newData);
  void Insert(int index, T&& newData);
  void PopFront();
  void PopBack();
  void PopMiddle();
  void Erase(int index);

  template <typename... Args>
  void EmplaceBack(Args&&... args);

  template <typename... Args>
  void EmplaceFront(Args&&... args);

  template <typename... Args>
  void Emplace(int index, Args&&... args);

  int Size() const;
  int MaxSize() const;
  int Capacity() const;
  bool Empty() const;
  void Reserve(int sizeToReserve);
  void Resize(int desiredSize);
  void ShrinkToFit();
  void Clear();
  const T& Front() const;
  const T& Back() const;
  const T& Middle() const;
  T& Front();
  T& Back();
  T& Middle();
  void Sort();
  void Reverse();
  T& At(int index);
  const T& At(int index) const;
  void Swap(Vector<T>&);
  void Swap(T*, T*);
  int RemoveIf(bool(*function(T)));
  void Print() const;
  T* Data();
  const T* Data() const;
  void ForEach(T(*function(T, int)));
  bool Every(bool(*function(T, int)));
  bool Some(bool(*function(T, int)));
  int IndexOf(const T&);
  int LastIndexOf(const T&);
  T& Find(const T&);
  const T& Find(const T&) const;
  [[nodiscard]] int GenerateRandomIndex() const;
  [[nodiscard]] int Midpoint() const;
  [[nodiscard]] int Midpoint(int newSize) const;
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

  template <typename U>
  friend ostream& operator<<(ostream& os, const Vector<U>& vector);

  bool operator!=(const Vector<T>&);
  bool operator==(const Vector<T>&);
  bool operator<(const Vector<T>&);
  bool operator<=(const Vector<T>&);
  bool operator>(const Vector<T>&);
  bool operator>=(const Vector<T>&);

  const T& operator[](int index) const;
  T& operator[](int index);

  Vector<T>& operator=(const Vector<T>& otherVector);
  Vector<T>& operator=(Vector<T>&&);
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
Vector<T>::Vector(const std::vector<T>& fillerVector) noexcept
    : size{(int)fillerVector.size()}, capacity{size}, data{new T[capacity]} {
  for (int i = 0; i < size; i++) {
    data[i] = move(fillerVector[i]);
  }
}

template <typename T>
Vector<T>::Vector(const initializer_list<T>& initList) noexcept
    : size{(int)initList.size()}, capacity{size}, data{new T[capacity]} {
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
const T& Vector<T>::operator[](int index) const {
  assert(index >= 0);
  assert(index < size);
  return data[index];
}

template <typename T>
T& Vector<T>::operator[](int index) {
  assert(index >= 0);
  assert(index < size);
  return data[index];
}

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& otherVector) {
  if (this == &otherVector) {
    return;
  }

  delete[] data;
  this->data = new T[otherVector.size];
  this->size = otherVector.size;
  this->capacity = size;

  for (int i = 0; i < size; i++) {
    data[i] = otherVector[i];
  }

  return *this;
}

template <typename T>
Vector<T>& Vector<T>::operator=(Vector<T>&& otherVector) {
  if (this == &otherVector) {
    return;
  }

  this->data = otherVector.data;
  otherVector.data = nullptr;

  return *this;
}

template <typename T>
bool Vector<T>::operator==(const Vector<T>& otherVector) {
  if (this->size != otherVector.Size()) {
    return false;
  }

  for (int i = 0; i < size; i++) {
    if (data[i] != otherVector[i]) {
      return false;
    }
  }

  return true;
}

template <typename T>
bool Vector<T>::operator!=(const Vector<T>& otherVector) {
  return !(*this == otherVector);
}

template <typename T>
bool Vector<T>::operator<(const Vector<T>& otherVector) {
  return this->size < otherVector.Size();
}

template <typename T>
bool Vector<T>::operator<=(const Vector<T>& otherVector) {
  if (*this == otherVector) {
    return true;
  }

  if (*this < otherVector) {
    return true;
  }

  return false;
}

template <typename T>
bool Vector<T>::operator>(const Vector<T>& otherVector) {
  return this->size > otherVector.Size();
}

template <typename T>
bool Vector<T>::operator>=(const Vector<T>& otherVector) {
  if (*this == otherVector) {
    return true;
  }

  if (*this > otherVector) {
    return true;
  }

  return false;
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
bool Vector<T>::Empty() const {
  if (size == 0) {
    return true;
  }

  return false;
}

template <typename T>
T& Vector<T>::Front() {
  assert(this->size > 0);
  return data[0];
}

template <typename T>
T& Vector<T>::Back() {
  assert(this->size > 0);
  return data[size - 1];
}

template <typename T>
T& Vector<T>::Middle() {
  assert(this->size > 0);
  int midpoint = this->Midpoint();
  return data[midpoint];
}

template <typename T>
const T& Vector<T>::Front() const {
  return data[0];
}

template <typename T>
const T& Vector<T>::Back() const {
  return data[size - 1];
}

template <typename T>
const T& Vector<T>::Middle() const {
  int midpoint = this->Midpoint();
  return data[midpoint];
}

template <typename T>
void Vector<T>::Assign(const initializer_list<T>& initList) {
  for (const T& element : initList) {
    PushBack(move(element));
  }
}

template <typename T>
void Vector<T>::Assign(const std::vector<T>& list) {
  for (const T& element : list) {
    PushBack(move(element));
  }
}

template <typename T>
void Vector<T>::Assign(int count, const T& value) {
  int counter = 0;
  while (counter < count) {
    PushBack(move(value));
    counter++;
  }
}

template <typename T>
void Vector<T>::PushBack(const T& newData) {
  if (size == capacity) {
    int newCapacity = GenerateNewCapacity();
    Resize(newCapacity);
  }

  this->data[size] = newData;
  this->size++;
}

template <typename T>
void Vector<T>::PushBack(T&& newData) {
  if (size == capacity) {
    int newCapacity = GenerateNewCapacity();
    Resize(newCapacity);
  }

  this->data[size] = move(newData);
  this->size++;
}

template <typename T>
void Vector<T>::PushFront(const T& newData) {
  if (size == capacity) {
    int newCapacity = GenerateNewCapacity();
    Resize(newCapacity);
  }

  for (int i = size; i >= 0; i--) {
    data[i] = move(data[i - 1]);
  }

  data[0] = newData;
  this->size++;
}

template <typename T>
void Vector<T>::PushFront(T&& newData) {
  if (size == capacity) {
    int newCapacity = GenerateNewCapacity();
    Resize(newCapacity);
  }

  for (int i = size; i >= 0; i--) {
    data[i] = move(data[i - 1]);
  }

  data[0] = move(newData);
  this->size++;
}

template <typename T>
void Vector<T>::Insert(int index, const T& newData) {
  if (size == capacity) {
    int newCapacity = GenerateNewCapacity();
    Resize(newCapacity);
  }

  assert(index >= 0);
  assert(index < size);

  for (int i = size; i >= index; i--) {
    data[i + 1] = data[i];
  }

  data[index] = newData;
  this->size++;
}

template <typename T>
void Vector<T>::Insert(int index, T&& newData) {
  if (size == capacity) {
    int newCapacity = GenerateNewCapacity();
    Resize(newCapacity);
  }

  assert(index >= 0);
  assert(index < size);

  for (int i = size; i >= index; i--) {
    data[i + 1] = data[i];
  }

  data[index] = move(newData);
  this->size++;
}

template <typename T>
void Vector<T>::PushMiddle(const T& newData) {
  if (size == capacity) {
    int newCapacity = GenerateNewCapacity();
    Resize(newCapacity);
  }

  int midpoint = Midpoint(size + 1);

  for (int i = size; i >= midpoint; i--) {
    data[i + 1] = data[i];
  }

  data[midpoint] = newData;
  this->size++;
}

template <typename T>
void Vector<T>::PushMiddle(T&& newData) {
  if (size == capacity) {
    int newCapacity = GenerateNewCapacity();
    Resize(newCapacity);
  }

  int midpoint = Midpoint(size + 1);

  for (int i = size; i >= midpoint; i--) {
    data[i + 1] = data[i];
  }

  data[midpoint] = move(newData);
  this->size++;
}

template <typename T>
template <typename... Args>
void Vector<T>::EmplaceBack(Args&&... args) {
  if (size == capacity) {
    int newCapacity = GenerateNewCapacity();
    Resize(newCapacity);
  }

  this->data[size] = T(forward<Args>(args)...);
  this->size++;
}

template <typename T>
template <typename... Args>
void Vector<T>::EmplaceFront(Args&&... args) {
  if (size == capacity) {
    int newCapacity = GenerateNewCapacity();
    Resize(newCapacity);
  }

  for (int i = size; i >= 0; i--) {
    data[i] = move(data[i - 1]);
  }
  this->data[0] = T(forward<Args>(args)...);
  this->size++;
}

template <typename T>
template <typename... Args>
void Vector<T>::Emplace(int index, Args&&... args) {
  if (size == capacity) {
    int newCapacity = GenerateNewCapacity();
    Resize(newCapacity);
  }

  assert(index >= 0);
  assert(index < size);

  for (int i = size; i >= index; i--) {
    data[i + 1] = data[i];
  }

  data[index] = T(forward<Args>(args)...);
  this->size++;
}

template <typename T>
void Vector<T>::PopFront() {
  for (int i = 0; i < size; i++) {
    data[i] = data[i + 1];
  }

  this->size--;
}

template <typename T>
void Vector<T>::PopBack() {
  this->size--;
}

template <typename T>
void Vector<T>::PopMiddle() {
  int midpoint = Midpoint();

  for (int i = midpoint; i < size; i++) {
    data[i] = data[i + 1];
  }

  this->size--;
}

template <typename T>
void Vector<T>::Erase(int index) {
  assert(index >= 0);
  assert(index < size);

  if (index == 0) {
    PopFront();
    return;
  }

  if (index == size - 1) {
    PopBack();
    return;
  }

  for (int i = index; i < size; i++) {
    data[i] = data[i + 1];
  }

  this->size--;
}

template <typename T>
T& Vector<T>::At(int index) {
  assert(index >= 0);
  assert(index < size);
  return data[index];
}

template <typename T>
const T& Vector<T>::At(int index) const {
  assert(index >= 0);
  assert(index < size);
  return data[index];
}

template <typename T>
void Vector<T>::Resize(int desiredCapacity) {
  if (desiredCapacity == capacity) {
    return;
  }

  if (desiredCapacity > capacity) {
    T* newData = new T[desiredCapacity];

    for (int i = 0; i < size; i++) {
      newData[i] = move(data[i]);
    }

    delete[] data;
    data = newData;
    this->capacity = desiredCapacity;
  }

  if (desiredCapacity < capacity) {
    T* newData = new T[desiredCapacity];

    for (int i = 0; i < desiredCapacity; i++) {
      newData[i] = move(data[i]);
    }

    delete[] data;
    data = newData;
    this->size = desiredCapacity;
  }
}

template <typename T>
void Vector<T>::Clear() {
  if (this->capacity == 0) {
    return;
  }

  this->size = 0;
  this->Resize(0);
  delete[] data;
}

template <typename T>
void Vector<T>::ShrinkToFit() {
  if (size == capacity) {
    return;
  }

  this->Resize(this->size);
}

template <typename T>
void Vector<T>::Reserve(int amountToReserve) {
  if (amountToReserve <= capacity) {
    return;
  }

  this->Resize(amountToReserve);
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
  int currentLength = size - 1;
  int midpoint = (int)floor(currentLength / 2);
  return midpoint;
}

template <typename T>
int Vector<T>::Midpoint(int newSize) const {
  int currentLength = newSize - 1;
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
void Vector<T>::Swap(Vector<T>& otherList) {
  if (this == &otherList) {
    return;
  }

  if (otherList.Size() > this->size) {
    int initialSize = this->size;
    this->Resize(otherList.Size());

    for (int i = 0; i < otherList.Size(); i++) {
      Swap(&data[i], &otherList.data[i]);
    }

    otherList.Resize(initialSize);
  }

  if (this->size > otherList.Size()) {
    int initialSize = otherList.Size();
    otherList.Resize(initialSize);

    for (int i = 0; i < size; i++) {
      Swap(&data[i], &otherList.data[i]);
    }

    this->Resize(initialSize);
  }

  if (this->size == otherList.Size()) {
    for (int i = 0; i < size; i++) {
      Swap(&data[i], &otherList[i]);
    }
  }
}

template <typename T>
int Vector<T>::RemoveIf(bool(*function(T))) {
  for (int i = 0; i < size; i++) {
    bool shouldRemove = function(data[i]);

    if (shouldRemove) {
      for (int j = i; i < size; j++) {
        data[j] = data[j + 1];
      }

      this->size--;
    }
  }
}

template <typename T>
void Vector<T>::ForEach(T(*function(T, int))) {
  int index = 0;
  for (int i = 0; i < size; i++) {
    data[i] = function(data[i], index);
    index++;
  }
}

template <typename T>
bool Vector<T>::Every(bool(*function(T, int))) {
  int index = 0;
  for (int i = 0; i < size; i++) {
    bool every = function(data[i], index);

    if (!every) {
      return false;
    }

    index++;
  }

  return true;
}

template <typename T>
bool Vector<T>::Some(bool(*function(T, int))) {
  int index = 0;
  for (int i = 0; i < size; i++) {
    bool some = function(data[i], index);

    if (some) {
      return true;
    }

    index++;
  }
  return false;
}

template <typename T>
int Vector<T>::IndexOf(const T& dataToFind) {
  int counter = 0;
  int index = -1;

  for (int i = 0; i < size; i++) {
    if (data[i] == dataToFind) {
      index = counter;
      break;
    }

    counter++;
  }

  return index;
}

template <typename T>
int Vector<T>::LastIndexOf(const T& dataToFind) {
  int counter = 0;
  int index = -1;

  for (int i = 0; i < size; i++) {
    if (data[i] == dataToFind) {
      index = counter;
    }

    counter++;
  }

  return index;
}

template <typename T>
T& Vector<T>::Find(const T& dataToFind) {
  for (int i = 0; i < size; i++) {
    if (data[i] == dataToFind) {
      return data[i];
    }
  }
}

template <typename T>
const T& Vector<T>::Find(const T& dataToFind) const {
  for (int i = 0; i < size; i++) {
    if (data[i] == dataToFind) {
      return data[i];
    }
  }
}

template <typename T>
void Vector<T>::Print() const {
  if (this->size == 0) {
    return;
  }

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
