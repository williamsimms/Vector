#define CATCH_CONFIG_MAIN

#include "vector.hpp"

#include <vector>

#include "Vector3.hpp"
#include "vendor/catch.hpp"

TEST_CASE("Assigns Elements to the Vector.", "[Assign]") {
  SECTION("Assigns elements to the vector using An Ininitializer list.") {
    Vector<int> vector{1, 2, 3, 4, 5};

    REQUIRE(vector.Size() == 5);
    REQUIRE(vector[0] == 1);
    REQUIRE(vector[1] == 2);
    REQUIRE(vector[2] == 3);
    REQUIRE(vector[3] == 4);
    REQUIRE(vector[4] == 5);
  }

  SECTION("Assigns elements to the vector using A Vector.") {
    std::vector vectorInitializer{1, 2, 3, 4, 5};
    Vector<int> vector(vectorInitializer);

    REQUIRE(vector.Size() == 5);
    REQUIRE(vector[0] == 1);
    REQUIRE(vector[1] == 2);
    REQUIRE(vector[2] == 3);
    REQUIRE(vector[3] == 4);
    REQUIRE(vector[4] == 5);
  }

  SECTION(
      "Assigns the number of elements provided all with the provided data.") {
    Vector<int> vector(5, 1);

    REQUIRE(vector.Size() == 5);
    REQUIRE(vector[0] == 1);
    REQUIRE(vector[1] == 1);
    REQUIRE(vector[2] == 1);
    REQUIRE(vector[3] == 1);
    REQUIRE(vector[4] == 1);
  }
}

TEST_CASE("Returns the current size of the vector.", "[Size]") {
  SECTION(
      "Returns 0 when the list, is initialized using the Default "
      "Constructor.") {
    Vector<int> vector;
    REQUIRE(vector.Size() == 0);
  }

  SECTION(
      "Returns the size of the list after being initialized with a initializer "
      "list.") {
    Vector<int> vector{1, 2, 3, 4, 5};
    REQUIRE(vector.Size() == 5);
  }

  SECTION(
      "Returns the size of the list after having elements appended to it.") {
    Vector<int> vector{1, 2, 3, 4, 5};
    REQUIRE(vector.Size() == 5);

    vector.PushBack(5);
    REQUIRE(vector.Size() == 6);

    vector.PushBack(12);
    REQUIRE(vector.Size() == 7);

    vector.PushBack(13);
    REQUIRE(vector.Size() == 8);
  }

  SECTION(
      "Returns the size of the list after having elements removed from it.") {
    Vector<int> vector{1, 2, 3, 4, 5};
    REQUIRE(vector.Size() == 5);

    vector.PopBack();
    REQUIRE(vector.Size() == 4);

    vector.PopBack();
    REQUIRE(vector.Size() == 3);
  }

  SECTION(
      "Returns the size of the list after having elements added and removed "
      "from it.") {
    Vector<int> vector{1, 2, 3, 4, 5};
    REQUIRE(vector.Size() == 5);

    vector.PushBack(5);
    REQUIRE(vector.Size() == 6);

    vector.PushBack(12);
    REQUIRE(vector.Size() == 7);

    vector.PushBack(13);
    REQUIRE(vector.Size() == 8);

    vector.PopBack();
    REQUIRE(vector.Size() == 7);

    vector.PopBack();
    REQUIRE(vector.Size() == 6);
  }
}

TEST_CASE("Returns the current maximum size of the vector.", "[Max Size]") {
  Vector<int> vector{1, 2, 3, 4, 5};
  REQUIRE(vector.MaxSize() == 5);
}

TEST_CASE("Returns the capacity of the array.", "[Capacity]") {
  Vector<int> vector{1};
  REQUIRE(vector.Capacity() == 1);
  REQUIRE(vector.Size() == 1);

  vector.PushBack(2);

  REQUIRE(vector.Capacity() == 2);
  REQUIRE(vector.Size() == 2);

  vector.PushBack(3);

  REQUIRE(vector.Capacity() == 4);
  REQUIRE(vector.Size() == 3);

  vector.PushBack(4);

  REQUIRE(vector.Capacity() == 4);
  REQUIRE(vector.Size() == 4);

  vector.PushBack(5);

  REQUIRE(vector.Capacity() == 8);
  REQUIRE(vector.Size() == 5);
}

TEST_CASE("Returns true if the vector is empty, otherwise returns true.",
          "[Empty]") {
  SECTION("Returns true if the list is empty.") {
    Vector<int> vector;
    bool isEmpty = vector.Empty();
    REQUIRE(isEmpty == true);
  }

  SECTION("Returns false if the list is not empty.") {
    Vector<int> vector{1, 2, 3};
    bool isEmpty = vector.Empty();
    REQUIRE(isEmpty == false);
  }
}

TEST_CASE("Returns a reference to the first element in the array.", "[Front]") {
  SECTION("Returns a reference to the first element in the array.") {
    Vector<int> vector{1, 2, 3, 4, 5};
    REQUIRE(vector.Front() == 1);
  }

  SECTION("The value of the element can be changed.") {
    Vector<int> vector{1, 2, 3, 4, 5};
    vector.Front() = 12;
    REQUIRE(vector.Front() == 12);
  }

  SECTION(
      "Returns a reference to the first element in the array when using a "
      "const Vector.") {
    const Vector<int> vector{1, 2, 3, 4, 5};
    REQUIRE(vector.Front() == 1);
  }
}

TEST_CASE("Returns a reference to the last element in the array.", "[Back]") {
  SECTION("Returns a reference to the last element in the array.") {
    Vector<int> vector{1, 2, 3, 4, 5};
    REQUIRE(vector.Back() == 5);
  }

  SECTION("The value of the element can be changed.") {
    Vector<int> vector{1, 2, 3, 4, 5};
    vector.Back() = 12;
    REQUIRE(vector.Back() == 12);
  }

  SECTION(
      "Returns a reference to the last element in the array when using a "
      "const Vector.") {
    const Vector<int> vector{1, 2, 3, 4, 5};
    REQUIRE(vector.Back() == 5);
  }
}

