#pragma once
#include <vector>
#include <string>
#include <QtWidgets/QApplication>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QMessageBox>
#include <QTableWidget>
#include <QHeaderView>
#include <QGroupBox>
#include <QRadioButton>
#include <QPainter>
#include "Service.h"
#include "MyTableModel.h"

using std::vector;
using std::string;
class ServiceGUI2 : public QWidget, public Observer {
private:

	Service& srv;

	QLabel* lblNrAp = new QLabel{ "Apartment number:" };
	QLineEdit* editNrAp;
	QPushButton* btnAdd;

	QPushButton* btnRemove;

	QLabel* lblRandom = new QLabel{ "Enter a number:" };
	QLineEdit* editRandom;
	QPushButton* btnRandom;

	QPushButton* btnDrawWindow;

	QTableView* table;
	MyTableModel* model;


	void initializeGUIComponents();
	void connectSignalsSlots();
	void reloadList(vector<Tenant> tenants);

	void update() override {
		reloadList(srv.getAllWishlist());
	}
public:
	explicit ServiceGUI2(Service& srv) : srv{ srv } {
		initializeGUIComponents();
		connectSignalsSlots();
		reloadList(srv.getAllWishlist());
	}
	void guiAdd();
	void guiRandom();
};

class ServiceGUI2Draw : public QWidget, public Observer {
private:
	WishList& wishlist;
protected:
	void paintEvent(QPaintEvent*) override {
		int x = 10, y = 10, w = 10;
		QPainter p{ this };
		p.setPen(Qt::blue);
		for (const auto t : wishlist.getAllWishList()) {
			p.drawRect(x, y, w, t.getSurface() * 10);
			x += 50;
		}
	}
public:
	ServiceGUI2Draw(WishList& wishlist) :wishlist{ wishlist } {
		wishlist.addObserver(this);
		update();
	}
	void update() override {
		repaint();
	}
	~ServiceGUI2Draw() {
		wishlist.removeObserver(this);
	}
};