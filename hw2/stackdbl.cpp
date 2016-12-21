#include "stackdbl.h"
#include "llistdbl.h"
#include <cstdlib>
/**
   * Returns true if the stack is empty, false otherwise

   */
StackDbl::StackDbl(){}

StackDbl::~StackDbl(){
  list_.clear();
}

bool StackDbl::empty() const{
  if(list_.size()== 0)
    return true;
  else
    return false;
}

  /**
   * Pushes a new value, val, onto the top of the stack
   */
void StackDbl::push(const double& val){
  list_.insert(list_.size(), val);
  // Item* temp = new Item;
  // temp->val = val;
  // tail->next=temp;
  // temp->prev=tail;
  // temp->next=NULL;
  // tail=temp;
  // size_++;
}

  /**
   * Returns the top value on the stack
   */
double const &  StackDbl::top() const{
  return list_.get(list_.size()-1);

}

  /**
   * Removes the top element on the stack
   */
void StackDbl::pop(){
  list_.remove(list_.size()-1);

  // Item* temp = tail -> prev;
  // temp->next =NULL;
  // delete tail;
  // tail = temp;
}

 