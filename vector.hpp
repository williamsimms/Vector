#ifndef VECTOR_H
#define VECTOR_H

#include <cassert>
#include <cmath>
#include <ctime>
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <ostream>
#include <utility>
#include <vector>

#include "reverseVectorIterator.hpp"
#include "vectorIterator.hpp"

template <typename T>
class Vector {
 public:
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
  int Partition(T* array, int low, int high);
  void QuickSort(T* array, int low, int high);
  int BSearch(T* array, const T& target, int left, int right);

 public:
  Vector() noexcept;
  Vector(int size) noexcept;
  Vector(int size, const T&) noexcept;
  Vector(const std::vector<T>&) noexcept;
  Vector(const std::initializer_list<T>&) noexcept;
  Vector(const Vector<T>&) noexcept;
  Vector(Vector&&) noexcept;
  ~Vector() noexcept;

  void Assign(const std::initializer_list<T>&);
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
  int FreeCapacity() const;
  bool Empty() const;
  void Reserve(int sizeToReserve);
  void Resize(int desiredSize);
  void ShrinkToFit();
  int GenerateNewCapacity() const;
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
  int RemoveIf(bool (*function)(const T&));
  bool RemoveIndexIf(int index, bool (*function)(const T&));
  void Print() const;
  T* Data();
  const T* Data() const;
  void ForEach(T (*function)(const T&, int));
  bool Every(bool (*function)(const T&, int));
  bool Any(bool (*function)(const T&, int));
  int IndexOf(const T&);
  int LastIndexOf(const T&);
  T* Find(const T&) const;
  T* Find(bool (*function)(const T&, int)) const;
  T* FindLast(const T&) const;
  T* FindLast(bool (*function)(const T&, int)) const;
  [[nodiscard]] int GenerateRandomIndex() const;
  [[nodiscard]] int Midpoint() const;
  [[nodiscard]] int Midpoint(int newSize) const;
  void Shuffle();
  void Concat(const Vector<T>&);
  void Concat(Vector<T>&&);
  int BinarySeach(const T&);

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
  friend std::ostream& operator<<(std::ostream& os, const Vector<U>& vector);

  bool operator!=(const Vector<T>&) const;
  bool operator==(const Vector<T>&) const;
  bool operator<(const Vector<T>&) const;
  bool operator<=(const Vector<T>&) const;
  bool operator>(const Vector<T>&) const;
  bool operator>=(const Vector<T>&) const;

  const T& operator[](int index) const;
  T& operator[](int index);

  Vector<T>& operator=(const Vector<T>& otherVector) noexcept;
  Vector<T>& operator=(Vector<T>&& otherVector) noexcept;
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
    data[i] = std::move(fillerVector[i]);
  }
}

