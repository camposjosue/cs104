#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include <cstring>
#include "util.h"

using namespace std;
std::string convToLower(std::string src) 
{
  std::transform(src.begin(), src.end(), src.begin(), ::tolower);
  return src;
}

/** Complete the code to convert a string containing a rawWord 
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWord) 
{

	std::set<std::string> *parsed_words = new std::set<std::string>;

	rawWord = convToLower(rawWord);

	for(unsigned int i = 0; i< rawWord.length(); i++){
		if(ispunct(rawWord[i])){
			rawWord[i]='\n';
		}
	}

	stringstream ss(rawWord);
	string word;


	while(ss>>word){

		//cout<<"***"<<word<<endl;
		if(strlen(word.c_str())>=2){
			parsed_words->insert(word);
		}
	}

	return *parsed_words;
}
