#include "../stackdbl.h"
#include "../llistdbl.h"
#include <iostream>
#include <cstdlib>

using namespace std;

int main(){

	StackDbl* s= new StackDbl();

	s->push(1);

	if(!s->empty()){

		cout<< "SUCESS : stack not empty after push" << endl;
	}
	else
		cout<< "FAIL"<<endl;

	s->push(2);
	if(s->top()==2) 
		cout<< "SUCESS : 2 is at the top of the stack" << endl;
	else
		cout<< "FAIL"<<endl;
	s->push(3);
	if(s->top()==3) 
		cout<< "SUCESS : 3 is at the top of the stack" << endl;
	else
		cout<< "FAIL"<<endl;
	s->push(4);
	if(s->top()==4) 
		cout<< "SUCESS : 4 is at the top of the stack" << endl;
	else
		cout<< "FAIL"<<endl;
	s->push(5);
	if(s->top()==5) 
		cout<< "SUCESS : 5 is at the top of the stack" << endl;
	else
		cout<< "FAIL"<<endl;
	s->push(6);
	if(s->top()==6) 
		cout<< "SUCESS : 6 is at the top of the stack" << endl;
	else
		cout<< "FAIL"<<endl;
	s->pop();
	if(s->top()==5) 
		cout<< "SUCESS : stack was popped" << endl;
	else
		cout<< "FAIL"<<endl;
	s->pop();
	s->pop();
	s->pop();
	s->pop();
	if(s->top()==1) 
		cout<< "SUCESS : stack was popped" << endl;
	else
		cout<< "FAIL"<<endl;
	s->pop();
	if(s->empty()){

		cout<< "SUCESS : stack empty after pop" << endl;
	}
	else
		cout<<"FAIL"<<endl;

	s->pop();

	cout<<"SUCCESS : Did not crash when popped empty stack"<<endl;
}