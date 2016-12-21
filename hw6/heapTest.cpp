#include "heap.h"
#include "gtest/gtest.h"
#include <functional>

using namespace std;

// struct IntComp {
//     bool operator()(const int& lhs, const int& rhs) 
//     { // Uses string's built in operator< 
//       // to do lexicographic (alphabetical) comparison
//       return lhs < rhs; 
//     }
// };



TEST(HeapTest, HappyTest) {
	Heap<int, less<int> > list(2, less<int>());
	list.push(8);
	list.push(9);
	list.push(3);
	EXPECT_EQ(list.top(), 3);
	list.pop();
	EXPECT_EQ(list.top(), 8);
	list.pop();
	EXPECT_EQ(list.top(), 9);
}

TEST(HeapTest, sadTest) {
	Heap<int, less<int> > list(2, less<int>());
	list.push(8);
	list.push(9);
	list.push(3);
	EXPECT_EQ(list.top(), 3);
	list.pop();
	EXPECT_EQ(list.top(), 8);
	list.pop();
	EXPECT_EQ(list.top(), 9);
	list.pop();
	list.push(25);
	list.push(7);
	list.push(2);
	EXPECT_EQ(list.top(), 2);
	list.pop();
	EXPECT_EQ(list.top(), 7);
	list.pop();
	EXPECT_EQ(list.top(), 25);
	list.push(6);
	EXPECT_EQ(list.top(), 6);
	list.push(9);
	list.push(15);
}

TEST(HeapTest, notSoHappyTest) {
	Heap<int, less<int> > list(2, less<int>());
	list.push(8);
	list.push(9);
	list.push(3);
	EXPECT_EQ(list.top(), 3);
	list.pop();
	EXPECT_EQ(list.top(), 8);
	list.pop();
	EXPECT_EQ(list.top(), 9);
	list.push(5);
	EXPECT_EQ(list.top(), 5);
	list.push(7);
	list.push(32);
	list.push(98);
	list.push(3);
	EXPECT_EQ(list.top(), 3);
}

TEST(HeapTest, semiHappyTest) {
	Heap<int, less<int> > list(4, less<int>());
	list.push(8);
	list.push(9);
	list.push(3);
	EXPECT_EQ(list.top(), 3);
	list.pop();
	EXPECT_EQ(list.top(), 8);
	list.pop();
	EXPECT_EQ(list.top(), 9);
	list.push(5);
	EXPECT_EQ(list.top(), 5);
	list.push(7);
	list.push(32);
	list.push(98);
	list.push(3);
	EXPECT_EQ(list.top(), 3);
	list.push(10);
	list.pop();
	EXPECT_EQ(list.top(), 5);
	list.pop();
	EXPECT_EQ(list.top(), 7);
	// for(unsigned int i = 0; i<list.items.size(); i++){
	// 	cout<<list.items[i]<<endl;
	// }
}

TEST(HeapTest, kindaHappyTest) {
	Heap<int, less<int> > list(3, less<int>());
	list.push(8);
	list.push(9);
	list.push(3);
	EXPECT_EQ(list.top(), 3);
	list.pop();
	EXPECT_EQ(list.top(), 8);
	list.pop();
	EXPECT_EQ(list.top(), 9);
	list.push(5);
	EXPECT_EQ(list.top(), 5);
	list.push(7);
	list.push(32);
	list.push(98);
	list.push(3);
	EXPECT_EQ(list.top(), 3);
	list.push(10);
	list.pop();
	EXPECT_EQ(list.top(), 5);
	list.pop();
	EXPECT_EQ(list.top(), 7);
	 // for(unsigned int i = 0; i<list.items.size(); i++){
	 // 	cout<<list.items[i]<<endl;
	 // }
}

TEST(HeapTest, sortaHappyTest) {
	Heap<int, less<int> > list(5, less<int>());
	list.push(8);
	list.push(9);
	list.push(3);
	EXPECT_EQ(list.top(), 3);
	list.pop();
	EXPECT_EQ(list.top(), 8);
	list.pop();
	EXPECT_EQ(list.top(), 9);
	list.push(5);
	EXPECT_EQ(list.top(), 5);
	list.push(7);
	list.push(32);
	list.push(98);
	list.push(3);
	EXPECT_EQ(list.top(), 3);
	list.push(10);
	list.pop();
	EXPECT_EQ(list.top(), 5);
	list.pop();
	EXPECT_EQ(list.top(), 7);
	 // for(unsigned int i = 0; i<list.items.size(); i++){
	 // 	cout<<list.items[i]<<endl;
	 // }
}

