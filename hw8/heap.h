#ifndef HEAP_H
#define HEAP_H

#include <vector>
#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <ostream>

template <typename T, typename Comparator >
class Heap
{
 public:
  /// Constructs an m-ary heap for any m >= 2
  Heap(int m, Comparator c){
  	//items.push_back(0);
  	divider=m;
  	comp = c;
  }

  /// Destructor as needed
  ~Heap(){}

  /// Adds an item
  void push(const T& item);

  /// returns the element at the top of the heap 
  ///  max (if max-heap) or min (if min-heap)
  T const & top() const;

  /// Removes the top element
  void pop();

  /// returns true if the heap is empty
  bool empty() const;

  // std::vector<T> items;

 private:
  /// Add whatever helper functions and data members you need below
 	void trickleUp(int loc);
 	void heapify(int idx);
 	std::vector<T> items;
 	Comparator comp;
 	int divider;



};

// Add implementation of member functions here


// We will start top() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename Comparator>
T const & Heap<T,Comparator>::top() const
{
  // Here we use exceptions to handle the case of trying
  // to access the top element of an empty heap
  if(empty()){
    throw std::logic_error("can't top an empty heap");
  }
  // If we get here we know the heap has at least 1 item
  // Add code to return the top element
  //std::cout<<"HEAP SIZE: "<<items.size();
  return items[0];

}


// We will start pop() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename Comparator>
void Heap<T,Comparator>::pop()
{
  if(empty()){
    throw std::logic_error("can't pop an empty heap");
  }

  items[0]=items[items.size()-1];
  items.pop_back();
  if(empty())
  	return;
  //std::cout<<"THIS IS THE ITEM"<<items[0]<<std::endl;;
  heapify(0);



}


template <typename T, typename Comparator>
void Heap<T, Comparator>::push(const T& item){
	items.push_back(item);
	trickleUp(items.size()-1);

}

template <typename T, typename Comparator>
bool Heap<T, Comparator>::empty() const{

	if(items.size()==0)
		return true;
	else
		return false;
}

template <typename T, typename Comparator>
void Heap<T, Comparator>::trickleUp(int loc){
	int parent = (loc-1)/divider;
	while(parent >=0 && comp(items[loc],items[parent])){
		std::swap(items[parent],items[loc]);
		// T temp = items[parent];
		// items[parent] = items[loc];
		// items[loc]= temp;
		loc = parent;
		parent = (loc-1)/divider;
	}
}


template <typename T, typename Comparator>
void Heap<T, Comparator>::heapify(int idx){
	if((idx*divider)+1>items.size()-1)
		return; 
	int smallerChild = (divider*idx)+1; // start w/ left
 	int firstChild = (divider*idx)+1;
 	for(int i = 1; i<divider; i++){
 		if((idx*divider)+i<=items.size()-1) {

 			int rChild = firstChild+i;
 			if(comp(items[rChild],items[smallerChild]))
 				smallerChild = rChild;
 		}
	}

	if(comp(items[smallerChild],items[idx])){
 		// T temp = items[idx];
 		// items[idx] = items[smallerChild];
 		// items[smallerChild]= temp;
 		std::swap(items[smallerChild],items[idx]);
 		heapify(smallerChild);
	}

}



#endif

