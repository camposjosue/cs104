// #include <iostream>
// #include <fstream>
// #include <set>
// #include <sstream>
// #include <vector>
// #include <iomanip>
// #include "product.h"
// #include "datastore.h"
// #include "db_parser.h"
// #include "product_parser.h"
// #include "util.h"
// #include "store.h"
// /** Add other #includes here **/

// using namespace std;

// /* Prototypes */
// void displayProducts(vector<Product*>& hits);

// int main(int argc, char* argv[])
// {
//   if(argc < 2){
//     cerr << "Please specify a database file" << endl;
//   }

//   /****************
//    * Declare your derived DataStore object here replacing
//    *  DataStore type to your derived type
//    ****************/
//   Store ds;

//   // Instantiate the parser
//   DBParser parser;

//   // Instantiate the individual product parsers we want
//   parser.addProductParser(new ProductBookParser);
//   parser.addProductParser(new ProductClothingParser);
//   parser.addProductParser(new ProductMovieParser);

//   // Now parse the database to populate the DataStore
//   if( parser.parse(argv[1], ds) ){
//     cerr << "Error parsing!" << endl;
//     return 1;
//   }

//   cout << "=====================================" << endl;
//   cout << "Menu: " << endl;
//   cout << "  AND term term ...                  " << endl;
//   cout << "  OR term term ...                   " << endl;
//   cout << "  ADD username search_hit_number     " << endl;
//   cout << "  VIEWCART username                  " << endl;
//   cout << "  BUYCART username                   " << endl;
//   cout << "  QUIT new_db_filename               " << endl;
//   cout << "====================================" << endl;

//   vector<Product*> hits;
//   bool done = false;
//   while(!done){
//     cout << "\nEnter search terms: " << endl;
//     string line;
//     getline(cin,line);
//     stringstream ss(line);
//     string cmd;
//     if((ss >> cmd)){
//       if( cmd == "AND"){
// 	string term;
// 	vector<string> terms;
// 	while(ss >> term){
// 	  term = convToLower(term);
// 	  terms.push_back(term);
// 	}
// 	hits = ds.search(terms, 0);
// 	displayProducts(hits);
//       }
//       else if ( cmd == "OR" ){
// 	string term;
// 	vector<string> terms;
// 	while(ss >> term){
// 	  term = convToLower(term);
// 	  terms.push_back(term);
// 	}
// 	hits = ds.search(terms, 1);
// 	displayProducts(hits);	
//       }
//       else if ( cmd == "ADD"){
//         string buyer; //creating appropriate variables
//         string number; //product from hits
//         ss >> buyer;
//         ss >> number;
//         Product* temp = hits[atoi(number.c_str())-1];
//         ds.addCart(buyer, temp);
//       }
//       else if ( cmd == "VIEWCART"){
//         string buyer; //creating appropriate variables
//         ss>>buyer;

//         ds.viewCart(buyer);

//       }
//       else if ( cmd == "BUYCART"){
//         string buyer; //creating appropriate variables
//         ss>>buyer;

//         ds.buyCart(buyer);
//       }
//       else if ( cmd == "QUIT"){
// 	string filename;
// 	if(ss >> filename){
// 	  ofstream ofile(filename.c_str());
// 	  ds.dump(ofile);
// 	  ofile.close();
// 	}
// 	done = true;
//       }
//       /** ADD support for other command here **/


//       else {
// 	cout << "Unknown command" << endl;
//       }
//     }
    
//   }
//   return 0;
// }
 
// void displayProducts(vector<Product*>& hits)
// {
//   int resultNo = 1;
//   for(vector<Product*>::iterator it = hits.begin(); it != hits.end(); ++it){
//     cout << "Hit " << setw(3) << resultNo << endl;
//     cout << (*it)->displayString() << endl;
//     cout << endl;
//     resultNo++;
//   }
// }
