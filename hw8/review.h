#ifndef REVIEW_H
#define REVIEW_H
#include <string>

/**
 * Models a review for the product identified by prodName
 */
struct Review
{
  Review() :  prodName(), rating(), date(), reviewText(), username()
  { }
  Review(std::string& prod, 
	 int& rate, 
	 std::string& d, 
	 std::string& review_text, 
   std::string& user) :
    prodName(prod), 
    rating(rate), 
    date(d), 
    reviewText(review_text),
    username(user)
  { }
  
  std::string prodName;
  int rating;
  std::string date;
  std::string reviewText;
  std::string username;
};

#endif
