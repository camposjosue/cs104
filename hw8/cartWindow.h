#ifndef CARTWINDOW_H
#define CARTWINDOW_H

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


class CartWindow : public QWidget {
	Q_OBJECT
	
	public:
		CartWindow(Store* ds, std::string current);
		~CartWindow();

	private slots:
		void display();
		void remove();
		void index(int displayIndex);
		void buying();

	private:
		QVBoxLayout* OverallLayout;
		QHBoxLayout* buttonLayout;
		QLabel* titleLabel;
		QListWidget* cartListWidget;
		QPushButton* removeButton;
		QPushButton* buyButton;
		QPushButton* closeButton;

		Store* ds;
		std::string buyer;

		int currentIndex;

};

#endif