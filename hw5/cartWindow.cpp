#include <iostream>
#include <fstream>
#include <set>
#include <sstream>
#include <vector>
#include <iomanip>
#include <QApplication>
#include "cartWindow.h"
#include "product.h"
#include "datastore.h"
#include "db_parser.h"
#include "product_parser.h"
#include "util.h"
#include "store.h"
#include "book.h"
#include "clothing.h"
#include "movie.h"

using namespace std;

CartWindow::CartWindow(Store* ds, string current){
	this->ds=ds;
	buyer = current;

	QString windowTitle = QString::fromStdString(current);
	windowTitle += "' cart";

	setWindowTitle(windowTitle);

	OverallLayout = new QVBoxLayout();
	setLayout(OverallLayout);

	QString title = QString::fromStdString(buyer);
	title += "'s Cart: ";

	titleLabel = new QLabel(title);
	OverallLayout->addWidget(titleLabel);

	cartListWidget = new QListWidget();
	connect(cartListWidget, SIGNAL(currentRowChanged(int)), this, SLOT(index(int)));
	display();
	OverallLayout->addWidget(cartListWidget);

	buttonLayout = new QHBoxLayout();
	OverallLayout->addLayout(buttonLayout);

	removeButton = new QPushButton("Remove Item");
	connect(removeButton, SIGNAL(clicked()), this, SLOT(remove()));
	buttonLayout->addWidget(removeButton);

	buyButton = new QPushButton("Buy Cart");
	connect(buyButton, SIGNAL(clicked()), this, SLOT(buying()));
	buttonLayout->addWidget(buyButton);

	closeButton = new QPushButton("Close");
	connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));
	OverallLayout->addWidget(closeButton);
}

CartWindow::~CartWindow(){
	close();
}

void CartWindow::display(){

	while(cartListWidget->count()>0){
		cartListWidget->takeItem(0);
	}

	vector<Product*> temp = ds->viewCart(buyer);

	for(unsigned int i =0; i<temp.size(); i++){
		QString searchText;
		searchText += QString::fromStdString(temp[i]->getName());
		searchText += '\n';
		searchText += "Price: $";
		searchText += QString::number(temp[i]->getPrice());
		searchText += '\n';
		searchText += "Quantity: ";
		searchText += QString::number(temp[i]->getQty());
		searchText += '\n';

		cartListWidget->addItem(searchText);
	}
}

void CartWindow::index(int displayIndex){
	currentIndex = displayIndex;
}
void CartWindow::remove(){
	vector<Product*> temp = ds->viewCart(buyer);

	if(temp.size()==0)
		return;

	ds->removeCart(buyer, currentIndex);

	display();
}

void CartWindow::buying(){
	ds->buyCart(buyer);
	display();

	vector<Product*> temp = ds->viewCart(buyer);
	if(temp.size()==0){

		QString searchText;
		
		
		searchText += "Your Cart is Empty";

		cartListWidget->addItem(searchText);

		//close();
	}
}