TEST_CASE("Returns a reference to the element at the middle of the array.",
          "[Middle]") {
  SECTION("Returns a reference to the middle element in the array.") {
    Vector<int> vector{1, 2, 3, 4, 5};
    REQUIRE(vector.Middle() == 3);
  }

  SECTION("The value of the element can be changed.") {
    Vector<int> vector{1, 2, 3, 4, 5};
    vector.Middle() = 12;
    REQUIRE(vector.Middle() == 12);
  }

  SECTION(
      "Returns a reference to the middle element in the array when using a "
      "const Vector.") {
    const Vector<int> vector{1, 2, 3, 4, 5};
    REQUIRE(vector.Middle() == 3);
  }
}

TEST_CASE("Appends a new element to the end of the Vector.", "[Push Back]") {
  SECTION("Pushes a New element to the end of the array using a l-value.") {
    Vector<int> vector;
    REQUIRE(vector.Size() == 0);
    REQUIRE(vector.Capacity() == 0);

    int x = 5;
    vector.PushBack(x);
    REQUIRE(vector[0] == 5);
    REQUIRE(vector.Size() == 1);
    REQUIRE(vector.Capacity() == 1);

    int z = 12;
    vector.PushBack(z);
    REQUIRE(vector[0] == 5);
    REQUIRE(vector[1] == 12);
    REQUIRE(vector.Size() == 2);
    REQUIRE(vector.Capacity() == 2);
  }

  SECTION("Pushes a New element to the end of the array using a r-value.") {
    Vector<int> vector;
    REQUIRE(vector.Size() == 0);
    REQUIRE(vector.Capacity() == 0);

    vector.PushBack(5);
    REQUIRE(vector[0] == 5);
    REQUIRE(vector.Size() == 1);
    REQUIRE(vector.Capacity() == 1);

    vector.PushBack(12);
    REQUIRE(vector[0] == 5);
    REQUIRE(vector[1] == 12);
    REQUIRE(vector.Size() == 2);
    REQUIRE(vector.Capacity() == 2);
  }
}

TEST_CASE("Appends a new element to the front of the Vector.", "[Push Front]") {
  SECTION("Appends a New element to the front of the vector using a l-value.") {
    Vector<int> vector;
    REQUIRE(vector.Size() == 0);
    REQUIRE(vector.Capacity() == 0);

    int x = 5;
    vector.PushFront(x);
    REQUIRE(vector[0] == 5);
    REQUIRE(vector.Size() == 1);
    REQUIRE(vector.Capacity() == 1);

    int z = 12;
    vector.PushFront(z);
    REQUIRE(vector[0] == 12);
    REQUIRE(vector[1] == 5);
    REQUIRE(vector.Size() == 2);
    REQUIRE(vector.Capacity() == 2);
  }

  SECTION("Appends a New element to the front of the vector using a r-value.") {
    Vector<int> vector;
    REQUIRE(vector.Size() == 0);
    REQUIRE(vector.Capacity() == 0);

    vector.PushBack(5);
    REQUIRE(vector[0] == 5);
    REQUIRE(vector.Size() == 1);
    REQUIRE(vector.Capacity() == 1);

    vector.PushBack(12);
    REQUIRE(vector[0] == 5);
    REQUIRE(vector[1] == 12);
    REQUIRE(vector.Size() == 2);
    REQUIRE(vector.Capacity() == 2);
  }
}

TEST_CASE("Appends a new element to the middle of the Vector.",
          "[Push Middle]") {
  SECTION(
      "Appends a New element to the middle of the vector using a l-value.") {
    Vector<int> vector{1, 2, 3};
    REQUIRE(vector.Size() == 3);
    REQUIRE(vector.Capacity() == 3);

    int x = 5;
    vector.PushMiddle(x);
    int midpoint = vector.Midpoint();
    REQUIRE(vector[midpoint] == 5);
    REQUIRE(vector.Size() == 4);
    REQUIRE(vector.Capacity() == 6);

    int z = 12;
    vector.PushMiddle(z);
    int midpointTwo = vector.Midpoint();
    REQUIRE(vector[midpointTwo] == 12);
    REQUIRE(vector.Size() == 5);
    REQUIRE(vector.Capacity() == 6);
  }

  SECTION(
      "Appends a New element to the middle of the vector using a r-value.") {
    Vector<int> vector{1, 2, 3};
    REQUIRE(vector.Size() == 3);
    REQUIRE(vector.Capacity() == 3);

    vector.PushMiddle(5);
    int midpoint = vector.Midpoint();
    REQUIRE(vector[midpoint] == 5);
    REQUIRE(vector.Size() == 4);
    REQUIRE(vector.Capacity() == 6);

    vector.PushMiddle(12);
    midpoint = vector.Midpoint();
    REQUIRE(vector[midpoint] == 12);
    REQUIRE(vector.Size() == 5);
    REQUIRE(vector.Capacity() == 6);
  }
}

