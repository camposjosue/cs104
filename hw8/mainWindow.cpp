#include <iostream>
#include <fstream>
#include <set>
#include <sstream>
#include <vector>
#include <iomanip>
#include <QApplication>
#include "mainWindow.h"
#include "product.h"
#include "datastore.h"
#include "db_parser.h"
#include "product_parser.h"
#include "util.h"
#include "store.h"
#include "cartWindow.h"
#include "msort.h"
#include <cmath>
#include "heap.h"
#include <queue>

using namespace std;

struct SimCmp {
	bool operator()(const pair<Product*,double> lhs, const pair<Product*,double> rhs) {
		return lhs.second > rhs.second;
	}
};

struct pairCmp {
	bool operator()(const pair<User*,double> lhs, const pair<User*,double> rhs) {
		return lhs.second < rhs.second;
	}
};

struct alphaProductCmp {
    bool operator()(const Product* lhs, const Product* rhs) 
    { // Uses string's built in operator< 
      // to do lexicographic (alphabetical) comparison
      return lhs->getName() < rhs->getName(); 
    }
};

MainWindow::MainWindow(Store* ds, string current){
	
	this->ds=ds;
	this->current= current;

	setWindowTitle("A M A Z O N");

	openedCart = false;
	openedReview =false;


	vector<User*> people = ds->getUsers();

	//User* mainBitch = new User;

	for(unsigned int i = 0; i < people.size(); i++){
		basicSimilarities(people[i]->getName());
	}

	string productName = makeReccomendation();




	OverallLayout = new QHBoxLayout();
	setLayout(OverallLayout);

	userLayout = new QVBoxLayout();
	OverallLayout->addLayout(userLayout);

	whiteSpaceLabel = new QLabel(" ");
	OverallLayout->addWidget(whiteSpaceLabel);

	formLayout = new QVBoxLayout();
	OverallLayout->addLayout(formLayout);


	userLabel = new QLabel("Current User ");
	userLayout->addWidget(userLabel);

	dropDown = new QComboBox();
	userLayout->addWidget(dropDown);


	dropDown->addItem(QString::fromStdString(current));
	// vector<User* > listUsers = ds->getUsers();
	// for(unsigned int i=0; i<listUsers.size(); i++){
	// 	dropDown->addItem(QString::fromStdString(listUsers[i]->getName()));
	// }


	userLayout->addWidget(whiteSpaceLabel);
	userLayout->addWidget(whiteSpaceLabel);
	userLayout->addWidget(whiteSpaceLabel);

//create a visual break
	seperatorLine = new QFrame();
	seperatorLine->setFrameShape(QFrame::HLine);
	seperatorLine->setFrameShadow(QFrame::Sunken);
	userLayout->addWidget(seperatorLine);

	//filename input
	filenameInput = new QLineEdit();
	userLayout->addWidget(filenameInput);

	saveButton = new QPushButton(" Save ");
	connect(saveButton, SIGNAL(clicked()), this, SLOT(fileOutput()));
	userLayout->addWidget(saveButton);

	quitButton = new QPushButton(" Quit ");
	connect(quitButton, SIGNAL(clicked()), this, SLOT(closeWindow()));
	userLayout->addWidget(quitButton);

	searchLayout = new QVBoxLayout();
	formLayout->addLayout(searchLayout);

	// Search Label
	searchLabel = new QLabel("Search Type:");
	searchLayout->addWidget(searchLabel);

	// Search Input

	// searchInput = new QLineEdit();
	// searchLayout->addWidget(searchInput);

	//radioLayout = new QHBoxLayout();
	//formLayout->addLayout(radioLayout);

	ORsearch = new QRadioButton(" OR", this);
	searchLayout->addWidget(ORsearch);

	ANDsearch = new QRadioButton(" AND", this);
	searchLayout->addWidget(ANDsearch);

	sortLabel = new QLabel("Sort Type:");
	searchLayout->addWidget(sortLabel);

	//add a row for the merge sort buttons
	filterLayout = new QVBoxLayout();
	formLayout->addLayout(filterLayout);

	//alphabetical search
	alphabeticalButton = new QPushButton("Alphabetical");
	connect(alphabeticalButton, SIGNAL(clicked()), this, SLOT(alphaSort()));
	filterLayout->addWidget(alphabeticalButton);

	//filter based on highest average rating
	ratingButton = new QPushButton("Highest Rated");
	connect(ratingButton, SIGNAL(clicked()), this, SLOT(ratingSort()));
	filterLayout->addWidget(ratingButton);

	searchInput = new QLineEdit();
	filterLayout->addWidget(searchInput);

	searchButton = new QPushButton(" Search ");
	connect(searchButton, SIGNAL(clicked()), this, SLOT(productSearch()));
	filterLayout->addWidget(searchButton);

	//making a seperate column for the results;
	searchResultsLayout = new QVBoxLayout();
	OverallLayout->addLayout(searchResultsLayout);

	//setting up for the new column
	searchResultsLabel = new QLabel("Search results:");
	searchResultsLayout->addWidget(searchResultsLabel);

	searchListWidget = new QListWidget();
	connect(searchListWidget, SIGNAL(currentRowChanged(int)), this, SLOT(index(int)));
	searchResultsLayout->addWidget(searchListWidget);

	//Button to add selected item to USER's cart;
	addcartButton = new QPushButton("Add-to-Cart");
	connect(addcartButton, SIGNAL(clicked()), this, SLOT(addToCart()));
	searchResultsLayout->addWidget(addcartButton);

	//Open a new window to view cart with button;
	viewcartButton = new QPushButton("View-Cart");
	connect(viewcartButton, SIGNAL(clicked()), this, SLOT(showCartPopup()));
	searchResultsLayout->addWidget(viewcartButton);

	reviewLayout = new QVBoxLayout();
	OverallLayout->addLayout(reviewLayout);

	reviewResultsLabel = new QLabel("Product Reviews:");
	reviewLayout->addWidget(reviewResultsLabel);

	reviewListWidget = new QListWidget();
	//connect(searchListWidget, SIGNAL(currentRowChanged(int)), this, SLOT(displayPokemon(int)));
	reviewLayout->addWidget(reviewListWidget);

	//open a new window to add review
	addreviewButton = new QPushButton("Add Review");
	connect(addreviewButton, SIGNAL(clicked()), this, SLOT(addReviewPopup()));
	reviewLayout->addWidget(addreviewButton);

	show();

	QMessageBox productBox;

	productBox.setWindowTitle("Product Reccommendation");
	productBox.setText(QString::fromStdString(productName));

	productBox.exec();

	myReview = new ReviewWindow(); //s(ds, hits[currentIndex], reviewListWidget, current); 
	myCart = new CartWindow(ds, current);

};

