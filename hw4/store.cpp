#include <set>
#include <map>
#include <vector>
#include "product.h"
#include "user.h"
#include "util.h"
#include "store.h"
#include "book.h"
#include "clothing.h"
#include "movie.h"
#include "db_parser.h"

using namespace std;

Store::Store(){}

Store::~Store() { 
  // delete products;
  // delete keywords;
  // delete users;
}

  /**
   * Adds a product to the data store
   */
void Store::addProduct(Product* p){
  products.push_back(p); //adding product to vector of product* 's'

  set<string> bubble= p->keywords();
  
  std::set<string>::iterator it;

  //add to the map of keywords with the keyword (string) as the key
  // and connecting it to a set of PRODUCTS*
  for(it = bubble.begin(); it != bubble.end(); ++it){
    std::map<string, set<Product*> >::iterator it2;
    it2=keys.find(*it);
    

    if(it2 == keys.end()){
      set<Product*> new_product;
      new_product.insert(p);
      keys.insert(make_pair(*it,new_product));  
    }
    else{
      it2->second.insert(p);
    }
  } 
}
 
  /**
   * Adds a user to the data store
   */
void Store::addUser(User* u){
  users.push_back(u);
  vector<Product*> basket;
  std::map<string,vector<Product*> >::iterator it = cart.find(u->getName());
  if(it == cart.end()){
    cart.insert(make_pair(u->getName(),basket));
  }
}

  /**
   * Performs a search of products whose keywords match the given "terms"
   *  type 0 = AND search (intersection of results for each term) while
   *  type 1 = OR search (union of results for each term)
   */
std::vector<Product*> Store::search(std::vector<std::string>& terms, int type){
  set<Product*> main; //set with all elements that match desription
  set<Product*> set1;
  vector<Product*> bucket;

  if(type == 0){ 
    for(unsigned int i=0; i < terms.size(); i++){
       map<string, set<Product*> >::iterator it;
       it=keys.find(terms[i]);
       if(it != keys.end()){
          set<Product*> set2 = it->second;
          if(i==0){
            set1 = set2;
          }
          if(terms.size()==1){
            main=set1;
            break;
          }
          else{
            set1 = setIntersection(set1,set2);
          }
       }
    }
    main = set1;
  }

  //the OR case
  else if(type ==1){
    for(unsigned int i=0; i < terms.size(); i++){
       map<string, set<Product*> >::iterator it;
       it=keys.find(terms[i]);

       if(it != keys.end()){
          set<Product*> set2 = it->second;
          if(i==0){
            set1 = set2;
          }
          if(terms.size()==1){
            main=set1;
            break;
          }
          else{
            set1 = setUnion(set1,set2);
          }
       }
    }
    main = set1;
  }
  for(std::set<Product*>::iterator it = main.begin(); it != main.end(); ++it){
    bucket.push_back(*it);
  }
  return bucket;
}

  /**
   * Reproduce the database file from the current Products and User values
   */
void Store::dump(std::ostream& ofile){
  ofile <<"<products>" << endl;
  for(unsigned int i =0; i < products.size(); i++){
    products[i]->dump(ofile);
    ofile<< endl;
  }
  ofile<<"</products>" << endl;
  ofile<<"<users>" << endl;
  for(unsigned int i =0; i <users.size(); i++){
    users[i]->dump(ofile);
  }
  ofile<<"</users>"<<endl;
}

void Store::addCart(string buyer, Product* p){
  std::map<string, vector<Product*> >::iterator it = cart.find(buyer);
  if(it == cart.end()) // checking if buyer exist
    return;
  it->second.push_back(p);
  //p->subtractQty(1);

}

void Store::viewCart(string buyer){
  //cout<< "made to view cart"<< endl;
  std::map<string, vector<Product*> >::iterator it = cart.find(buyer);
  if(it == cart.end()){ //checking if person exists
    return;
  }
  else{

  
  vector<Product*> temp = it->second;

    for(unsigned int i=0; i< temp.size(); i++ ){
     std::cout<<"Item "<< i+1 <<endl;
      std::cout<< temp[i]->displayString()<<endl;
    }
  }
  cout<<endl;
}

void Store::buyCart(string buyer){
  User* u;
  vector<Product*> shopping;
  std::map<string, vector<Product*> >::iterator it = cart.find(buyer);
  if(it == cart.end())
    return;
  shopping = it->second;
  vector<Product*> not_bought;

  for(unsigned int i =0; i< users.size(); i++){
    if(users[i]->getName()== buyer){
      u = users[i];
    }
  }

  for(unsigned int i=0; i < shopping.size(); i++){
    if(u->getBalance() - shopping[i]->getPrice() >= 0 && shopping[i]->getQty() >0){
        u->deductAmount(shopping[i]->getPrice());
        shopping[i]->subtractQty(1);

    }
    else{
      not_bought.push_back(shopping[i]);
    }
  }

  it->second = not_bought;


}