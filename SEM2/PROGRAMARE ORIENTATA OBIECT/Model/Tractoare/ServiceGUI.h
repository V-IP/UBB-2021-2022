#pragma once
#include <vector>
#include <string>
#include <QtWidgets/QApplication>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QTableWidget>
#include <QMessageBox>
#include <QTableView>
#include <QHeaderView>
#include <QGroupBox>
#include <QRadioButton>
#include <QPainter>
#include <QComboBox>
#include "Service.h"
#include "MyTableModel.h"

using std::vector;
using std::string;
class ServiceGUI : public QWidget {
private:

	Service& srv;

	QLabel* lblId = new QLabel{ "Id:" };
	QLabel* lblDenumire = new QLabel{ "Denumire:" };
	QLabel* lblTip = new QLabel{ "Tip:" };
	QLabel* lblNrRoti = new QLabel{ "Numar de roti:" };

	QLineEdit* editId;
	QLineEdit* editDenumire;
	QLineEdit* editTip;
	QLineEdit* editNrRoti;

	QComboBox* comboBox;

	QPushButton* btnAdd;

	MyTableModel* model;
	QTableView* table;


	void initializeGUIComponents();
	void connectSignalsSlots();
public:
	ServiceGUI(Service& srv) : srv{ srv } {
		initializeGUIComponents();
		connectSignalsSlots();
	}
	void guiAdd();
};

class ServiceGUIDraw : public QWidget {
private:
	Service& srv;
protected:
	void paintEvent(QPaintEvent*) override {
		QPainter p{ this };
		p.setPen(Qt::blue);
		for (const auto o : srv.getAll_srv()) {
			p.drawEllipse(QPoint(0, 1), 1, 1);
		}
	}
public:
	ServiceGUIDraw(Service& srv) :srv{ srv } {
		update();
	}
	void update() {
		repaint();
	}
};