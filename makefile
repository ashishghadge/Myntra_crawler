CURL=-lcurl 
CXXFLAGS=-g -Wall -std=c++11

all: Myntra

Myntra: Myntra.o CurlObj.o Data.o
	g++ $(CXXFLAGS) -o Myntra Myntra.o Data.o CurlObj.o $(CURL)

Myntra.o: Myntra.cpp Data.hpp CurlObj.hpp
	g++ $(CXXFLAGS) -c Myntra.cpp 

CurlObj.o: CurlObj.hpp CurlObj.cpp
	g++ $(CXXFLAGS) -c CurlObj.cpp $(CURL)

Data.o: Data.hpp Data.cpp
	g++ $(CXXFLAGS) -c Data.cpp 

clean:
	-rm -f *.o Myntra
