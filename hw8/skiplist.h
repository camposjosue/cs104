#ifndef SKIPLIST_H
#define SKIPLIST_H

#include <vector>
#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <ostream>
#include <string>
#include <user.h>
#include <string>




struct SkipNode
{
	std::string key;
	User* value;
	SkipNode** forward; //array of ptrs


	SkipNode(std::string& k, User* v, int level){
 		key = k; 
 		value = v;
 		forward = new SkipNode*[level+1];
	} 
};

class SkipList{
	
	public:
		SkipList();

		~SkipList();

		User* search( std::string& key);

		void insert(std::string key, User* v);

		int randomLevel();
 	
 	private:

 		int maxLevel; // data members
		SkipNode* head;
		int currentLevel;



};

#endif
