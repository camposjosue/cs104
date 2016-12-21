#include "stackdbl.h"
#include "llistdbl.h"
#include <iostream>
#include <fstream>
#include <string> 
#include <sstream>
#include <cstdlib>

using namespace std;


double calculate(string& expr, bool& success){
	istringstream ss(expr);
	double total;
	bool brk=false;

	StackDbl* s= new StackDbl();

	while(!ss.eof()){
		string input;
		
		ss >> input;
		

		if(input == "+"||input=="*"||input=="-"||input=="/"){
			
			double firstnum = s->top();
		
			double secondnum;
	
			s->pop();


			if(s->empty()){
				success=false;
				brk=true;
				break;

			}
			else
				secondnum = s->top();
			s->pop();
			if(input == "+")
				total = secondnum + firstnum;
			else if(input == "-")
				total = secondnum - firstnum;
			else if(input == "*")
				total = secondnum * firstnum;
			else if(input == "/")
				total = secondnum / firstnum;
			s->push(total);

		}
		else{
			double num = atof(input.c_str());
			s->push(num);
		}
	}
	s->pop();
	if(s->empty() && brk == false)
		success=true;
	else if(!s->empty() && brk == true)
		success=false;

	return total;

}

int main(int argc, char* argv[]){
	
	bool success;

	ifstream input;
	input.open(argv[1]);

	ofstream ofile(argv[2]);
	string line;
	while(getline(input, line)){

		double total = calculate(line, success);
		if (success== true)
			ofile << total<<endl;
		else if(success == false)
			ofile << "Invalid" << endl;
	}
}

