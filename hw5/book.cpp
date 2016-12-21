  #include "book.h"
#include "util.h"
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

Book::Book(const std::string category, const std::string name, double price, int qty,
		std::string ISBN, std::string author):
	Product(category, name, price, qty)
{
	ISBN_=ISBN;
	author_=author;

}

Book::~Book(){}

std::set<std::string> Book::keywords() const{
	std::set<std::string> holder= parseStringToWords(getName());
	holder.insert(getName());
	holder.insert(ISBN_);
	std::set<std::string> more= (parseStringToWords(author_));
	holder = setUnion(holder,more);
	return holder;
}

//all info in one continuous string
std::string Book::displayString()const{

	stringstream a,b;

	a<< getPrice();
	b<< getQty();

	string howmuch = a.str();
	string howmany = b.str();

	string output = getName() + '\n' + "ISBN: " + ISBN_ + " Author: " + author_ + '\n'
		+ howmuch + " " + howmany + " left ";  
	return output;
 }

//outputs data into format
void Book::dump(std::ostream& os)const{
	os << "book" << "\n" << getName() << "\n" << getPrice() << "\n" << getQty();
	os << "\n" << ISBN_ << "\n" << author_;
}


bool Book::isMatch(std::vector<std::string>& searchTerms) const{
	return false;
}


std::string Book::getISBN(){
	return ISBN_;
}

std::string Book::getAuthor(){
	return author_;
}
