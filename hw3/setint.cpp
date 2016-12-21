#include "llistint.h"
#include "setint.h"
#include <cstdlib>
#include <iostream>


  SetInt::SetInt(){

  }

  /**
   * Destructor
   */
  SetInt::~SetInt(){

  }

  /**
   * Returns the current number of items in the list 
   */
  int SetInt::size() const{
  	return list_.size();
  }

  /**
   * Returns true if the list is empty, false otherwise
   */
  bool SetInt::empty() const{
  	return list_.empty();
  }

  /**
   * Inserts val so it appears at index, pos
   */
  void SetInt::insert(const int& val){
  	bool found = false;
  	for(int i=0; i < list_.size(); i++){
  		if(list_.get(i) == val){
  			found = true;
  			return;
  		}
  	}
  	if(found == false)
  		list_.push_back(val);
  }

  /**
   * Removes the value at index, pos
   */
  void SetInt::remove(const int& val){
  	for(int i=0; i<list_.size(); i++){
  		if(list_.get(i) == val){
  			list_.remove(i);
  		}
  	}
  }

  /**
   * Returns true if the item is in the set
   */
  bool SetInt::exists(const int& val) const{
  	bool found = false;
  	for(int i=0; i < list_.size(); i++){
  		if(list_.get(i) == val){
  			found = true;
  			return found;
  		}
  	}
  	return found;
  }

  /**
   * Return a pointer to the first item
   *  and support future calls to next()
   */
  int const* SetInt::first(){
  	counter = 0;
    if(list_.empty()){
      return NULL;
    }
  	else{
      return &list_.get(0);
    }
  }

  /**
   * Return a pointer to the next item
   *  after the previous call to next
   *  and NULL if you reach the end
   */
  int const* SetInt::next(){
  	if(counter == list_.size()){
  		return NULL; //&list_.get(list_.size()-1);
  	}
  	else{
  		counter++;
  		return &list_.get(counter);
  	}
  }

  /**
   * Returns another (new) set that contains
   * the union of this set and "other"
   */
  SetInt SetInt::setUnion(const SetInt& other) const{
  	SetInt newset;
  	for(int i=0; i<other.size(); i++){
  		newset.insert(other.list_.get(i));
  	}
  	for(int i=0; i<this->size(); i++){
  		newset.insert(list_.get(i));
  	}
  	return newset;
  }

  /**
   * Returns another (new) set that contains
   * the intersection of this set and "other"
   */
  SetInt SetInt::setIntersection(const SetInt& other) const{
  	SetInt newset;
  	for(int i=0; i <other.size(); i++){
  		if(this->exists(other.list_.get(i))){
  			newset.insert(other.list_.get(i));
  		}
  	}
  	return newset;
  }

  SetInt SetInt::operator|(const SetInt& other) const{
  	return this->setUnion(other);
  }

  SetInt SetInt::operator&(const SetInt& other) const{
  	return this->setIntersection(other);
  }