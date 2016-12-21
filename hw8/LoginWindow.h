#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

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
#include "userWindow.h"


class LoginWindow : public QWidget {
	Q_OBJECT
	
	public:
		LoginWindow(Store* ds);
		~LoginWindow();

		//std::vector<Review*> currentReviews;

	private slots:
		void attemptLogin();
		void closeWindow();
		void newUser();

		// void productSearch();
		// void display();
		// void addToCart();
		// void showCartPopup();
		// void addReviewPopup();
		// void fileOutput();
		// void index(int displayIndex);
		// void ratingSort();
		// void alphaSort();
		//void closeWindow();

	private:
		long long hash(std::string password);
		MainWindow* myWindow;
		UserWindow* myUser;
		QVBoxLayout* OverallLayout;
		QHBoxLayout* UserLayout;
		QLabel* UserLabel;
		QLineEdit* UserInput;
		QLabel* PasswordLabel;
		QLineEdit* PasswordInput;
		QPushButton* LoginButton;
		QPushButton* QuitButton;
		QFrame* seperatorLine;
		QPushButton* NewButton;
		// QComboBox* dropDown;
		// QHBoxLayout* OverallLayout;
		// QVBoxLayout* formLayout;
		// QVBoxLayout* searchLayout;
		// QVBoxLayout* reviewLayout;
		// QLineEdit* searchInput;
		// QLineEdit* filenameInput;
		// QLabel* searchLabel;
		// QLabel* sortLabel;
		// QLabel* userLabel;
		// QLabel* reviewResultsLabel;
		// QLabel* searchResultsLabel;
		// QLabel* whiteSpaceLabel;
		// QVBoxLayout* searchResultsLayout;
		// QFrame* seperatorLine;
		// QHBoxLayout* radioLayout;
		// QRadioButton* ORsearch;
		// QRadioButton* ANDsearch;
		// QPushButton* searchButton;
		// QPushButton* addreviewButton;
		// QVBoxLayout* filterLayout;
		// QVBoxLayout* userLayout;
		// QPushButton* ratingButton;
		// QPushButton* alphabeticalButton;
		// QPushButton* addcartButton;
		// QPushButton* saveButton;
		// QPushButton* quitButton;
		// QPushButton* viewcartButton;
		// QListWidget* searchListWidget;
		// QListWidget* reviewListWidget;


		Store* ds;

};

#endif 