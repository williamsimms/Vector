#ifndef _VECTORITERATOR_H_
#define _VECTORITERATOR_H_

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

#endif