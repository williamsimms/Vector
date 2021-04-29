CC=clang
CXX=clang++
CXXFLAGS=-std=c++20 -Wall -Wpedantic -Wextra

build:
	clang++ $(CXXFLAGS) main.cpp 

run:
	clang++ $(CXXFLAGS) -o main main.cpp && ./main && rm -f main

test:
	clang++ $(CXXFLAGS) -o vector vector.test.cpp && ./vector && rm -f vector

clean:
	rm -f a.exe main main.pdb main.ilk vector

debug:
	clang++ $(CXXFLAGS) -g -o main main.cpp 