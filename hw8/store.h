#ifndef STORE_H
#define STORE_H
#include <set>
#include <vector>
#include <map>
#include "product.h"
#include "user.h"
#include "util.h"
#include "datastore.h"
#include "book.h"
#include "clothing.h"
#include "movie.h"
#include "skiplist.h"

/** 
 * DataStore Interface needed for parsing and instantiating products and users
 *
 * A derived version of the DataStore can provide other services as well but
 * must support those below
 */
class Store : public DataStore {


  public: 
    Store();
    ~Store();

  /**
   * Adds a product to the data store
   */
    void addProduct(Product* p);
 
  /**
   * Adds a user to the data store
   */
    void addUser(User* u);

  /**
   * Adds a review
   */
  void addReview(Review* r);
  /**
   * Performs a search of products whose keywords match the given "terms"
   *  type 0 = AND search (intersection of results for each term) while
   *  type 1 = OR search (union of results for each term)
   */
  std::vector<Product*> search(std::vector<std::string>& terms, int type);

  /**
   * Reproduce the database file from the current Products and User values
   */
    void dump(std::ostream& ofile);

    void addCart(std::string buyer, Product*p);
    std::vector<Product* > viewCart(std::string buyer);
    void buyCart(std::string buyer);
    std::vector<User*> getUsers();

    std::vector<Review*> reviews;
    void removeCart(std::string username, int index);
    std::vector<Product*> getProducts();
    void setSynonyms(std::map<std::string, std::set<std::string> > dict);

    SkipList* fuckers; 


  protected:
    std::map<std::string, std::set<Product*> > keys;
    std::vector<User*> users;
    std::vector<Product*> products;
    User* u;
    std::map<std::string, std::vector<Product*> > cart;
    std::map<std::string, std::set<std::string> > synonyms;
};

#endif
