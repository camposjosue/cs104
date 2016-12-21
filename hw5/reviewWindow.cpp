#include <iostream>
#include <fstream>
#include <set>
#include <sstream>
#include <vector>
#include <iomanip>
#include <string>
#include <QApplication>
#include "reviewWindow.h"
#include "product.h"
#include "datastore.h"
#include "db_parser.h"
#include "product_parser.h"
#include "util.h"
#include "store.h"
#include "book.h"
#include "clothing.h"
#include "movie.h"
#include "stdio.h"


using namespace std;

ReviewWindow::ReviewWindow(Store* ds, Product* thing, QListWidget* temp ){

	
	this->ds=ds;
	currentItem = thing;

	view = temp;

	setWindowTitle("Add Review");

	OverallLayout = new QVBoxLayout();
	setLayout(OverallLayout);

	QString title; // =QString::fromStdString(thing->getName());
	title += "Add Review : ";
	title += QString::fromStdString(currentItem->getName());

	setWindowTitle(title);

	QString instructions = "Rate the product: ";

	titleLabel = new QLabel(instructions);
	OverallLayout->addWidget(titleLabel);

	seperatorLine = new QFrame();
	seperatorLine->setFrameShape(QFrame::HLine);
	seperatorLine->setFrameShadow(QFrame::Sunken);
	OverallLayout->addWidget(seperatorLine);

	//add rating
	ratingLayout = new QHBoxLayout();
	OverallLayout->addLayout(ratingLayout);


	// ratingLabel = new QLabel("Rating : 1-5   ");
	// OverallLayout->addWidget(ratingLabel);

	rating1 = new QRadioButton("1");
	ratingLayout->addWidget(rating1);

	rating2 = new QRadioButton("2");
	ratingLayout->addWidget(rating2);

	rating3 = new QRadioButton("3");
	ratingLayout->addWidget(rating3);

	rating4 = new QRadioButton("4");
	ratingLayout->addWidget(rating4);

	rating5 = new QRadioButton("5");
	ratingLayout->addWidget(rating5);


	// ratingInput = new QLineEdit();
	// ratingLayout->addWidget(ratingInput);

	//add date
	dateLayout = new QVBoxLayout();
	OverallLayout->addLayout(dateLayout);

	yearLayout = new QHBoxLayout();
	dateLayout->addLayout(yearLayout);

	yearLabel = new QLabel("Date : YYYY ");
	yearLayout->addWidget(yearLabel);

	yearInput = new QLineEdit();
	yearInput->setMaxLength(4);
	yearLayout->addWidget(yearInput);

	yearInput->QLineEdit::setValidator( new QIntValidator(0, 9999, this) );

	monthLayout = new QHBoxLayout();
	dateLayout->addLayout(monthLayout);

	monthLabel = new QLabel("Month : MM ");
	monthLayout->addWidget(monthLabel);

	monthInput = new QLineEdit();
	monthInput->setMaxLength(2);
	monthLayout->addWidget(monthInput);

	monthInput->QLineEdit::setValidator( new QIntValidator(1, 12, this) );

	dayLayout = new QHBoxLayout();
	dateLayout->addLayout(dayLayout);

	dayLabel = new QLabel("Day : DD        ");
	dayLayout->addWidget(dayLabel);

	dayInput = new QLineEdit();
	dayInput->setMaxLength(2);
	dayLayout->addWidget(dayInput);

	dayInput->QLineEdit::setValidator( new QIntValidator(1,31, this) );


	//seperatorLine->setFrameShape(QFrame::HLine);
	//seperatorLine->setFrameShadow(QFrame::Sunken);
	dateLayout->addWidget(seperatorLine);

	//add review text
	reviewLayout = new QVBoxLayout();
	OverallLayout->addLayout(reviewLayout);

	reviewLabel = new QLabel("Enter your review below: ");
	reviewLayout->addWidget(reviewLabel);

	reviewInput = new QTextEdit();
	reviewLayout->addWidget(reviewInput);


	addButton = new QPushButton("Add Review");
	connect(addButton, SIGNAL(clicked()), this, SLOT(add()));
	OverallLayout->addWidget(addButton);

	cancelButton = new QPushButton("Cancel");
	connect(cancelButton, SIGNAL(clicked()), this, SLOT(close()));
	OverallLayout->addWidget(cancelButton);

}

ReviewWindow::~ReviewWindow(){
	close();
}

void ReviewWindow::add(){

	//int originalsize = ds->reviews.size();

	if(yearInput->text().isEmpty() || reviewInput->toPlainText().isEmpty()
		|| monthInput->text().isEmpty() || dayInput->text().isEmpty())
		return;

	

	// string rating = ratingInput->text().toStdString();

	// stringstream ss(rating);

	int userRating;

	// ss >> userRating;

	if(rating1->isChecked()){
		userRating=1;
	} 
	else if(rating2->isChecked()){
		userRating=2;
	} 
	else if(rating3->isChecked()){
		userRating=3;
	} 
	else if(rating4->isChecked()){
		userRating=4;
	} 
	else if(rating5->isChecked()){
		userRating=5;
	} 
	else
		return;


	string year = yearInput->text().toStdString();

	if(year.length() != 4)
		return;


	string month = monthInput->text().toStdString();

	if(month.length() != 2)
		return;

	string day = dayInput->text().toStdString();

	if(day.length() != 2)
		return;

	string date = year + "-" + month + "-" + day;

	string comments = reviewInput->toPlainText().toStdString();

	Review* currentReview = new Review();

	currentReview->prodName = currentItem->getName();
	currentReview->rating = userRating;
	currentReview->date = date;
	currentReview->reviewText = comments;


	ds->reviews.push_back(currentReview);

	QString reviewText;
		reviewText += "Rating: ";
		reviewText += QString::number(userRating);
		reviewText += '\n';
		reviewText += "Date: ";
		reviewText += QString::fromStdString(date);
		reviewText += '\n';
		//reviewText += "Quantity: ";
		reviewText += QString::fromStdString(comments);
		reviewText += '\n';

		view->addItem(reviewText);

	//int finalsize = ds->reviews.size();

	// if(finalsize>originalsize)
	// 	display();

	//amazon()->index(n)

	close();
}