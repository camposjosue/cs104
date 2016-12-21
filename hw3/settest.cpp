#include "llistint.h"
#include "setint.h"
#include "gtest/gtest.h"

TEST(SetIntTest, insert) {
	SetInt set;
	set.insert(4);
	EXPECT_EQ(set.exists(4), true);
	set.insert(863);
	EXPECT_EQ(set.exists(863), true);
	set.insert(22);
	EXPECT_EQ(set.exists(22), true);
	set.insert(37);
	EXPECT_EQ(set.exists(37), true);
	set.insert(1956);
	EXPECT_EQ(set.exists(1956), true);
	set.insert(7);
	EXPECT_EQ(set.exists(7), true);
	set.insert(4);
	EXPECT_EQ(set.size(), 6);
}

TEST(SetIntTest, remove) {
	SetInt set;
	set.insert(4);
	EXPECT_EQ(set.exists(4), true);
	set.insert(863);
	EXPECT_EQ(set.exists(863), true);
	set.insert(7);
	EXPECT_EQ(set.exists(7), true);
	set.insert(4);
	EXPECT_EQ(set.size(), 3);
	set.remove(4);
	EXPECT_EQ(set.size(),2);
	EXPECT_EQ(set.empty(),false);
	set.remove(4);
	EXPECT_EQ(set.size(),2);
	set.remove(7);
	EXPECT_EQ(set.size(),1);
	set.remove(863);
	EXPECT_EQ(set.size(),0);
	EXPECT_EQ(set.empty(),true);
}

TEST(SetIntTest, iterator) {
	SetInt set;
	set.insert(24);
	EXPECT_EQ(set.exists(24), true);
	set.insert(8639);
	EXPECT_EQ(set.exists(8639), true);
	set.insert(127);
	EXPECT_EQ(set.exists(127), true);
	// set.first();
	// EXPECT_EQ(set.first()., 24);
	// set.next();
	// EXPECT_EQ(set.next(), 8639);
	// set.next();
	// EXPECT_EQ(set.next(), 127);
}

TEST(SetIntTest, comparators){
	SetInt set;
	SetInt set2;
	set.insert(24);
	EXPECT_EQ(set.exists(24), true);
	set.insert(8639);
	EXPECT_EQ(set.exists(8639), true);
	set.insert(127);
	EXPECT_EQ(set.exists(127), true);
	set2.insert(24);
	EXPECT_EQ(set2.exists(24), true);
	set2.insert(39);
	EXPECT_EQ(set2.exists(39), true);
	set2.insert(17);
	EXPECT_EQ(set2.exists(17), true);
	SetInt set3 = set | set2;
	set3.size();
	EXPECT_EQ(set3.size(),5);
	EXPECT_EQ(set3.exists(24), true);
	EXPECT_EQ(set3.exists(8639), true);
	EXPECT_EQ(set3.exists(127), true);
}

TEST(SetIntTest, union){
	SetInt set;
	SetInt set2;
	set.insert(24);
	EXPECT_EQ(set.exists(24), true);
	set.insert(8639);
	EXPECT_EQ(set.exists(8639), true);
	set.insert(127);
	EXPECT_EQ(set.exists(127), true);
	set2.insert(24);
	EXPECT_EQ(set2.exists(24), true);
	set2.insert(39);
	EXPECT_EQ(set2.exists(39), true);
	set2.insert(17);
	EXPECT_EQ(set2.exists(17), true);
	SetInt set3 = set.setUnion(set2);
	set3.size();
	EXPECT_EQ(set3.size(),5);
	EXPECT_EQ(set3.exists(24), true);
	EXPECT_EQ(set3.exists(8639), true);
	EXPECT_EQ(set3.exists(127), true);
}

TEST(SentIntTest, anding){
	SetInt set;
	SetInt set2;
	set.insert(24);
	set.insert(93);
	EXPECT_EQ(set.exists(24), true);
	EXPECT_EQ(set.exists(93), true);
	set.insert(8639);
	EXPECT_EQ(set.exists(8639), true);
	set.insert(127);
	EXPECT_EQ(set.exists(127), true);
	set2.insert(24);
	EXPECT_EQ(set2.exists(24), true);
	set2.insert(39);
	EXPECT_EQ(set2.exists(39), true);
	set2.insert(17);
	EXPECT_EQ(set2.exists(17), true);
	set2.insert(127);
	EXPECT_EQ(set2.exists(127), true);
	SetInt set3 = set & set2;
	set3.size();
	EXPECT_EQ(set3.size(),2);
	EXPECT_EQ(set3.exists(24), true);
	EXPECT_EQ(set3.exists(127), true);

}

TEST(SentIntTest, intersection){
	SetInt set;
	SetInt set2;
	set.insert(24);
	set.insert(93);
	EXPECT_EQ(set.exists(24), true);
	EXPECT_EQ(set.exists(93), true);
	set.insert(8639);
	EXPECT_EQ(set.exists(8639), true);
	set.insert(127);
	EXPECT_EQ(set.exists(127), true);
	set2.insert(24);
	EXPECT_EQ(set2.exists(24), true);
	set2.insert(39);
	EXPECT_EQ(set2.exists(39), true);
	set2.insert(17);
	EXPECT_EQ(set2.exists(17), true);
	set2.insert(127);
	EXPECT_EQ(set2.exists(127), true);
	SetInt set3 = set.setIntersection(set2);
	set3.size();
	EXPECT_EQ(set3.size(),2);
	EXPECT_EQ(set3.exists(24), true);
	EXPECT_EQ(set3.exists(127), true);

}