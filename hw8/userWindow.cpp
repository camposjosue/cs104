#include <iostream>
#include <fstream>
#include <set>
#include <sstream>
#include <vector>
#include <iomanip>
#include <QApplication>
#include "userWindow.h"
//#include "mainWindow.h"
#include "product.h"
#include "datastore.h"
#include "db_parser.h"
#include "product_parser.h"
#include "util.h"
#include "store.h"
#include "cartWindow.h"
#include "msort.h"
#include "LoginWindow.h"

using namespace std;

UserWindow::UserWindow(Store* ds, string buyer, string password){
	this->ds=ds;

	setWindowTitle("A M A Z O N");

	OverallLayout = new QVBoxLayout();
	setLayout(OverallLayout);

	InformationLabel = new QLabel("Please fill out the following information below: ");
	OverallLayout->addWidget(InformationLabel);

	whiteSpaceLabel = new QLabel(" ");
	OverallLayout->addWidget(whiteSpaceLabel);

	UserLabel = new QLabel("Enter a username:");
	OverallLayout->addWidget(UserLabel);

	UserInput = new QLineEdit();
	UserInput->setText(QString::fromStdString(buyer));
	UserInput->setMaxLength(15);
	OverallLayout->addWidget(UserInput);

	PasswordLabel = new QLabel("Enter a password up to 8 characters long:");
	OverallLayout->addWidget(PasswordLabel);

	PasswordInput = new QLineEdit();
	PasswordInput->setText(QString::fromStdString(password));
	PasswordInput->setMaxLength(8);
	OverallLayout->addWidget(PasswordInput);

	AgeLabel = new QLabel("Enter the User's age:");
	OverallLayout->addWidget(AgeLabel);

	AgeInput = new QLineEdit();
	AgeInput->QLineEdit::setValidator( new QIntValidator(0, 100, this) );
	OverallLayout->addWidget(AgeInput);

	CreditLabel = new QLabel("Enter the User's credit amount:");
	OverallLayout->addWidget(CreditLabel);

	CreditInput = new QLineEdit();
	CreditInput->QLineEdit::setValidator( new QIntValidator(0, 9999, this) );
	OverallLayout->addWidget(CreditInput);



	AddButton = new QPushButton("Add User");
	connect(AddButton, SIGNAL(clicked()), this, SLOT(attemptAdd()));
	OverallLayout->addWidget(AddButton);


}

UserWindow::~UserWindow(){

}

void UserWindow::attemptAdd(){
	int type = 0;


	if(UserInput->text().isEmpty() || PasswordInput->text().isEmpty()
			|| AgeInput->text().isEmpty() || CreditInput->text().isEmpty())
	{
		QMessageBox msgBox;
		msgBox.setText("One or more fields are empty/incorrect");
		msgBox.exec();
		return;
	} //check for empty

	//User(std::string name, int age, double balance, int type, long long password) : 

	//vector<User*> group = ds->getUsers();

	string person = UserInput->text().toStdString();

	User* temp = ds->fuckers->search(person);
	
	bool userAlreadyExists = false;
	
	if(temp != NULL)
		userAlreadyExists = true;
		

	// for(unsigned int i = 0; i < group.size(); i++){
	// 	if(UserInput->text().toStdString() == group[i]->getName())
	// 		userAlreadyExists= true;
	// }

	if(userAlreadyExists){
		QMessageBox msgBox;
		msgBox.setText("User Already Exists!");
		msgBox.exec();
		return;
	}
	else{

		//int temp = hash(PasswordInput->text().toStdString());

	

		User* u = new User(UserInput->text().toStdString(), AgeInput->text().toInt(), 
		CreditInput->text().toInt(), type, hash(PasswordInput->text().toStdString()));

		ds->addUser(u);

		QMessageBox msgBox;
		msgBox.setText("User has been added");
		msgBox.exec();
		//return;


		//close();

		LoginWindow* happy = new LoginWindow(ds);
  		happy->show();

  		close();
	}
}

long long UserWindow::hash(string password){

	unsigned long long hashBrown = 0;


	unsigned long long multiplier = 1;
	for(unsigned int i = 0; i < password.length(); i++){
		hashBrown+= (long long)password[password.length()-1 - i]*multiplier;
		multiplier *= 128;
	}

	unsigned int w1;
	unsigned int w2;
	unsigned int w3;
	unsigned int w4;

	w4 = hashBrown %  65521;
	hashBrown /= 65521;
	w3 = hashBrown %  65521;
	hashBrown /= 65521;
	w2 = hashBrown %  65521;
	hashBrown /= 65521;
	w1 = hashBrown %  65521;

	unsigned long long temp = (45912 * w1 + 35511 * w2 + 65169 * w3 + 4625 * w4);
	temp = temp % 65521;

	cout<< temp;
	cout<<endl;
	return temp;

}