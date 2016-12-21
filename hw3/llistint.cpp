#include "llistint.h"
#include <cstdlib>

LListInt::LListInt()
{
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;
}

LListInt::~LListInt()
{
  clear();
}

bool LListInt::empty() const
{
  return size_ == 0;
}

int LListInt::size() const
{
  return size_;
}

/**
 * Complete the following function
 */
void LListInt::insert(int loc, const int& val)
{
	Item* temp = new Item;
	temp->val = val;
	if(loc < 0 || loc > size_){
		return;
	}
	else if(loc==0){
		if(head_==NULL){
			head_ = temp;
			tail_ = temp;
			temp->next = NULL;
			temp->prev = NULL;
		}
		else{
			head_->prev = temp;
			temp->next = head_;
			temp->prev = NULL;
			head_ = temp;
		}
		size_++;
	}
	else if(loc==size_ && loc != 0){
		tail_->next = temp;
		temp->prev = tail_;
		temp->next = NULL;
		tail_ = temp;
		size_++;
	}
	else{
		Item* place = getNodeAt(loc);
		temp->prev = place->prev;
		(place->prev)->next=temp;
		place->prev = temp;
		temp->next = place;
		size_++;
	}


}

/**
 * Complete the following function
 */
void LListInt::remove(int loc)
{
	Item* place = getNodeAt(loc);
	if(size_==0){
		return;
	}
	else if(loc < 0 || loc >= size_){
		return;
	}
	else if(loc == 0){
		
		if(head_->next == NULL){
			//delete head;
			head_=NULL;
			tail_=NULL;
			delete place;
		}
		else{
			head_=place->next;
			(place->next)->prev=NULL;
			delete place;
		}
		size_--;
	}
	else if(loc==size_-1 && loc != 0){
		tail_=place->prev;
		tail_->next=NULL;
		delete place;
		size_--;
	}
	else{
		(place->prev)->next = (place->next);
		(place->next)->prev = (place->prev);
		delete place;
		size_--;
	}
}

void LListInt::set(int loc, const int& val)
{
  Item *temp = getNodeAt(loc);
  temp->val = val;
}

int& LListInt::get(int loc)
{
  Item *temp = getNodeAt(loc);
  return temp->val;
}

int const & LListInt::get(int loc) const
{
  Item *temp = getNodeAt(loc);
  return temp->val;
}

void LListInt::clear()
{
  while(head_ != NULL){
    Item *temp = head_->next;
    delete head_;
    head_ = temp;
  }
  tail_ = NULL;
  size_ = 0;
}


LListInt::Item* LListInt::getNodeAt(int loc) const
{
  Item *temp = head_;
  if(loc >= 0 && loc < size_){
    while(temp != NULL && loc > 0){
      temp = temp->next;
      loc--;
    }
    return temp;
  }
  else {
    //throw std::invalid_argument("bad location");
    return NULL;
  }
}

/**
   * Adds an item to the back of the list in O(1) time
   */
void LListInt::push_back(const int& val){
	
	insert(size_,val);
	// Item* temp = new Item;
	// temp->val = val;

	// if(head_==NULL){
	// 	head_ = temp;
	// 	tail_ = temp;
	// 	temp->next = NULL;
	// 	temp->prev = NULL;
	// }
	// else{
	// 	tail_->next = temp;
	// 	temp->prev = tail_;
	// 	temp->next = NULL;
	// 	tail_ = temp;
	// 	size_++;
	// }
}

  /**
   * Copy constructor
   */
LListInt::LListInt(const LListInt& other){
	head_=NULL;
	tail_=NULL;
	size_=0;

	for(int i=0; i < other.size(); i++){
		push_back(other.get(i));
	}

}

  /**
   * Assignment Operator
   */
LListInt& LListInt::operator=(const LListInt& other){
	if(this == & other) //if list1 = list1
		{return *this;}
	 
	this->clear(); // frees up memory from list

	this->head_=NULL;
	this->tail_=NULL;
	this->size_=0;

	for(int i=0; i < other.size(); i++){
		this->push_back(other.get(i));
	}
	
	return *this;
};

