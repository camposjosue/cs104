#include "movie.h"
#include "util.h"
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

Movie::Movie(const std::string category, const std::string name, double price, int qty,
		std::string genre, std::string rating):
	Product(category, name, price, qty)
{
	genre_=genre;
	rating_=rating;
}
Movie::~Movie(){}

std::set<std::string> Movie::keywords()const{
	std::set<std::string> holder= parseStringToWords(getName());
	holder.insert(getName());
	std::set<std::string> more= (parseStringToWords(genre_));
	holder = setUnion(holder,more);

	return holder;
} 
	
std::string Movie::displayString()const{
	stringstream a,b;

	a<< getPrice();
	b<< getQty();

	string howmuch = a.str();
	string howmany = b.str();

	string output = getName() + '\n' + "Genre: " + genre_ + " Rating: " + rating_ + '\n'
		+ howmuch + " " + howmany + " left ";  
	return output;
}

void Movie::dump(std::ostream& os)const{
	os << "movie" << "\n"<< getName() << "\n"<< getPrice() << "\n"<< getQty();
	os << "\n"<< genre_ << "\n"<< rating_;
}

bool Movie::isMatch(std::vector<std::string>& searchTerms) const{
	return false;
}


string Movie::getGenre(){
	return genre_;
}

string Movie::getRating(){
	return rating_;
}
