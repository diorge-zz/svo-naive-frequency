CXX=g++
CXXFLAGS=-std=c++11 -Wall -pedantic
RM=rm -f

SRC=naivefrequency.cpp
OBJ=naivefrequency

naivefrequency:
	$(CXX) $(CXXFLAGS) -O3 -o $(OBJ) $(SRC)

naivefrequency2:
	$(CXX) $(CXXFLAGS) -O2 -o $(OBJ) $(SRC)

clean:
	$(RM) $(OBJ)