template <typename T>
Vector<T>::Vector(const std::initializer_list<T>& initList) noexcept
    : size{static_cast<int>(initList.size())},
      capacity{size},
      data{new T[capacity]} {
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
Vector<T>::Vector(Vector<T>&& otherList) noexcept
    : size{otherList.Size()}, capacity{otherList.Capacity()} {
  this->data = otherList.data;
  otherList.data = nullptr;
  otherList.capacity = 0;
  otherList.size = 0;
}

template <typename T>
Vector<T>::~Vector() noexcept {
  if (this->capacity > 0) {
    delete[] data;
    data = nullptr;
    this->capacity = 0;
    this->size = 0;
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
Vector<T>& Vector<T>::operator=(const Vector<T>& otherVector) noexcept {
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
Vector<T>& Vector<T>::operator=(Vector<T>&& otherVector) noexcept {
  if (this == &otherVector) {
    return;
  }

  this->Clear();
  this->data = otherVector.data;
  this->size = otherVector.size;
  this->capacity = otherVector.capacity;
  otherVector.data = nullptr;
  otherVector.capacity = 0;
  otherVector.size = 0;

  return *this;
}

template <typename T>
bool Vector<T>::operator==(const Vector<T>& otherVector) const {
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
bool Vector<T>::operator!=(const Vector<T>& otherVector) const {
  return !(*this == otherVector);
}

template <typename T>
bool Vector<T>::operator<(const Vector<T>& otherVector) const {
  return this->size < otherVector.Size();
}

template <typename T>
bool Vector<T>::operator<=(const Vector<T>& otherVector) const {
  if (*this == &otherVector) {
    return true;
  }

  if (this->size <= otherVector.Size()) {
    return true;
  }

  return false;
}

template <typename T>
bool Vector<T>::operator>(const Vector<T>& otherVector) const {
  return this->size > otherVector.Size();
}

template <typename T>
bool Vector<T>::operator>=(const Vector<T>& otherVector) const {
  if (*this == &otherVector) {
    return true;
  }

  if (this->size >= otherVector.Size()) {
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
int Vector<T>::FreeCapacity() const {
  return this->capacity - this->size;
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
  assert(size > 0);
  return data[0];
}

template <typename T>
const T& Vector<T>::Back() const {
  assert(size > 0);
  return data[size - 1];
}

template <typename T>
const T& Vector<T>::Middle() const {
  assert(size > 0);
  int midpoint = this->Midpoint();
  return data[midpoint];
}

template <typename T>
T* Vector<T>::Data() {
  return data;
}

template <typename T>
const T* Vector<T>::Data() const {
  return data;
}

template <typename T>
void Vector<T>::Assign(const std::initializer_list<T>& initList) {
  for (const T& element : initList) {
    PushBack(std::move(element));
  }
}

template <typename T>
void Vector<T>::Assign(const std::vector<T>& list) {
  for (const T& element : list) {
    PushBack(std::move(element));
  }
}

template <typename T>
void Vector<T>::Assign(int count, const T& value) {
  int counter = 0;
  while (counter < count) {
    PushBack(std::move(value));
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

  this->data[size] = std::move(newData);
  this->size++;
}

template <typename T>
void Vector<T>::PushFront(const T& newData) {
  if (size == capacity) {
    int newCapacity = GenerateNewCapacity();
    Resize(newCapacity);
  }

  for (int i = size; i >= 0; i--) {
    data[i] = std::move(data[i - 1]);
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
    data[i] = std::move(data[i - 1]);
  }

  data[0] = std::move(newData);
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

  data[index] = std::move(newData);
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

  data[midpoint] = std::move(newData);
  this->size++;
}

template <typename T>
template <typename... Args>
void Vector<T>::EmplaceBack(Args&&... args) {
  if (size == capacity) {
    int newCapacity = GenerateNewCapacity();
    Resize(newCapacity);
  }

  this->data[size] = T(std::forward<Args>(args)...);
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
    data[i] = std::move(data[i - 1]);
  }
  this->data[0] = T(std::forward<Args>(args)...);
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

  data[index] = T(std::forward<Args>(args)...);
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
      newData[i] = std::move(data[i]);
    }

    delete[] data;
    data = newData;
    this->capacity = desiredCapacity;
  }

  if (desiredCapacity < capacity) {
    T* newData = new T[desiredCapacity];

    for (int i = 0; i < desiredCapacity; i++) {
      newData[i] = std::move(data[i]);
    }

    delete[] data;
    data = newData;
    this->size = desiredCapacity;
    this->capacity = desiredCapacity;
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
  data = nullptr;
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
  } else if (currentCapacity >= 1000) {
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
  this->QuickSort(data, 0, size - 1);
}

template <typename T>
void Vector<T>::Reverse() {
  for (int i = 0; i < size / 2; i++) {
    Swap(&data[i], &data[size - i - 1]);
  }
}

template <typename T>
void Vector<T>::QuickSort(T* array, int low, int high) {
  if (low < high) {
    int partition = this->Partition(array, low, high);
    QuickSort(array, low, partition - 1);
    QuickSort(array, partition + 1, high);
  }
}

template <typename T>
int Vector<T>::Partition(T* array, int low, int high) {
  int i = low - 1;
  int j = low;
  T k = array[high];

  while (j < high) {
    if (array[j] <= k) {
      i++;

      if (i != j) {
        Swap(&array[i], &array[j]);
      }
    }

    j++;
  }

  T temp = array[i + 1];
  array[i + 1] = array[high];
  array[high] = temp;
  return i + 1;
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

  if (otherList.Size() > this->capacity) {
    int initialSize = this->size;
    this->Resize(otherList.Size());
    this->size = otherList.Size();

    for (int i = 0; i < otherList.Size(); i++) {
      Swap(&data[i], &otherList.data[i]);
    }

    otherList.Resize(initialSize);
    otherList.size = initialSize;
  }

  if (this->capacity > otherList.Size()) {
    int initialSize = otherList.Size();
    otherList.Resize(this->size);
    otherList.size = this->size;

    for (int i = 0; i < size; i++) {
      Swap(&data[i], &otherList.data[i]);
    }

    this->Resize(initialSize);
    this->size = initialSize;
  }

  if (this->size == otherList.Size()) {
    for (int i = 0; i < size; i++) {
      Swap(&data[i], &otherList[i]);
    }
  }
}

template <typename T>
int Vector<T>::RemoveIf(bool (*function)(const T&)) {
  int amountRemoved = 0;

  for (int i = 0; i < size; i++) {
    bool shouldRemove = function(data[i]);

    if (shouldRemove) {
      Erase(i);
      amountRemoved++;
    }
  }

  return amountRemoved;
}

template <typename T>
bool Vector<T>::RemoveIndexIf(int index, bool (*function)(const T&)) {
  bool shouldRemove = function(index);

  if (shouldRemove) {
    this->Erase(index);
    return true;
  }

  return false;
}

template <typename T>
void Vector<T>::ForEach(T (*function)(const T&, int)) {
  int index = 0;
  for (int i = 0; i < size; i++) {
    data[i] = std::move(function(data[i], index));
    index++;
  }
}

template <typename T>
bool Vector<T>::Every(bool (*function)(const T&, int)) {
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
bool Vector<T>::Any(bool (*function)(const T&, int)) {
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
  int counter = size - 1;
  int index = -1;

  for (int i = size - 1; i >= 0; i--) {
    if (data[i] == dataToFind) {
      index = counter;
      break;
    }

    counter--;
  }

  return index;
}

template <typename T>
T* Vector<T>::Find(const T& dataToFind) const {
  for (int i = 0; i < size; i++) {
    if (data[i] == dataToFind) {
      return &data[i];
    }
  }

  return nullptr;
}

template <typename T>
T* Vector<T>::Find(bool (*function)(const T&, int)) const {
  for (int i = 0; i < size; i++) {
    if (function(data[i], i)) {
      return &data[i];
    }
  }

  return nullptr;
}

template <typename T>
T* Vector<T>::FindLast(const T& dataToFind) const {
  for (int i = size - 1; i >= 0; i--) {
    if (data[i] == dataToFind) {
      return &data[i];
    }
  }

  return nullptr;
}

template <typename T>
T* Vector<T>::FindLast(bool (*function)(const T&, int)) const {
  for (int i = size - 1; i >= 0; i--) {
    if (function(data[i], i)) {
      return &data[i];
    }
  }

  return nullptr;
}

template <typename T>
void Vector<T>::Swap(T* a, T* b) {
  T temporary = std::move(*a);
  *a = std::move(*b);
  *b = std::move(temporary);
}

template <typename T>
void Vector<T>::Concat(const Vector<T>& otherVector) {
  if (otherVector.Size() == 0) {
    return;
  }

  int otherVectorSize = otherVector.size;
  int freeCapacity = this->FreeCapacity();

  if (otherVectorSize > freeCapacity) {
    this->Resize(freeCapacity + otherVectorSize);
  }

  for (int i = 0; i < otherVector.Size(); i++) {
    PushBack(otherVector[i]);
  }
}

template <typename T>
int Vector<T>::BinarySeach(const T& target) {
  return this->BSearch(data, target, 0, size - 1);
}

template <typename T>
int Vector<T>::BSearch(T* array, const T& target, int left, int right) {
  while (left <= right) {
    int middle = static_cast<int>(floor((left + right) / 2));
    int middleValue = array[middle];

    if (target == middleValue) {
      return middle;
    } else if (target < middleValue) {
      right = middle - 1;
    } else {
      left = middle + 1;
    }
  }

  return -1;
}

template <typename T>
void Vector<T>::Print() const {
  if (this->size == 0) {
    return;
  }

  std::cout << "[";
  for (int i = 0; i < size; i++) {
    std::cout << data[i];

    if (i < (size - 1)) {
      std::cout << ", ";
    }
  }

  std::cout << "]" << std::endl;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const Vector<T>& vector) {
  vector.Print();
  return os;
}

#endif