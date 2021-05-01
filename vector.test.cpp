#define CATCH_CONFIG_MAIN

#include "vector.hpp"

#include <vector>

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
    REQUIRE(vector.Size() == 3);

    vector.PopBack();
    REQUIRE(vector.Size() == 2);
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

  REQUIRE(vector.Capacity() == 8);
  REQUIRE(vector.Size() == 4);
}

TEST_CASE("Returns true if the vector is empty, otherwise returns true.",
          "[Empty]") {
  SECTION("Returns true if the list is empty.") {
    //
  }

  SECTION("Returns false if the list is not empty.") {
    //
  }
}

TEST_CASE("Returns true if the vector is empty, otherwise returns true.",
          "[Front]") {
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

TEST_CASE("Returns true if the vector is empty, otherwise returns true.",
          "[Back]") {}

TEST_CASE("Returns true if the vector is empty, otherwise returns true.",
          "[Middle]") {}
