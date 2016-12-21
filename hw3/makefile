CXXFLAGS = -g -Wall 
GTEST_LL = -I /usr/local/opt/gtest/include/ -l gtest -l gtest_main -pthread

all: copytest settest pgindex

copytest: llistint.o copytest.cpp
	g++ $(CXXFLAGS) copytest.cpp llistint.o $(GTEST_LL) -o copytest

bin/llistint.o: llistint.h llistint.cpp
	g++ $(CXXFLAGS) -c llistint.cpp -o llistint.o

settest: setint.o settest.cpp llistint.o 
	g++ $(CXXFLAGS) settest.cpp llistint.o setint.o $(GTEST_LL) -o settest

bin/setint.o: setint.h setint.cpp 
	g++ $(CXXFLAGS) -c setint.cpp -o setint.o

pgindex: llistint.o setint.o pgindex.cpp
	g++ $(CXXFLAGS) pgindex.cpp setint.o llistint.o $(GTEST_LL) -o pgindex

.PHONY: clean

clean: 
	rm -rf copytest
	rm -rf settest
	rm -rf llistint.o
	rm -rf setint.o
	rm -rf copytest
	rm -rf pgindex
	













