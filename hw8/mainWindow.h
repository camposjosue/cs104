#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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
#include <string>


class MainWindow : public QWidget {
	Q_OBJECT
	
	public:
		MainWindow(Store* ds, std::string current);
		~MainWindow();

		std::vector<Review*> currentReviews;

	private slots:
		void productSearch();
		void display();
		void addToCart();
		void showCartPopup();
		void addReviewPopup();
		void fileOutput();
		void index(int displayIndex);
		void ratingSort();
		void alphaSort();
		void closeWindow();

	private:

		void basicSimilarities(std::string person);
		std::map<User*, double> refinedSimilarities(std::string person);
		std::string makeReccomendation();
		QComboBox* dropDown;
		QHBoxLayout* OverallLayout;
		QVBoxLayout* formLayout;
		QVBoxLayout* searchLayout;
		QVBoxLayout* reviewLayout;
		QLineEdit* searchInput;
		QLineEdit* filenameInput;
		QLabel* searchLabel;
		QLabel* sortLabel;
		QLabel* userLabel;
		QLabel* reviewResultsLabel;
		QLabel* searchResultsLabel;
		QLabel* whiteSpaceLabel;
		QVBoxLayout* searchResultsLayout;
		QFrame* seperatorLine;
		QHBoxLayout* radioLayout;
		QRadioButton* ORsearch;
		QRadioButton* ANDsearch;
		QPushButton* searchButton;
		QPushButton* addreviewButton;
		QVBoxLayout* filterLayout;
		QVBoxLayout* userLayout;
		QPushButton* ratingButton;
		QPushButton* alphabeticalButton;
		QPushButton* addcartButton;
		QPushButton* saveButton;
		QPushButton* quitButton;
		QPushButton* viewcartButton;
		QListWidget* searchListWidget;
		QListWidget* reviewListWidget;

		CartWindow* myCart;
		ReviewWindow* myReview;

		std::vector<Product*> hits;
		//std::vector<string> searchTerms;

		int currentIndex;
		std::string current;
		Store* ds;

		bool openedCart;
		bool openedReview;

		

};

#endif 