#ifndef BOOK_H
#define BOOK_H
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
#include "product.h"

class Book : public Product
{

public:
	Book(const std::string category, const std::string name, double price, int qty, 
		std::string ISBN, std::string author);
	~Book();
	std::set<std::string> keywords() const; 
	std::string displayString() const;
	void dump(std::ostream& os) const;
	bool isMatch(std::vector<std::string>& searchTerms) const;
	std::string getISBN();
	std::string getAuthor();
protected:
	std::string ISBN_;
	std::string author_;

};
#endif