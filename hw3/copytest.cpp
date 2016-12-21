#include "llistint.h"
#include "gtest/gtest.h"

TEST(LListIntTest, pushback) {
	LListInt list;
	list.push_back(3);
	EXPECT_EQ(list.get(0), 3);
	list.push_back(7);
	EXPECT_EQ(list.get(1), 7);
	list.push_back(2);
	EXPECT_EQ(list.get(2), 2);
}


TEST(LListIntTest, copy_constructor) {
	LListInt l1;
	l1.push_back(1);
	EXPECT_EQ(l1.get(0), 1);
	l1.push_back(2);
	EXPECT_EQ(l1.get(0), 1);
	LListInt l2(l1);
	EXPECT_EQ(l2.get(0), 1);
	EXPECT_EQ(l2.get(0), 1);
}

TEST(LListIntTest, assignment) {
	LListInt l1;
	l1.push_back(1);
	EXPECT_EQ(l1.get(0), 1);
	l1.push_back(2);
	EXPECT_EQ(l1.get(0), 1);
	LListInt l2;
	l2.push_back(35);
	EXPECT_EQ(l2.get(0), 35);
	l2=l1;
	EXPECT_EQ(l2.get(0), 1);
	EXPECT_EQ(l2.get(0), 1);
}
// TEST(FibTest, Boundary) {
//     Fibonacci f;
//     EXPECT_EQ(f.get(1), 1);
//     EXPECT_EQ(f.get(2), 1);
// }

// TEST(FibTest, OffNominal) {
//     Fibonacci f;
//     EXPECT_EQ(f.get(-1), 0);
// }