TEST_CASE("Inserta a new element at the desired index.", ";Insert]") {
  SECTION("Inserts new element at the first position of the vector.") {
    Vector<int> vector{1, 2, 3, 4};

    REQUIRE(vector.Size() == 4);
    REQUIRE(vector.Capacity() == 4);
    REQUIRE(vector[0] == 1);
    REQUIRE(vector[1] == 2);
    REQUIRE(vector[2] == 3);
    REQUIRE(vector[3] == 4);

    vector.Insert(0, 12);

    REQUIRE(vector.Size() == 5);
    REQUIRE(vector.Capacity() == 8);
    REQUIRE(vector[0] == 12);
    REQUIRE(vector[1] == 1);
    REQUIRE(vector[2] == 2);
    REQUIRE(vector[3] == 3);
    REQUIRE(vector[4] == 4);
  }

  SECTION("Inserts new element at the last index of the vector.") {
    Vector<int> vector{1, 2, 3, 4};

    REQUIRE(vector.Size() == 4);
    REQUIRE(vector.Capacity() == 4);
    REQUIRE(vector[0] == 1);
    REQUIRE(vector[1] == 2);
    REQUIRE(vector[2] == 3);
    REQUIRE(vector[3] == 4);

    vector.Insert(3, 12);

    REQUIRE(vector.Size() == 5);
    REQUIRE(vector.Capacity() == 8);
    REQUIRE(vector[0] == 1);
    REQUIRE(vector[1] == 2);
    REQUIRE(vector[2] == 3);
    REQUIRE(vector[3] == 12);
    REQUIRE(vector[4] == 4);
  }

  SECTION("Inserts new element at the middle position of the vector.") {
    Vector<int> vector{1, 2, 3, 4};

    REQUIRE(vector.Size() == 4);
    REQUIRE(vector.Capacity() == 4);
    REQUIRE(vector[0] == 1);
    REQUIRE(vector[1] == 2);
    REQUIRE(vector[2] == 3);
    REQUIRE(vector[3] == 4);

    vector.Insert(1, 12);

    REQUIRE(vector.Size() == 5);
    REQUIRE(vector.Capacity() == 8);
    REQUIRE(vector[0] == 1);
    REQUIRE(vector[1] == 12);
    REQUIRE(vector[2] == 2);
    REQUIRE(vector[3] == 3);
    REQUIRE(vector[4] == 4);
  }

  SECTION("Inserts new element at an arbritrary index of the vector.") {
    Vector<int> vector{1, 2, 3, 4};

    REQUIRE(vector.Size() == 4);
    REQUIRE(vector.Capacity() == 4);
    REQUIRE(vector[0] == 1);
    REQUIRE(vector[1] == 2);
    REQUIRE(vector[2] == 3);
    REQUIRE(vector[3] == 4);

    vector.Insert(2, 12);

    REQUIRE(vector.Size() == 5);
    REQUIRE(vector.Capacity() == 8);
    REQUIRE(vector[0] == 1);
    REQUIRE(vector[1] == 2);
    REQUIRE(vector[2] == 12);
    REQUIRE(vector[3] == 3);
    REQUIRE(vector[4] == 4);
  }
}

TEST_CASE("Removes the first element from the Vector.", "[Pop Front]") {
  Vector<int> vector{1, 2, 3, 4};

  REQUIRE(vector.Size() == 4);
  REQUIRE(vector.Capacity() == 4);

  REQUIRE(vector[0] == 1);
  REQUIRE(vector[1] == 2);
  REQUIRE(vector[2] == 3);
  REQUIRE(vector[3] == 4);

  vector.PopFront();

  REQUIRE(vector.Size() == 3);
  REQUIRE(vector.Capacity() == 4);

  REQUIRE(vector[0] == 2);
  REQUIRE(vector[1] == 3);
  REQUIRE(vector[2] == 4);
}

TEST_CASE("Removes the last element from the Vector.", "[Pop Back]") {
  Vector<int> vector{1, 2, 3, 4};

  REQUIRE(vector.Size() == 4);
  REQUIRE(vector.Capacity() == 4);

  REQUIRE(vector[0] == 1);
  REQUIRE(vector[1] == 2);
  REQUIRE(vector[2] == 3);
  REQUIRE(vector[3] == 4);

  vector.PopBack();

  REQUIRE(vector.Size() == 3);
  REQUIRE(vector.Capacity() == 4);

  REQUIRE(vector[0] == 1);
  REQUIRE(vector[1] == 2);
  REQUIRE(vector[2] == 3);
}

TEST_CASE("Removes the element at the middle position from the Vector.",
          "[Pop Middle]") {
  Vector<int> vector{1, 2, 3, 4};

  REQUIRE(vector.Size() == 4);
  REQUIRE(vector.Capacity() == 4);

  REQUIRE(vector[0] == 1);
  REQUIRE(vector[1] == 2);
  REQUIRE(vector[2] == 3);
  REQUIRE(vector[3] == 4);

  vector.PopMiddle();

  REQUIRE(vector.Size() == 3);
  REQUIRE(vector.Capacity() == 4);

  REQUIRE(vector[0] == 1);
  REQUIRE(vector[1] == 3);
  REQUIRE(vector[2] == 4);
}

TEST_CASE("Removes the element at the desired index from the Vector.",
          "[Erase]") {
  SECTION("Removes the first element from the Vector.") {
    Vector<int> vector{1, 2, 3, 4};

    REQUIRE(vector.Size() == 4);
    REQUIRE(vector.Capacity() == 4);

    REQUIRE(vector[0] == 1);
    REQUIRE(vector[1] == 2);
    REQUIRE(vector[2] == 3);
    REQUIRE(vector[3] == 4);

    vector.Erase(0);

    REQUIRE(vector.Size() == 3);
    REQUIRE(vector.Capacity() == 4);

    REQUIRE(vector[0] == 2);
    REQUIRE(vector[1] == 3);
    REQUIRE(vector[2] == 4);
  }

  SECTION("Removes the last element from the Vector.") {
    Vector<int> vector{1, 2, 3, 4};

    REQUIRE(vector.Size() == 4);
    REQUIRE(vector.Capacity() == 4);

    REQUIRE(vector[0] == 1);
    REQUIRE(vector[1] == 2);
    REQUIRE(vector[2] == 3);
    REQUIRE(vector[3] == 4);

    vector.Erase(3);

    REQUIRE(vector.Size() == 3);
    REQUIRE(vector.Capacity() == 4);

    REQUIRE(vector[0] == 1);
    REQUIRE(vector[1] == 2);
    REQUIRE(vector[2] == 3);
  }

  SECTION("Removes the middle element from the Vector.") {
    Vector<int> vector{1, 2, 3, 4};

    REQUIRE(vector.Size() == 4);
    REQUIRE(vector.Capacity() == 4);

    REQUIRE(vector[0] == 1);
    REQUIRE(vector[1] == 2);
    REQUIRE(vector[2] == 3);
    REQUIRE(vector[3] == 4);

    vector.Erase(1);

    REQUIRE(vector.Size() == 3);
    REQUIRE(vector.Capacity() == 4);

    REQUIRE(vector[0] == 1);
    REQUIRE(vector[1] == 3);
    REQUIRE(vector[2] == 4);
  }

  SECTION("Removes an arbritrary index from the Vector.") {
    Vector<int> vector{1, 2, 3, 4};

    REQUIRE(vector.Size() == 4);
    REQUIRE(vector.Capacity() == 4);

    REQUIRE(vector[0] == 1);
    REQUIRE(vector[1] == 2);
    REQUIRE(vector[2] == 3);
    REQUIRE(vector[3] == 4);

    vector.Erase(2);

    REQUIRE(vector.Size() == 3);
    REQUIRE(vector.Capacity() == 4);

    REQUIRE(vector[0] == 1);
    REQUIRE(vector[1] == 2);
    REQUIRE(vector[2] == 4);
  }
}

