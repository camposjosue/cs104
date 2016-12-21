CXXFLAGS = -g -Wall 
GTEST_LL = -I /usr/local/opt/gtest/include/ -l gtest -l gtest_main -pthread

all: heaptest board.o puzzle_solver.o puzzle_heur.o puzzle_move.o puzzle

puzzle: board.o puzzle_move.o puzzle_heur.o puzzle_solver.o
	g++ $(CXXFLAGS) board.o puzzle_move.o puzzle_heur.o puzzle_solver.o puzzle.cpp -o puzzle

heaptest: heap.h heapTest.cpp
	g++ $(CXXFLAGS) heapTest.cpp $(GTEST_LL) -o heaptest

bin/board.o: board.h board.cpp
	g++ $(CXXFLAGS) -c board.cpp -o board.o

bin/puzzle_solver.o: puzzle_solver.h puzzle_solver.cpp heap.h board.h puzzle_heur
	g++ $(CXXFLAGS) -c puzzle_solver.cpp -o puzzle_solver.o

bin/puzzle_heur.o: puzzle_heur.cpp puzzle_heur.h  board.h
	g++ $(CXXFLAGS) -c puzzle_heur.cpp -o puzzle_heur.o

bin/puzzle_move.o: puzzle_move.h puzzle_move.cpp
	g++ $(CXXFLAGS) -c puzzle_move.cpp -o puzzle_move.o



.PHONY: clean

clean: 
	rm -rf heaptest
	rm -rf board.o
	rm -rf puzzle_solver.o
	rm -rf puzzle_heur.o
	rm -rf puzzle_move.o 
	rm -rf puzzle
