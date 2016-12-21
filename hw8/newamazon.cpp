#include <iostream>
#include <fstream>
#include <set>
#include <sstream>
#include <vector>
#include <iomanip>
#include <QApplication>
#include "LoginWindow.h"
#include "product.h"
#include "datastore.h"
#include "db_parser.h"
#include "product_parser.h"
#include "util.h"
#include "store.h"

using namespace std;


int main(int argc, char* argv[])
{
  if(argc < 2){
    cerr << "Please specify a database file" << endl;
    return 0;
  }

  if(argc < 3){
    cerr << "Please specify a thesaurus file" << endl;
    return 0;
  }

  Store* ds = new Store();

  // Instantiate the parser
  DBParser parser;

  if( parser.parseDictionary(argv[2], *ds) ){
    cerr << "Error parsing!" << endl;
    return 1;
  }

  // Instantiate the individual product parsers we want
  parser.addProductParser(new ProductBookParser);
  parser.addProductParser(new ProductClothingParser);
  parser.addProductParser(new ProductMovieParser);

  // Now parse the database to populate the DataStore
  if( parser.parse(argv[1], *ds) ){
    cerr << "Error parsing!" << endl;
    return 1;
  }

  
  

  QApplication app(argc, argv);
  LoginWindow main(ds);
  main.show();

  return app.exec();

  //delete ds;

}