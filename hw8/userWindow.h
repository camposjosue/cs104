#ifndef USERWINDOW_H
#define USERWINDOW_H

#include <string>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QComboBox>
#include <QLabel>
#include <QRadioButton>
#include <QLineEdit>
#include <QString>
#include <QApplication>
#include <QTextEdit>
#include <QListWidget>
#include <QFrame>
#include <QMessageBox>
#include "msort.h"
#include "product.h"
#include "datastore.h"
#include "db_parser.h"
#include "product_parser.h"
#include "util.h"
#include "store.h"
#include "cartWindow.h"
#include "reviewWindow.h"
#include "mainWindow.h"


class UserWindow : public QWidget {
	Q_OBJECT
	
	public:
		UserWindow(Store* ds, std::string user, std::string password);
		~UserWindow();

		//std::vector<Review*> currentReviews;

	private slots:
		// void attemptLogin();
		// void closeWindow();
		// void newUser();
		void attemptAdd();




	private:

		long long hash(std::string password);
		QVBoxLayout* OverallLayout;

		QLabel* InformationLabel;
		QLabel* whiteSpaceLabel;
		QLabel* UserLabel;
		QLineEdit* UserInput;
		QLabel* PasswordLabel;
		QLineEdit* PasswordInput;
		QLabel* AgeLabel;
		QLineEdit* AgeInput;
		QLabel* CreditLabel;
		QLineEdit* CreditInput;
		QPushButton* AddButton;

		Store* ds;

		// QHBoxLayout* UserLayout;
		// QLabel* UserLabel;
		// QLineEdit* UserInput;
		// QLabel* PasswordLabel;
		// QLineEdit* PasswordInput;
		// QPushButton* LoginButton;
		// QPushButton* QuitButton;
		// QFrame* seperatorLine;
		// QPushButton* NewButton;


};

#endif 