MainWindow::~MainWindow(){
	delete myCart;
	delete myReview;
}

void MainWindow::productSearch(){

	if(searchInput->text().isEmpty())
	{
		return;
	} //check for empty

	while(reviewListWidget->count()>0){
		reviewListWidget->takeItem(0);
	}


	currentReviews.clear();

	stringstream ss(searchInput->text().toStdString());
	string term;
	vector<string> terms;
	while(ss >> term){
	  term = convToLower(term);
	  terms.push_back(term);

	}


	if(ANDsearch->isChecked())
		hits = ds->search(terms,0);
	else if(ORsearch->isChecked())
		hits = ds->search(terms,1);
	// else  
	// 	somethings wrong

	display();

}

void MainWindow::display(){

// 	while(searchListWidget->count()>0){
 		searchListWidget->clear();
//	}



	for(unsigned int i =0; i < hits.size(); i++){
		QString searchText;
		searchText += QString::fromStdString(hits[i]->getName());
		searchText += '\n';
		searchText += "Price: $";
		searchText += QString::number(hits[i]->getPrice());
		searchText += '\n';
		searchText += "Quantity: ";
		searchText += QString::number(hits[i]->getQty());
		searchText += '\n';

		searchListWidget->addItem(searchText);

	}

}

void MainWindow::addToCart(){
	string buyer = dropDown->currentText().toStdString();

	if(hits.size()==0 || (unsigned int)currentIndex>(hits.size()-1))
		return;
	
	ds->addCart(buyer, hits[currentIndex]);

}

