#include "alistint.h"
#include <cstdlib>

AListInt::AListInt(){
	box = new int[10];
	size_ = 0;
	max = 10;
}

AListInt::AListInt(int cap){
	box = new int[cap];
	size_ = 0;
	max = cap;
}

AListInt::~AListInt(){
	delete [] box;
}

  /**
   * Standard List interface
   */

  /**
   * Returns the current number of items in the list 
   */
int AListInt::size() const{
	return size_;
}
  
  /**
   * Returns true if the list is empty, false otherwise
   */
bool AListInt::empty() const{
	if(size_==0)
		return true;
	else
		return false;
}

  /**
   * Inserts val so it appears at index, pos
   */
void AListInt::insert (int pos, const int& val){
	if(size_==max)
		resize();
	if(pos<0 || pos>size_)
		return;
	else if(pos == size_){
		box[pos]=val;
		size_++;
	}
	else{
		for(int i=size_; i>pos; i--){
			box[i]=box[i-1];
		}
		box[pos]=val;
		size_++;
	}
}

  /**
   * Removes the value at index, pos
   */
void AListInt::remove (int pos){
	if(pos<0 || pos>=size_)
		return;
	else if(pos == size_-1){
		size_--;
	}
	else{
		for(int i=pos; i<size_-1; i++){
			box[i]=box[i+1];
		}
		size_--;
	}
}

  /**
   * Overwrites the old value at index, pos, with val
   */
void AListInt::set (int position, const int& val){
	if(position<0 || position>size_)
		return;
	else{
		box[position]=val;
	}

}

  /**
   * Returns the value at index, pos
   */
int& AListInt::get (int position){
	if(position >= size_ || position < 0)
		return box[0];
	else
		return box[position];
} 

  /**
   * Returns the value at index, pos
   */
int const & AListInt::get (int position) const{
	if(position >= size_ || position < 0)
		return box[0];
	else
		return box[position];
}
  

void AListInt::resize(){
	int * temp;
	temp = new int[max*2];
	max = max*2;
	for(int i =0; i<size_-1;i++){
		temp[i]=box[i];
	}
	delete [] box;
	box = temp;
	delete [] temp;
}
   
  /* Add necessary data members here */