TEST_CASE("Returns the element at the desired index.", "[At]") {
  SECTION("Returns a reference to the element at the provided index.") {
    Vector<int> vector{1, 2, 3, 4};

    REQUIRE(vector.Size() == 4);
    REQUIRE(vector.Capacity() == 4);

    REQUIRE(vector.At(0) == 1);
    REQUIRE(vector.At(1) == 2);
    REQUIRE(vector.At(2) == 3);
    REQUIRE(vector.At(3) == 4);
  }

  SECTION("Allows for the editing of the Reference via the At function.") {
    Vector<int> vector{1, 2, 3, 4};

    REQUIRE(vector.Size() == 4);
    REQUIRE(vector.Capacity() == 4);

    REQUIRE(vector.At(0) == 1);
    REQUIRE(vector.At(1) == 2);
    REQUIRE(vector.At(2) == 3);
    REQUIRE(vector.At(3) == 4);

    vector.At(0) = 12;
    vector.At(3) = 22;

    REQUIRE(vector.At(0) == 12);
    REQUIRE(vector.At(1) == 2);
    REQUIRE(vector.At(2) == 3);
    REQUIRE(vector.At(3) == 22);
  }

  SECTION(
      "Returns a non modifiable reference to the element at the provided index "
      "when working with a const Vector.") {
    const Vector<int> vector{1, 2, 3, 4};

    REQUIRE(vector.Size() == 4);
    REQUIRE(vector.Capacity() == 4);

    REQUIRE(vector.At(0) == 1);
    REQUIRE(vector.At(1) == 2);
    REQUIRE(vector.At(2) == 3);
    REQUIRE(vector.At(3) == 4);
  }
}

TEST_CASE(
    "Generates the next capacity the vector will resize to, when it needs to "
    "resize.",
    "[Generate New Capacity]") {
  SECTION("If the current capacity is zero, the new capacity is one.") {
    Vector<char> vector;
    int newCapacity = vector.GenerateNewCapacity();
    REQUIRE(vector.Capacity() == 0);
    REQUIRE(newCapacity == 1);
  }

  SECTION(
      "If the current capacity is greater than 1000, the new capacity is the "
      "old capacity plus one quarter of the old capacity.") {
    Vector<char> vector;
    vector.Reserve(1000);
    int newCapacity = vector.GenerateNewCapacity();
    REQUIRE(vector.Capacity() == 1000);
    REQUIRE(newCapacity == 1250);
  }

  SECTION(
      "If the capacity is greater than zero and less than one thousand, the "
      "capacity is doubled.") {
    Vector<char> vector;
    vector.Reserve(10);
    int newCapacity = vector.GenerateNewCapacity();
    REQUIRE(vector.Capacity() == 10);
    REQUIRE(newCapacity == 20);
  }
}

TEST_CASE("Resizes the vector to the provided capacity.", "[Resize]") {
  SECTION(
      "If the desired capacity is greater than the current capacity, allocates "
      "new memory of the desired size, and copies over elements from previous "
      "vector.") {
    Vector<int> vector{1, 2, 3};

    REQUIRE(vector.Size() == 3);
    REQUIRE(vector.Capacity() == 3);

    REQUIRE(vector[0] == 1);
    REQUIRE(vector[1] == 2);
    REQUIRE(vector[2] == 3);

    vector.Resize(10);

    REQUIRE(vector.Size() == 3);
    REQUIRE(vector.Capacity() == 10);

    REQUIRE(vector[0] == 1);
    REQUIRE(vector[1] == 2);
    REQUIRE(vector[2] == 3);
  }

  SECTION(
      "If the desired capacity is lesser than the current capacity, allocates "
      "new memory of the desired size, and copies over elements from previous "
      "vector, potentially cropping elements which were once present in the "
      "list.") {
    Vector<int> vector{1, 2, 3, 4, 5};

    REQUIRE(vector.Size() == 5);
    REQUIRE(vector.Capacity() == 5);

    REQUIRE(vector[0] == 1);
    REQUIRE(vector[1] == 2);
    REQUIRE(vector[2] == 3);
    REQUIRE(vector[3] == 4);
    REQUIRE(vector[4] == 5);

    vector.Resize(3);

    REQUIRE(vector.Size() == 3);
    REQUIRE(vector.Capacity() == 3);

    REQUIRE(vector[0] == 1);
    REQUIRE(vector[1] == 2);
    REQUIRE(vector[2] == 3);
  }

  SECTION(
      "Doesnt Change the capacity if the desired capacity is the same as the "
      "current capacity.") {
    Vector<int> vector{1, 2, 3, 4, 5};

    REQUIRE(vector.Size() == 5);
    REQUIRE(vector.Capacity() == 5);

    REQUIRE(vector[0] == 1);
    REQUIRE(vector[1] == 2);
    REQUIRE(vector[2] == 3);
    REQUIRE(vector[3] == 4);
    REQUIRE(vector[4] == 5);

    vector.Resize(5);

    REQUIRE(vector.Size() == 5);
    REQUIRE(vector.Capacity() == 5);

    REQUIRE(vector[0] == 1);
    REQUIRE(vector[1] == 2);
    REQUIRE(vector[2] == 3);
    REQUIRE(vector[3] == 4);
    REQUIRE(vector[4] == 5);
  }
}

