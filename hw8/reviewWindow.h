#ifndef REVIEWWINDOW_H
#define REVIEWWINDOW_H

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
#include "product.h"
#include "datastore.h"
#include "db_parser.h"
#include "product_parser.h"
#include "util.h"
#include "store.h"
//#include "mainWindow.h"

class ReviewWindow : public QWidget {
	Q_OBJECT
	
	public:
		ReviewWindow();
		ReviewWindow(Store* ds, Product* thing, QListWidget* temp, std::string current);
		~ReviewWindow();

	private slots:
		void add();
	

	private:
		QVBoxLayout* OverallLayout;
		QLabel* titleLabel;
		QPushButton* addButton;
		QPushButton* cancelButton;
		QHBoxLayout* ratingLayout;
		QVBoxLayout* dateLayout;
		QHBoxLayout* yearLayout;
		QHBoxLayout* monthLayout;
		QHBoxLayout* dayLayout;
		QVBoxLayout* reviewLayout;
		QLabel* ratingLabel;
		QLineEdit* ratingInput;
		QLabel* yearLabel;
		QLineEdit* yearInput;
		QLabel* monthLabel;
		QLineEdit* monthInput;
		QLabel* dayLabel;
		QLineEdit* dayInput;
		QLabel* reviewLabel;
		QTextEdit* reviewInput;
		QFrame* seperatorLine;
		QRadioButton* rating1;
		QRadioButton* rating2;
		QRadioButton* rating3;
		QRadioButton* rating4;
		QRadioButton* rating5;

		QListWidget* view;

		Store* ds;
		std:: string current;
		Product* currentItem;

};

#endif