void MainWindow::showCartPopup()
{
	openedCart = true;
	string buyer = dropDown->currentText().toStdString();
	myCart = new CartWindow(ds, buyer);

	myCart->show();



}

void MainWindow::addReviewPopup()
{

	// string buyer = dropDown->currentText().toStdString();
	openedReview = true;
	if(hits.size()==0)
		return;

	myReview = new ReviewWindow(ds, hits[currentIndex], reviewListWidget, current); 
	//cout<<"we are about to show";
	myReview->show();
	
}

void MainWindow::fileOutput()
{
	if(filenameInput->text().isEmpty())
	{
		QMessageBox msgBox;

		msgBox.setWindowTitle("Error");
		msgBox.setText("\"Could not save to file\"");
		//return;
	} //check for empty

	string filename = filenameInput->text().toStdString();
	 ofstream ofile(filename.c_str());
	 ds->dump(ofile);
	 ofile.close();

	if(ofile.fail()){
		QMessageBox msgBox;

		msgBox.setWindowTitle("Error");
		msgBox.setText("\"Could not save to file\"");
	}
	if(ofile.good())
		filenameInput->clear();
}

void MainWindow::index(int displayIndex){
	currentIndex = displayIndex;



	if(hits.size()==0 || (unsigned int)currentIndex>(hits.size()-1))
		return;

	//reviewListWidget->clear();

	while(reviewListWidget->count()>0)
	{
  		reviewListWidget->takeItem(0);//handle the item if you don't 
                          //have a pointer to it elsewhere
	}

	string itemName = hits[currentIndex]->getName();

	currentReviews.clear();

	for(unsigned int i=0; i<ds->reviews.size(); i++){
		if(itemName == ds->reviews[i]->prodName){
			currentReviews.push_back(ds->reviews[i]);
		}
	}

	for(unsigned int i=0; i<currentReviews.size(); i++){
		QString reviewText;
		reviewText += "Rating: ";
		reviewText += QString::number(currentReviews[i]->rating);
		reviewText += '\n';
		reviewText += "Date: ";
		reviewText += QString::fromStdString(currentReviews[i]->date);
		reviewText += '\n';
		//reviewText += "Quantity: ";
		reviewText += QString::fromStdString(currentReviews[i]->reviewText);
		reviewText += '\n';

		reviewListWidget->addItem(reviewText);
	}

	//reviewListWidget->clear();
}

void MainWindow::alphaSort(){
	if(hits.size()==0)
		return;

	vector<string> sorted;
	vector<string> unsorted;
	vector<Product*> FINAL;
	AlphaStrComp comp;
	for(unsigned int i = 0; i < hits.size(); i++){
		sorted.push_back(hits[i]->getName());
	}

	unsorted=sorted;

	mergeSort(sorted, comp);

	for(unsigned int i = 0; i < sorted.size(); i++){
		for(unsigned int j = 0; j < unsorted.size(); j++){
			if(sorted[i]==unsorted[j]){
				FINAL.push_back(hits[j]);
			}
		}
	}


	hits = FINAL;
	
	display();

}

void MainWindow::ratingSort(){

	vector<int> sorted;
	vector<int> unsorted;

	vector<Product* > FINAL;

	for(unsigned int i =0; i < hits.size(); i++){
		double total=0;
		double count=0;
		for(unsigned int j =0; j < ds->reviews.size(); j++){
			if(hits[i]->getName()==ds->reviews[j]->prodName){
				total += ds->reviews[j]->rating;
				count++;
			}
		}

		total = total/count;
		sorted.push_back(total);
	}

	unsorted = sorted;

	GrtDoubleComp comp;

	mergeSort(sorted,comp);

	for(unsigned int i = 0; i < sorted.size(); i++){
		for(unsigned int j = 0; j < unsorted.size(); j++){
			if(sorted[i]==unsorted[j]){
				FINAL.insert(FINAL.begin(),hits[j]);
			}
		}
	}


	hits = FINAL;

	display();


	//for(hits)

}

