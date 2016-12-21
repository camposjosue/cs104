#include "llistdbl.h"
#include <cstdlib>

LListDbl::LListDbl()
{
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;
}

LListDbl::~LListDbl()
{
  clear();
}

bool LListDbl::empty() const
{
  return size_ == 0;
}

int LListDbl::size() const
{
  return size_;
}

/**
 * Complete the following function
 */
void LListDbl::insert(int loc, const double& val)
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
void LListDbl::remove(int loc)
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

void LListDbl::set(int loc, const double& val)
{
  Item *temp = getNodeAt(loc);
  temp->val = val;
}

double& LListDbl::get(int loc)
{
  Item *temp = getNodeAt(loc);
  return temp->val;
}

double const & LListDbl::get(int loc) const
{
  Item *temp = getNodeAt(loc);
  return temp->val;
}

void LListDbl::clear()
{
  while(head_ != NULL){
    Item *temp = head_->next;
    delete head_;
    head_ = temp;
  }
  tail_ = NULL;
  size_ = 0;
}


LListDbl::Item* LListDbl::getNodeAt(int loc) const
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