TEST_CASE("Reserves memory for the Vector.", "[Reserve]") {
  SECTION(
      "If the procided amount to reserve is less than or equal to the current "
      "capacity, no memory is allocated.") {
    Vector<int> vector{1, 2, 3, 4, 5};

    REQUIRE(vector.Size() == 5);
    REQUIRE(vector.Capacity() == 5);

    vector.Reserve(5);

    REQUIRE(vector.Size() == 5);
    REQUIRE(vector.Capacity() == 5);
  }

  SECTION(
      "If the provided amount to reserve is greater than the current capacity, "
      "the desired amount of memory is allocated, and the elements are "
      "copied.") {
    Vector<int> vector{1, 2, 3, 4, 5};

    REQUIRE(vector.Size() == 5);
    REQUIRE(vector.Capacity() == 5);

    vector.Reserve(10);

    REQUIRE(vector.Size() == 5);
    REQUIRE(vector.Capacity() == 10);
  }
}

TEST_CASE(
    "Sets the size and capacity of the vector to 0, and deallocates the "
    "allocated memory of the vector.",
    "[Clear]") {
  Vector<int> vector{1, 2, 3, 4, 5};

  REQUIRE(vector.Size() == 5);
  REQUIRE(vector.Capacity() == 5);

  vector.Clear();

  REQUIRE(vector.Size() == 0);
  REQUIRE(vector.Capacity() == 0);
  REQUIRE(vector.Data() == nullptr);
}

TEST_CASE(
    "Shrinks the capacity of the vector to the current size of the vector.",
    "[Shrink to Fit]") {
  SECTION("Does nothing if the current capacity and size are equal.") {
    Vector<int> vector{1, 2, 3, 4, 5};

    REQUIRE(vector.Size() == 5);
    REQUIRE(vector.Capacity() == 5);

    vector.ShrinkToFit();

    REQUIRE(vector.Size() == 5);
    REQUIRE(vector.Capacity() == 5);
  }

  SECTION(
      "If the capacity is greater than the current length, resizes the vector "
      "to the amount of elements in the vector, effectively shrinking the "
      "vector. The capacity and size of the vector will now be equal.") {
    Vector<int> vector{1, 2, 3, 4, 5};

    REQUIRE(vector.Size() == 5);
    REQUIRE(vector.Capacity() == 5);

    vector.PushBack(6);

    REQUIRE(vector.Size() == 6);
    REQUIRE(vector.Capacity() == 10);

    vector.ShrinkToFit();

    REQUIRE(vector.Size() == 6);
    REQUIRE(vector.Capacity() == 6);

    vector.Reserve(10);

    REQUIRE(vector.Size() == 6);
    REQUIRE(vector.Capacity() == 10);

    vector.ShrinkToFit();

    REQUIRE(vector.Size() == 6);
    REQUIRE(vector.Capacity() == 6);
  }
}

TEST_CASE("Emplaces the new element at the back of the Vector.",
          "[Emplace Back]") {
  Vector<Vector2> vector;

  REQUIRE(vector.Size() == 0);
  REQUIRE(vector.Capacity() == 0);

  Vector2 vector2One(2, 3);

  vector.EmplaceBack(2, 3);

  REQUIRE(vector.Size() == 1);
  REQUIRE(vector.Capacity() == 1);

  REQUIRE(vector.Back() == vector2One);

  Vector2 vector2Two(1, 2);

  vector.EmplaceBack(1, 2);
  REQUIRE(vector.Size() == 2);
  REQUIRE(vector.Capacity() == 2);

  REQUIRE(vector.Back() == vector2Two);
}

TEST_CASE("Emplaces the new element at the beginning of the Vector.",
          "[Emplace Front]") {
  Vector<Vector2> vector;

  REQUIRE(vector.Size() == 0);
  REQUIRE(vector.Capacity() == 0);

  Vector2 vector2One(2, 3);

  vector.EmplaceFront(2, 3);

  REQUIRE(vector.Size() == 1);
  REQUIRE(vector.Capacity() == 1);

  REQUIRE(vector.Front() == vector2One);

  Vector2 vector2Two(1, 2);

  vector.EmplaceFront(1, 2);
  REQUIRE(vector.Size() == 2);
  REQUIRE(vector.Capacity() == 2);

  REQUIRE(vector.Front() == vector2Two);
}

TEST_CASE("Emplaces the new element at the specified index of the Vector.",
          "[Emplace Middle]") {
  Vector<Vector2> vector;

  REQUIRE(vector.Size() == 0);
  REQUIRE(vector.Capacity() == 0);

  Vector2 vector2One(2, 3);

  vector.EmplaceBack(2, 3);

  REQUIRE(vector.Size() == 1);
  REQUIRE(vector.Capacity() == 1);

  REQUIRE(vector.Back() == vector2One);

  Vector2 vector2Two(1, 2);

  vector.EmplaceBack(1, 2);
  REQUIRE(vector.Size() == 2);
  REQUIRE(vector.Capacity() == 2);

  REQUIRE(vector.Back() == vector2Two);

  Vector2 vector3Three(2, 6);
  vector.Emplace(0, 2, 6);
  REQUIRE(vector.Size() == 3);
  REQUIRE(vector.Capacity() == 4);

  REQUIRE(vector.Front() == vector3Three);
}

