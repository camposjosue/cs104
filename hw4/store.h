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
    void viewCart(std::string buyer);
    void buyCart(std::string buyer);



  protected:
    std::map<std::string, std::set<Product*> > keys;
    std::vector<User*> users;
    std::vector<Product*> products;
    std::map<std::string, std::vector<Product*> > cart;

};

#endif
