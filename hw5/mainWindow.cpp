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

using namespace std;

struct alphaProductCmp {
    bool operator()(const Product* lhs, const Product* rhs) 
    { // Uses string's built in operator< 
      // to do lexicographic (alphabetical) comparison
      return lhs->getName() < rhs->getName(); 
    }
};

MainWindow::MainWindow(Store* ds){
	
	this->ds=ds;

	setWindowTitle("A M A Z O N");

	openedCart = false;
	openedReview =false;

	OverallLayout = new QHBoxLayout();
	setLayout(OverallLayout);

	userLayout = new QVBoxLayout();
	OverallLayout->addLayout(userLayout);

	whiteSpaceLabel = new QLabel(" ");
	OverallLayout->addWidget(whiteSpaceLabel);

	formLayout = new QVBoxLayout();
	OverallLayout->addLayout(formLayout);


	userLabel = new QLabel("Select User ");
	userLayout->addWidget(userLabel);

	dropDown = new QComboBox();
	userLayout->addWidget(dropDown);

	vector<User* > listUsers = ds->getUsers();
	for(unsigned int i=0; i<listUsers.size(); i++){
		dropDown->addItem(QString::fromStdString(listUsers[i]->getName()));
	}


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
	openedReview = true;
	if(hits.size()==0)
		return;

	myReview = new ReviewWindow(ds, hits[currentIndex], reviewListWidget); 
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
	
	myReview->close();

	myCart->close();
	close();
}