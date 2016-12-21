#include <iostream>
#include <fstream>
#include <string> 
#include <sstream>
#include <cstdlib>
#include <map>
#include <cctype>
#include "llistint.h"
#include "setint.h"
//#include 

using namespace std;


string filter(string word,bool& valid, bool& hyphen){
	while(ispunct(word[0])){
		word.erase(0,1);
	}
	while(ispunct(word[word.size()])){
		word.substr(0,word.size()-1);
	}

	for(unsigned int i =0; i < word.length(); i++){
		if(ispunct(word[i])){
			valid = false;
		}
	}
	for(unsigned int i =0; i<word.length(); i++){
		if(word[i]=='-'){
			hyphen = true;
		}
	}
	return word;

}



int main(int argc, char* argv[]){

	ifstream ifile(argv[1]);	
	ofstream ofile(argv[2]);

	map<string,SetInt> words;
	// istringstream ss;
	int pagenumber=1;
	bool valid;
	bool hyphen;

	string input;
	string key;
	string cut;

		while(ifile>>input){
			valid = true;
			hyphen = false;
			if(input=="<pagebreak>"){
				pagenumber++;
			}
			else{   //a word
				for(unsigned int i=0; i< input.length(); i++){
					input[i] = tolower(input[i]);
				}

				key=filter(input, valid, hyphen);

				if(valid==false){
					if(hyphen == true){
						unsigned int i=0;
						int length = 0;
						int start =0;
						while(i< key.size()){
							//cout<<"--- "<<i<<" ---"<<endl;
							if(key[i]=='-'|| i==key.size()-1){
								cut=key.substr(start,length);
								//cout<<cut<<endl;
								if(words.find(cut)==words.end()){
									SetInt temp;
									temp.insert(pagenumber);
									words.insert(make_pair(cut,temp));
									start = i+1;
									length =0;
								}
								else{
									words[cut].insert(pagenumber);
									start = i+1;
									length =0;
								}
								
							}
							i++;
							length++;
						}
					}
				}
				else if(valid == true){
					if(words.find(key)==words.end()){
						SetInt temp;
						temp.insert(pagenumber);
						words.insert(make_pair(key,temp));
					}
					else{
						words[key].insert(pagenumber);
					}
				}

			}
		}

	for(int i = 3; i < argc; i++){
		
		string index(argv[i]);
		for(unsigned int i =0; i < index.size(); i++){
			index[i] = tolower(index[i]);
		}
		if(words.find(index)==words.end()){
			ofile<< "None"<< endl;
		}
		else{
			ofile<< *(words[index].first()) << " ";
			for(int i =1; i< words[index].size();i++){
				ofile<< *(words[index].next());
				ofile<<" ";
			}
			ofile << endl;
		}
	}
	//ofile<< words[]

	ifile.close();
	ofile.close();
	
}