void MainWindow::closeWindow(){
	
	if(myReview->isVisible() && openedReview == true)
		myReview->close();
	if(myCart->isVisible() && openedCart)
		myCart->close();
	close();
}

void MainWindow::basicSimilarities(string person){

	std::map<User*, double> scoreMap;

	vector<User*> people = ds->getUsers();

	User* mainBitch = ds->fuckers->search(person);

	// for(unsigned int i = 0; i < people.size(); i++){
	// 	if(person == people[i]->getName()){
	// 		mainBitch = people[i];
	// 	}
	// }

	set<string> mainBitchReviews;

	for(unsigned int i = 0; i < ds->reviews.size(); i++){
		if(person == ds->reviews[i]->username){
			mainBitchReviews.insert(ds->reviews[i]->prodName);
		}
	}



	for(unsigned int i = 0; i < people.size(); i++){
		set<string> sideBitchReviews;			
		
		if(person != people[i]->getName()){
		
			for(unsigned int j = 0; j < ds->reviews.size(); j++){
				if(people[i]->getName() == ds->reviews[j]->username){
					sideBitchReviews.insert(ds->reviews[j]->prodName);
				}
			}

			set<string> matchingReviews = setIntersection(mainBitchReviews, sideBitchReviews);
			//set intersection here of the vector of reviews.
			double mainRating = 0;
			double sideRating = 0;

			double rawSimilarity = 0;

			double setSize = matchingReviews.size(); 


			//cout<<"size of the set is : "<< matchingReviews.size()<<endl;

			for(set<string>::iterator it =  matchingReviews.begin();
				it != matchingReviews.end(); ++it){

				for(unsigned int k = 0; k < ds->reviews.size(); k++){
					if(*it == ds->reviews[k]->prodName){
						if(ds->reviews[k]->username == people[i]->getName()){
							sideRating = ds->reviews[k]->rating;

							//cout<<"rating: "<<ds->reviews[k]->rating<<endl;
						} 
						if(ds->reviews[k]->username == mainBitch->getName()){
							mainRating = ds->reviews[k]->rating;
							//cout<<"rating: "<<ds->reviews[k]->rating<<endl;
						}
					}
				}

				//cout<<endl;
				rawSimilarity += (abs(mainRating - sideRating))/4;

				//cout<<rawSimilarity<<endl;
			}

			if(setSize == 0){  // make sure not to divide by 0
				rawSimilarity=1;
			} 
			else{
				rawSimilarity = rawSimilarity/setSize;
			
			}


			//cout<<"rawSimilarity : "<<rawSimilarity<<endl<<endl;

			scoreMap.insert(make_pair(people[i],rawSimilarity));

			
		}
	}
	mainBitch->setMap(scoreMap);
	
	
	//cout<< "Basic for :" << person << endl;
	// for(map<User*,double>::iterator it = scoreMap.begin(); it != scoreMap.end(); ++it){
	// 	cout<<"User: "<<it->first->getName()<<endl;
	// 	cout<<"Value: "<<it->second<<endl;
	// }


}