TEST_CASE(
    "Returns the index of the first occurence of the provided data in the "
    "Vector. Otherwise returns -1.",
    "[Index Of]") {
  Vector<int> vector{1, 2, 3, 4, 5, 5, 2, 1};

  REQUIRE(vector.IndexOf(1) == 0);
  REQUIRE(vector.IndexOf(2) == 1);
  REQUIRE(vector.IndexOf(3) == 2);
  REQUIRE(vector.IndexOf(4) == 3);
  REQUIRE(vector.IndexOf(5) == 4);
  REQUIRE(vector.IndexOf(12) == -1);
}

TEST_CASE(
    "Returns the index of the last occurence of the provided data in the "
    "Vector. Otherwise returns -1.",
    "[Last Index Of]") {
  Vector<int> vector{1, 2, 3, 4, 5, 5, 2, 1};

  REQUIRE(vector.LastIndexOf(1) == 7);
  REQUIRE(vector.LastIndexOf(2) == 6);
  REQUIRE(vector.LastIndexOf(3) == 2);
  REQUIRE(vector.LastIndexOf(4) == 3);
  REQUIRE(vector.LastIndexOf(5) == 5);
  REQUIRE(vector.LastIndexOf(12) == -1);
}

TEST_CASE(
    "Returns a pointer to the first occurrence of the element with matching "
    "data.",
    "[Find]") {
  SECTION(
      "Returns nullptr if no element in the Vector matches the passed in "
      "data.") {
    Vector<int> vector{1, 2, 3, 4, 5};

    REQUIRE(vector.Find(12) == nullptr);
  }

  SECTION("Returns a pointer to the first element found with matching data.") {
    Vector<int> vector{1, 2, 3, 4, 5, 1, 2, 3};

    REQUIRE(vector[0] == 1);
    REQUIRE(vector[1] == 2);
    REQUIRE(vector[2] == 3);
    REQUIRE(vector[3] == 4);
    REQUIRE(vector[4] == 5);
    REQUIRE(vector[5] == 1);
    REQUIRE(vector[6] == 2);
    REQUIRE(vector[7] == 3);

    REQUIRE(*(vector.Find(1)) == 1);
    REQUIRE(*(vector.Find(2)) == 2);
    REQUIRE(*(vector.Find(3)) == 3);

    *(vector.Find(1)) += 10;
    *(vector.Find(2)) += 10;
    *(vector.Find(3)) += 10;

    REQUIRE(vector[0] == 11);
    REQUIRE(vector[1] == 12);
    REQUIRE(vector[2] == 13);
    REQUIRE(vector[3] == 4);
    REQUIRE(vector[4] == 5);
    REQUIRE(vector[5] == 1);
    REQUIRE(vector[6] == 2);
    REQUIRE(vector[7] == 3);
  }

  SECTION(
      "Returns a pointer to the first element in which the provided function "
      "returned a truthy value for its value.") {
    Vector<int> vector{1, 2, 3, 4, 5};

    int* foundElement = vector.Find([](const int& number, int) {
      if (number > 2) {
        return true;
      }

      return false;
    });

    REQUIRE(*foundElement == 3);

    int* foundElementTwo = vector.Find([](const int& number, int) {
      if (number % 2 == 0) {
        return true;
      }

      return false;
    });

    REQUIRE(*foundElementTwo == 2);
  }
}

TEST_CASE(
    "Returns a pointer to the last occurrence of the element with matching "
    "data.",
    "[Find Last]") {
  SECTION(
      "Returns nullptr if no element in the Vector matches the passed in "
      "data.") {
    Vector<int> vector{1, 2, 3, 4, 5};

    REQUIRE(vector.FindLast(12) == nullptr);
  }

  SECTION("Returns a pointer to the last element found with matching data.") {
    Vector<int> vector{1, 2, 3, 4, 5, 1, 2, 3};

    REQUIRE(vector[0] == 1);
    REQUIRE(vector[1] == 2);
    REQUIRE(vector[2] == 3);
    REQUIRE(vector[3] == 4);
    REQUIRE(vector[4] == 5);
    REQUIRE(vector[5] == 1);
    REQUIRE(vector[6] == 2);
    REQUIRE(vector[7] == 3);

    REQUIRE(*(vector.FindLast(1)) == 1);
    REQUIRE(*(vector.FindLast(2)) == 2);
    REQUIRE(*(vector.FindLast(3)) == 3);

    *(vector.FindLast(1)) += 10;
    *(vector.FindLast(2)) += 10;
    *(vector.FindLast(3)) += 10;

    REQUIRE(vector[0] == 1);
    REQUIRE(vector[1] == 2);
    REQUIRE(vector[2] == 3);
    REQUIRE(vector[3] == 4);
    REQUIRE(vector[4] == 5);
    REQUIRE(vector[5] == 11);
    REQUIRE(vector[6] == 12);
    REQUIRE(vector[7] == 13);
  }

  SECTION(
      "Returns a pointer to the last element in which the provided function "
      "returned a truthy value for its value.") {
    Vector<int> vector{1, 2, 3, 4, 5};

    int* foundElement = vector.FindLast([](const int& number, int) {
      if (number > 2) {
        return true;
      }

      return false;
    });

    REQUIRE(*foundElement == 5);

    int* foundElementTwo = vector.FindLast([](const int& number, int) {
      if (number % 2 == 0) {
        return true;
      }

      return false;
    });

    REQUIRE(*foundElementTwo == 4);
  }
}

