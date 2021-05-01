#include <iostream>

#include "Vector3.hpp"
#include "vector.hpp"

using namespace std;

int main() {
  Vector<int> vector{1, 2, 3, 4};

  int x = 12;
  vector.Insert(3, x);

  cout << vector;

  return 0;
}