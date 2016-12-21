#include <iostream>
#include <fstream>
#include <set>
#include <sstream>
#include <vector>
#include <iomanip>
#include <QApplication>
#include "LoginWindow.h"
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

LoginWindow::LoginWindow(Store* ds){
	this->ds=ds;

	setWindowTitle("A M A Z O N");

	OverallLayout = new QVBoxLayout();
	setLayout(OverallLayout);

	// UserLayout = new QHBoxLayout();
	// OverallLayout->addLayout(UserLayout);

	UserLabel = new QLabel("Username:");
	OverallLayout->addWidget(UserLabel);

	UserInput = new QLineEdit();
	UserInput->setMaxLength(15);
	OverallLayout->addWidget(UserInput);

	PasswordLabel = new QLabel("Password:");
	OverallLayout->addWidget(PasswordLabel);

	PasswordInput = new QLineEdit();
	PasswordInput->setEchoMode(QLineEdit::Password); 
	PasswordInput->setMaxLength(8);
	OverallLayout->addWidget(PasswordInput);

	LoginButton = new QPushButton("Login");
	connect(LoginButton, SIGNAL(clicked()), this, SLOT(attemptLogin()));
	OverallLayout->addWidget(LoginButton);

	QuitButton = new QPushButton("Quit");
	connect(QuitButton, SIGNAL(clicked()), this, SLOT(closeWindow()));
	OverallLayout->addWidget(QuitButton);

	seperatorLine = new QFrame();
	seperatorLine->setFrameShape(QFrame::HLine);
	seperatorLine->setFrameShadow(QFrame::Sunken);
	OverallLayout->addWidget(seperatorLine);

	NewButton = new QPushButton("New User");
	connect(NewButton, SIGNAL(clicked()), this, SLOT(newUser()));
	OverallLayout->addWidget(NewButton);

}

LoginWindow::~LoginWindow(){
	
}

void LoginWindow::attemptLogin(){

	if(UserInput->text().isEmpty() || PasswordInput->text().isEmpty())
	{
		QMessageBox msgBox;
		msgBox.setText("One or more fields are empty/incorrect");
		msgBox.exec();
	} //check for empty

	else{
		stringstream ss(UserInput->text().toStdString());
		string currentUser;
		ss >> currentUser;

		//bool userFound = false;
		// vector<User*> temp = ds->getUsers();

		// for(unsigned int i = 0; i < temp.size(); i++){
		// 	if(currentUser == temp[i]->getName())
		// 		userFound = true;
		// }


		User* temp = ds->fuckers->search(currentUser);


		if(temp != NULL){


			stringstream ss(PasswordInput->text().toStdString());
			string current;
			ss >> current;

//*****************   HASH THE PASSWORD HERE
			long long currentPassword= hash(current);

			//bool passwordFound = false;

			// for(unsigned int i = 0; i < temp.size(); i++){
			// 	if(currentPassword == temp[i]->getPassword()){
			// 		passwordFound = true;
			// 	}
			// }

				if(currentPassword == temp->getPassword()){
					
					myWindow = new MainWindow(ds, currentUser);

					close();

					myWindow->show();

				}

				else{


					QMessageBox msgBoxError;
					msgBoxError.setText("Incorrect Login Information");
					msgBoxError.exec();
					return;

				}
//***************** verify the password here then do something to make an insatnce of password information
	
		}
		else{
			QMessageBox msgBoxError;
			msgBoxError.setText("Incorrect Login Information");
			msgBoxError.exec();
			return;
		}
	}

}

void LoginWindow::closeWindow(){
	close();
}

void LoginWindow::newUser(){

	string the_user = UserInput->text().toStdString();
	string the_password = PasswordInput->text().toStdString();
	
	myUser = new UserWindow(ds, the_user, the_password );

	close();

	myUser->show();
}

long long LoginWindow::hash(string password){
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
	return temp;
}