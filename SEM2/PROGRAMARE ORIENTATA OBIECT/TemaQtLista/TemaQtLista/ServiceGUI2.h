#pragma once
#include <QtWidgets/QApplication>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QListWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QFormLayout>
#include <QMessageBox>
#include <string>
#include <vector>
#include "Service.h"
using std::to_string;
using std::vector;

class ServiceGUI2 :public QWidget {
private:
	Service& srv;
	QHBoxLayout* lyMain;
	QListWidget* lst;

	QLabel* lblNrAp = new QLabel{ "Apartment number:" };
	QLineEdit* editNrAp;
	QPushButton* btnAdd;

	QPushButton* btnRemove;

	QLabel* lblRandom = new QLabel{ "Enter a number:" };
	QLineEdit* editRandom;
	QPushButton* btnRandom;

	void initializeGUIComponents();
	void connectSignalsSlots();
	void reloadList(vector<Tenant> tenants);
public:
	explicit ServiceGUI2(Service& srv) : srv{ srv } {
		initializeGUIComponents();
		connectSignalsSlots();
		reloadList(srv.getAllWishlist());
	}
	void guiAdd();
	void guiRandom();
};