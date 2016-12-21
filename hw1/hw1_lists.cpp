#include <iostream>
#include <fstream>
#include <string> 
#include <sstream>
using namespace std;

struct Item {
  Item(int v, Item* n) { val = v; next = n; }
  int val;
  Item* next;
};

Item* concatenate(Item* head1, Item* head2);  // returns head pointer to new list
void removeEvens(Item*& head);
double findAverage(Item* head, int size);
void readLists(Item*& head1, Item*& head2, char* file);
void printList(std::ostream& ofile, Item* head);
int countList(Item* head);


int main(int argc, char* argv[]){

	Item* head1;
	Item* head2;

	head1 = NULL;
	head2 = NULL;

	readLists(head1, head2, argv[1]);

	ofstream ofile;
	ofile.open(argv[2]);
	


	Item* head3;
	head3 = concatenate(head1, head2);
	printList(ofile, head3);  // returns head pointer to new list
	removeEvens(head3);
	int size = countList(head3);
	printList(ofile, head3); 
	double average = findAverage(head3, size);
	printList(ofile, head3); 

	if (size ==0)
		cout<< "Cannot Compute average of empty list" << endl;
	else 
		cout << average << endl;
	
	ofile << average;

return 0;
	
}

Item* concatenate(Item* head1, Item* head2){
	Item* tempend;
	tempend=head1;

	while(tempend -> next){
		tempend = tempend -> next;
	}
	tempend -> next = head2;
	return head1;


}  // returns head pointer to new list


void removeEvens(Item*& head){
	int temp;

	Item* curr;
	if (head == NULL){
		return;
	}
	if (head->val %2 != 0 && head->next == NULL){
		return;
	} else if (head -> val %2 ==0){
		curr = head -> next;
		delete head;
		head = curr;
		removeEvens(head);
	} else if(head-> next-> val % 2 == 0){
		curr = head -> next -> next;
		delete (head -> next);
		head -> next = curr;
		removeEvens(head->next);
	} else {
		removeEvens(head->next);
	}
}

double findAverage(Item* head, int size){
	if (head->next->next != NULL){
		head->next->val += head->val;
		findAverage(head->next, size);
	} else {
		head->next->val += head->val;
		double dummy = double(head -> next -> val);
		return double(dummy / double(size));
	}
}

int countList(Item* head){
	int counter = 0;
	while(head != NULL){
		
		head = head->next;
		counter++;
	}
	return counter;
}
void printList(std::ostream& ofile, Item* head)
{
  if(head == NULL)
    ofile << std::endl;
  else {
    ofile << head->val << " ";
    printList(ofile, head->next);    
  }
}

void readLists(Item*& head1, Item*& head2, char* file){
	ifstream input;
	input.open(file);

	string line1;
	string line2;

	
	getline(input, line1);


	stringstream strm1(line1);

	int temp1;
	Item* pointerTemp = NULL;
	//Item* prev = NULL;



	while(strm1>>temp1){

		if(head1 ==NULL){

			pointerTemp= new Item(temp1, NULL);
			head1 = pointerTemp;
		}
		else{

			pointerTemp -> next = new Item(temp1,NULL);
			pointerTemp = pointerTemp-> next;
		}
	}

	
	getline(input, line2);
	stringstream strm2(line2);

	int temp2;
	pointerTemp = NULL;

	while(strm2>>temp2){
		if(head2==NULL){
			pointerTemp= new Item(temp2, NULL);
			head2 = pointerTemp;
		}
		else{
			pointerTemp -> next = new Item(temp2,NULL);
			pointerTemp = pointerTemp-> next;
		}
	}
	
}
