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