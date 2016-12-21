all: problem3 problem3_test problem4 problem4_test problem5 problem5_test problem6

problem3: llistdbl.h
	g++ -g -c -Wall llistdbl.cpp -o LListDbl.o

problem3_test: 
	g++ -g -Wall tests/testAddToEmptyList.cpp LListDbl.o -o problem3

problem4: alistint.h
	g++ -g -c -Wall alistint.cpp -o AListInt.o

problem4_test:
	g++ -g -Wall tests/test_array.cpp AListInt.o -o problem4

problem5: stackdbl.h
	g++ -g -c -Wall stackdbl.cpp -o StackDbl.o

problem5_test:
	g++ -g -Wall tests/test_stack.cpp llistdbl.cpp StackDbl.o -o problem5

problem6: 
	g++ -g -Wall calculator.cpp stackdbl.cpp llistdbl.cpp -o calculator