TEST_CASE("Sorts the Vector using Merge Sort.", "[Sort]") {
  Vector<int> vector{5, 4, 3, 2, 1};

  REQUIRE(vector[0] == 5);
  REQUIRE(vector[1] == 4);
  REQUIRE(vector[2] == 3);
  REQUIRE(vector[3] == 2);
  REQUIRE(vector[4] == 1);

  vector.Sort();

  REQUIRE(vector[0] == 1);
  REQUIRE(vector[1] == 2);
  REQUIRE(vector[2] == 3);
  REQUIRE(vector[3] == 4);
  REQUIRE(vector[4] == 5);
}

TEST_CASE("Reverses the Vector.", "[Reverse]") {
  Vector<int> vector{1, 4, 3, 5, 2};

  REQUIRE(vector[0] == 1);
  REQUIRE(vector[1] == 4);
  REQUIRE(vector[2] == 3);
  REQUIRE(vector[3] == 5);
  REQUIRE(vector[4] == 2);

  vector.Reverse();

  REQUIRE(vector[0] == 2);
  REQUIRE(vector[1] == 5);
  REQUIRE(vector[2] == 3);
  REQUIRE(vector[3] == 4);
  REQUIRE(vector[4] == 1);
}

TEST_CASE(
    "Removes the proved index from the Vector, and returns true; otherwise "
    "returns false.",
    "[Remove Index If]") {
  SECTION("Returns false when the list is empty.") {
    Vector<int> vector;

    bool removed = vector.RemoveIndexIf(2, [](const int& number) {
      if (number > 2) {
        return true;
      }

      return false;
    });

    REQUIRE(removed == false);
  }

  SECTION(
      "Returns false when no element in the Vector suffices the provided "
      "function. No element is removed from the Vector.") {
    Vector<int> vector{1, 2, 3, 4, 5};

    bool removed = vector.RemoveIndexIf(0, [](const int& number) {
      if (number == 10) {
        return true;
      }
      return false;
    });

    REQUIRE(removed == false);
  }

  SECTION(
      "Returns true and removes the element at the provided index in the "
      "Vector.") {
    Vector<int> vector{1, 2, 3, 4, 5};

    bool removed = vector.RemoveIndexIf(0, [](const int& number) {
      if (number < 5) {
        return true;
      }

      return false;
    });

    REQUIRE(removed == true);
  }
}

TEST_CASE(
    "Applies a transformation to every element in the Vector, based on the "
    "passed in Function.",
    "[For Each]") {
  Vector<int> vector{1, 2, 3, 4, 5};

  REQUIRE(vector[0] == 1);
  REQUIRE(vector[1] == 2);
  REQUIRE(vector[2] == 3);
  REQUIRE(vector[3] == 4);
  REQUIRE(vector[4] == 5);

  vector.ForEach([](const int& number, int) { return number + 10; });

  REQUIRE(vector[0] == 11);
  REQUIRE(vector[1] == 12);
  REQUIRE(vector[2] == 13);
  REQUIRE(vector[3] == 14);
  REQUIRE(vector[4] == 15);
}

TEST_CASE(
    "Returns true if any of the elements in the Vector, suffice the passed in "
    "Function.",
    "[Any]") {
  SECTION(
      "Returns false if no elements in the Vector Suffice the passed in "
      "Function.") {
    Vector<int> vector{1, 2, 3, 4, 5};

    bool any = vector.Any([](const int& number, int) {
      if (number > 100) {
        return true;
      }

      return false;
    });

    REQUIRE(any == false);
  }

  SECTION(
      "Returns true if any elements in the Vector Suffice the passed in "
      "Function.") {
    Vector<int> vector{1, 2, 3, 4, 5};

    bool any = vector.Any([](const int& number, int) {
      if (number > 4) {
        return true;
      }

      return false;
    });

    REQUIRE(any == true);
  }
}

TEST_CASE(
    "Returns true if all of the elements in the Vector, suffice the passed in "
    "Function.",
    "[Any]") {
  SECTION(
      "Returns false if no elements in the Vector Suffice the passed in "
      "Function.") {
    Vector<int> vector{1, 2, 3, 4, 5};

    bool every = vector.Every([](const int& number, int) {
      if (number > 100) {
        return true;
      }

      return false;
    });

    REQUIRE(every == false);
  }

  SECTION(
      "Returns false if even one element does not suffice the passed in "
      "function.") {
    Vector<int> vector{1, 2, 3, 4, 5};

    bool every = vector.Every([](const int& number, int) {
      if (number > 1) {
        return true;
      }

      return false;
    });

    REQUIRE(every == false);
  }

  SECTION(
      "Returns true if all elements in the Vector suffice the passed in "
      "function.") {
    Vector<int> vector{1, 2, 3, 4, 5};

    bool every = vector.Every([](const int& number, int) {
      if (number < 10) {
        return true;
      }

      return false;
    });

    REQUIRE(every == true);
  }
}

TEST_CASE("Shuffles the elements of the Vector.", "[Shuffle]") {
  Vector<int> vectorOne{1, 2, 3, 4, 5};
  Vector<int> vectorTwo{1, 2, 3, 4, 5};

  REQUIRE(vectorOne == vectorTwo);

  vectorOne.Shuffle();

  REQUIRE(vectorOne != vectorTwo);
}

TEST_CASE(
    "Swaps the data of two memebers of type T. Takes in two T pointers to swap "
    "the elements in place.",
    "[Swap Elements]") {
  Vector<int> vector{1, 2, 3, 4, 5};

  REQUIRE(vector[0] == 1);
  REQUIRE(vector[1] == 2);
  REQUIRE(vector[2] == 3);
  REQUIRE(vector[3] == 4);
  REQUIRE(vector[4] == 5);

  vector.Swap(&vector[0], &vector[4]);

  REQUIRE(vector[0] == 5);
  REQUIRE(vector[1] == 2);
  REQUIRE(vector[2] == 3);
  REQUIRE(vector[3] == 4);
  REQUIRE(vector[4] == 1);
}

