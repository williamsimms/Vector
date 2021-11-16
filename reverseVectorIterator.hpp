#ifndef _REVERSEVECTORITERATOR_H_
#define _REVERSEVECTORITERATOR_H_

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

#endif  // _REVERSEVECTORITERATOR_H_