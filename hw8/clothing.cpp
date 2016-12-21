#include "clothing.h"
#include "util.h"
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

Clothing::Clothing(const std::string category, const std::string name, double price, int qty,
		std::string size, std::string brand):
	Product(category, name, price, qty)
{
	size_=size;
	brand_=brand;
}

Clothing::~Clothing(){}

std::set<std::string> Clothing::keywords()const{
	std::set<std::string> holder= parseStringToWords(getName());
	holder.insert(getName());
	std::set<std::string> more= (parseStringToWords(brand_));
	holder = setUnion(more,holder);

	return holder;
}

std::string Clothing::displayString()const{
	
	stringstream a,b;

	a<< getPrice();
	b<< getQty();

	string howmuch = a.str();
	string howmany = b.str();

	string output = getName() + '\n' + "Size: " + size_ + " Brand: " + brand_ + '\n'
		+ howmuch + " " + howmany + " left ";  
	return output;

}

void Clothing::dump(std::ostream& os)const{
	os << "clothing" << "\n" << getName() << "\n" << getPrice() << "\n" << getQty();
	os << "\n" << size_ << "\n" << brand_;
}

bool Clothing::isMatch(std::vector<std::string>& searchTerms) const{
	return false;
}

string Clothing::getSize(){
	return size_;
}

string Clothing::getBrand(){
	return brand_;
}