map<User*, double> MainWindow::refinedSimilarities(string person){
	//pas current user
	pairCmp comp;
	Heap<pair<User*, double>, pairCmp > tracker(2, comp);

	vector<User*> people = ds->getUsers();

	User* mainBitch = ds->fuckers->search(person);

	// for(unsigned int i = 0; i < people.size(); i++){
	// 	if(person == people[i]->getName()){
	// 		mainBitch = people[i];
	// 	}
	// }

	map<User*, double> solutionMap;

	tracker.push(make_pair(mainBitch,0));
	solutionMap.insert(make_pair(mainBitch, 0));

	for(unsigned int i = 0; i < people.size(); i++){
		if(people[i]->getName() != person){
			tracker.push(make_pair(people[i],1.0));
			solutionMap.insert(make_pair(people[i],1.0));

		}
		//add the rest to map;
		//add the rest in to the heap
		//initial distance is on
	}


	//cout << "========================" << endl;
	while(!tracker.empty()){
		
		pair<User*, double> currentPair= tracker.top();
		tracker.pop();

		map<User*, double> currentMap = currentPair.first->getMap();
		//cout << "CURRENT: " << currentPair.first->getName() << endl;
		for(map<User*,double>::iterator it = currentMap.begin(); it != currentMap.end(); ++it){
			//cout<<"\tUser: "<<it->first->getName()<<endl;
			//cout<<"\tValue: "<<it->second<<endl;
		}

		for(map<User*, double>::iterator it = solutionMap.begin(); it != solutionMap.end(); ++it){
			double weight = currentMap[it->first];
			//cout << "Checking with: " << it->first->getName() << " with weight " << weight << endl;
			if(weight+ solutionMap[currentPair.first]< solutionMap[it->first]){
				//cout << "Overriding " << "with total weight" << weight + solutionMap[currentPair.first] << endl;
			//if(weight+ currentPair.second< solutionMap[it->first]){
				solutionMap[it->first]= weight+ solutionMap[currentPair.first];
				tracker.push(make_pair(it->first, solutionMap[it->first] ));
			}
		}
		// pop from heap
		// distance to that node += current; 	map[user] = min( map[user]->second, whtever value)

		// user->score Map make new pairs and push them in
	}

	return solutionMap;

}

string MainWindow::makeReccomendation(){
	map<User*, double> temp = refinedSimilarities(current);

	//cout<<endl<<"REFINED"<<endl;

	//for(map<User*, double>::iterator it = temp.begin(); it != temp.end(); ++it){
		
		//cout<<"Key:"<<it->first->getName()<<endl;
		//cout<<"Value: "<<it->second<<endl;

	//}

	SimCmp cp;
	Heap<pair<Product*, double>, SimCmp > total(2, cp);

	//typedef::priority_queue<double,pair<Product*, double>,SimCmp >total;

	vector<Product*> stash = ds->getProducts();

	//cout<<"#####THE SIZE OF THE VECTOR: "<< stash.size()<<endl;

	//set<Product*> verified;
	for(unsigned int i = 0; i< stash.size(); i++){
		double sum = 0; 
		double w = 0;
		User* mainBitch;

		bool badproduct = false;
		set<Product*> verified;

		vector<Review*> list = stash[i]->getReview();
		for(unsigned int j = 0; j<list.size(); j++){

			//cout<<'\t'<<list[j]->username<<endl;
			
			if(current != list[j]->username){
				//cout<<'\t'<<list[j]->username<<endl;

				double rating = list[j]->rating; //r(b,p)

				mainBitch = ds->fuckers->search(list[j]->username);

				// vector<User*> people = ds->getUsers();

				// for(unsigned int k = 0; k < people.size(); k++){
				// 	if(list[j]->username == people[k]->getName()){
				// 		mainBitch = people[k];
				// 	}
				// }

				double similarity= temp[mainBitch]; //s(b,a)

				sum += (1 - similarity)*rating;
				//cout<<"SUM: "<<sum<<endl;

				w += (1 - similarity);
				//cout<<" W : "<<w<<endl;
			}
			else{
				badproduct = true;
				//verified.insert(stash[i]);
			}
		}

		double interstingness;
		if(w == 0){
			interstingness = 0;
		} 
		else{
			interstingness = sum/w;
		}

		//std::cout << "iteration nmber: " << i << std::endl;

		//set<Product*>::iterator it = verified.find(stash[i]);
		if(badproduct==false)
			total.push(make_pair(stash[i],interstingness));
		//cout<< "what i am pushing in   " <<stash[i]->getName()<<endl;
		//cout<< "level of interstingness " <<interstingness<<endl;


		//cout<<"hello"<<endl;
	}

	//cout<<"Done"<<endl;

	pair<Product*, double> sample= total.top();

	
	//cout<<"what is wrong"<<endl;
	//cout<< "******  " <<sample.first->getName()<<endl;

	return sample.first->getName();
}

