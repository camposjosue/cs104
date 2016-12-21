#include "skiplist.h"

using namespace std;

SkipList::SkipList(){

	string dummy1 = "dummy";
	User* dummy2 = NULL;
	currentLevel = 0;


 	maxLevel = 5;
 	head = new SkipNode(dummy1,dummy2,maxLevel);

 	string INFINITY = "zzzzzzzzzzzzzz";

	SkipNode* end = new SkipNode(INFINITY,dummy2,maxLevel);
 	for(int i=0; i < maxLevel; i++){
 		head->forward[i] = end;
	}
}

SkipList::~SkipList(){

}

User* SkipList::search( std::string& key){
 	SkipNode*  current = head;
 	for(int i=currentLevel; i >= 0; i--){
 		while( current->forward[i]->key < key){
 			current = current->forward[i];
 		}
 	}

 	current = current->forward[0];

 // will always stop on level 0 w/ current=node
 // just prior to the actual target node or End node

 	//current = current->forward[0];
 	if(current->key == key) return current->value;
 	else return NULL; // current wa

}

void SkipList::insert(string key, User* v){
 	SkipNode*  current = head;
	vector<SkipNode*> update(maxLevel+1);


	for(int i=currentLevel; i >= 0; i--){
 		while( current->forward[i]->key < key){
 			current = current->forward[i];
 			
 		}
 		update[i] = current;
 	}


// perform typical search but fill in update array
//...
	 current = current->forward[0];

	if(current->key == key)
 		{ current->value = v; return; }
 	else {
 		int height = randomLevel();

 		if(height > currentLevel){

 			for(int i = currentLevel+1; i<= height; i++){
 				update[i] = head;
 			}
 			currentLevel=height;
 		}


 		// Allocate new node, x
 		SkipNode* x = new SkipNode(key, v, maxLevel);
 		for(int i=0; i < height; i++){
 			x->forward[i] = update[i]->forward[i];
 			update[i]->forward[i] = x;
		} 
	}
}

int SkipList::randomLevel()
{
 	int height = 1;
	// assume rand() returns double in range [0,1)
	while(rand() % 2 < 0.5 && height < maxLevel){
 		height++;
	}
	return height;
}