TEST_CASE("Swaps the elements of two Vectors.", "[Swap Vectors]") {
  SECTION("Swaps the Vectors when the first vector has more elements.") {
    Vector<int> vectorOne{1, 2, 3, 4, 5};
    Vector<int> vectorTwo{1, 2};

    REQUIRE(vectorOne[0] == 1);
    REQUIRE(vectorOne[1] == 2);
    REQUIRE(vectorOne[2] == 3);
    REQUIRE(vectorOne[3] == 4);
    REQUIRE(vectorOne[4] == 5);

    REQUIRE(vectorTwo[0] == 1);
    REQUIRE(vectorTwo[1] == 2);

    REQUIRE(vectorOne.Size() == 5);
    REQUIRE(vectorTwo.Size() == 2);

    vectorOne.Swap(vectorTwo);

    REQUIRE(vectorTwo[0] == 1);
    REQUIRE(vectorTwo[1] == 2);
    REQUIRE(vectorTwo[2] == 3);
    REQUIRE(vectorTwo[3] == 4);
    REQUIRE(vectorTwo[4] == 5);

    REQUIRE(vectorOne[0] == 1);
    REQUIRE(vectorOne[1] == 2);

    REQUIRE(vectorOne.Size() == 2);
    REQUIRE(vectorTwo.Size() == 5);
  }

  SECTION("Swaps the vectors when the second vector has more elements.") {
    Vector<int> vectorOne{1, 2};
    Vector<int> vectorTwo{1, 2, 3, 4, 5};

    REQUIRE(vectorOne[0] == 1);
    REQUIRE(vectorOne[1] == 2);

    REQUIRE(vectorTwo[0] == 1);
    REQUIRE(vectorTwo[1] == 2);
    REQUIRE(vectorTwo[2] == 3);
    REQUIRE(vectorTwo[3] == 4);
    REQUIRE(vectorTwo[4] == 5);

    REQUIRE(vectorOne.Size() == 2);
    REQUIRE(vectorTwo.Size() == 5);

    vectorOne.Swap(vectorTwo);

    REQUIRE(vectorOne[0] == 1);
    REQUIRE(vectorOne[1] == 2);
    REQUIRE(vectorOne[2] == 3);
    REQUIRE(vectorOne[3] == 4);
    REQUIRE(vectorOne[4] == 5);

    REQUIRE(vectorTwo[0] == 1);
    REQUIRE(vectorTwo[1] == 2);

    REQUIRE(vectorOne.Size() == 5);
    REQUIRE(vectorTwo.Size() == 2);
  }

  SECTION("Swaps the vectors when both the vectors have the same length.") {
    Vector<int> vectorOne{1, 2, 3};
    Vector<int> vectorTwo{6, 7, 8};

    REQUIRE(vectorOne[0] == 1);
    REQUIRE(vectorOne[1] == 2);
    REQUIRE(vectorOne[2] == 3);

    REQUIRE(vectorTwo[0] == 6);
    REQUIRE(vectorTwo[1] == 7);
    REQUIRE(vectorTwo[2] == 8);

    REQUIRE(vectorOne.Size() == 3);
    REQUIRE(vectorTwo.Size() == 3);

    vectorOne.Swap(vectorTwo);

    REQUIRE(vectorTwo[0] == 1);
    REQUIRE(vectorTwo[1] == 2);
    REQUIRE(vectorTwo[2] == 3);

    REQUIRE(vectorOne[0] == 6);
    REQUIRE(vectorOne[1] == 7);
    REQUIRE(vectorOne[2] == 8);

    REQUIRE(vectorOne.Size() == 3);
    REQUIRE(vectorTwo.Size() == 3);
  }
}

TEST_CASE("Concatenates one vector to the end of another.", "[Concat]") {
  Vector<int> vectorOne{1, 2, 3, 4, 5};
  Vector<int> vectorTwo{6, 7, 8, 9, 10};

  REQUIRE(vectorOne[0] == 1);
  REQUIRE(vectorOne[1] == 2);
  REQUIRE(vectorOne[2] == 3);
  REQUIRE(vectorOne[3] == 4);
  REQUIRE(vectorOne[4] == 5);

  REQUIRE(vectorTwo[0] == 6);
  REQUIRE(vectorTwo[1] == 7);
  REQUIRE(vectorTwo[2] == 8);
  REQUIRE(vectorTwo[3] == 9);
  REQUIRE(vectorTwo[4] == 10);

  vectorOne.Concat(vectorTwo);

  REQUIRE(vectorOne[0] == 1);
  REQUIRE(vectorOne[1] == 2);
  REQUIRE(vectorOne[2] == 3);
  REQUIRE(vectorOne[3] == 4);
  REQUIRE(vectorOne[4] == 5);
  REQUIRE(vectorOne[5] == 6);
  REQUIRE(vectorOne[6] == 7);
  REQUIRE(vectorOne[7] == 8);
  REQUIRE(vectorOne[8] == 9);
  REQUIRE(vectorOne[9] == 10);
}

TEST_CASE("Returns the amount of free capacity the vector has available.",
          "[Free Capacity]") {
  Vector<int> vector{1, 2, 3, 4, 5};

  REQUIRE(vector.Size() == 5);
  REQUIRE(vector.Capacity() == 5);
  REQUIRE(vector.FreeCapacity() == 0);

  vector.PushBack(6);

  REQUIRE(vector.Size() == 6);
  REQUIRE(vector.Capacity() == 10);
  REQUIRE(vector.FreeCapacity() == 4);

  vector.Reserve(20);

  REQUIRE(vector.Size() == 6);
  REQUIRE(vector.Capacity() == 20);
  REQUIRE(vector.FreeCapacity() == 14);
}

// TEST_CASE(
//     "Removes elements in the Vector which suffice the passed in Function. "
//     "Returns the amount of elements which were removed.",
//     "[Remove If]") {
//   SECTION("") {
//     //
//   }

//   Vector<int> vectorOne{1, 2, 3, 4, 5};
// }
