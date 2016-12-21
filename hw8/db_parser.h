#ifndef DBPARSER_H
#define DBPARSER_H
#include <iostream>
#include <string>
#include <map>
#include "datastore.h"
#include "product.h"
#include "user.h"
#include "product_parser.h"
#include "review.h"

class DBParser {
 public:
  DBParser();
  virtual ~DBParser();
  void addProductParser(ProductParser* p);
  bool parse(std::string db_filename, DataStore& ds);
  bool parseDictionary(std::string db_filename, DataStore& ds);

 protected:
  enum PState { INIT, PRODUCTS, FIND_USERS, READ_USERS, FIND_REVIEWS, READ_REVIEWS, DONE, SYNONYMS };

  Product* parseProduct(const std::string& category, 
			std::istream& is);



  virtual User* parseUser(std::istream& is);
  virtual void parseLine( std::istream& is);

  virtual Review* parseReview(std::istream& is, 
			      std::string prodname); 

  virtual Review* makeReview(std::string& prodname, 
			     int& rating, 
			     std::string& date, 
			     std::string& review_text,
           std::string& user);
 private:
  int lineno_;
  std::string errorMsg_;
  bool error_;
  std::map<std::string, ProductParser*> parsers_;
  std::map<std::string, std::set<std::string > > dict;

};

#endif
