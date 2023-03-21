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
#include <QHeaderView>
#include <QGroupBox>
#include <QRadioButton>
#include <QPainter>
#include "ServiceGUI2.h"

using std::vector;
using std::string;
class ServiceGUI : public QWidget {
private:

	Service& srv;
	ServiceGUI2 gui2{ srv };

	QLabel* lblNrAp = new QLabel{ "Apartment number:" };
	QLabel* lblOwner = new QLabel{ "Apartment owner:" };
	QLabel* lblType = new QLabel{ "Type:" };
	QLabel* lblSurface = new QLabel{ "Surface:" };

	QLineEdit* editNrAp;
	QLineEdit* editOwner;
	QLineEdit* editType;
	QLineEdit* editSurface;

	QPushButton* btnAdd;

	QLabel* lblRemoveFindNrAp = new QLabel{ "Apartment number:" };
	QLineEdit* editRemoveFindNrAp;
	QPushButton* btnRemove;
	QPushButton* btnFind;

	QLabel* lblModifyNrAp = new QLabel{ "Apartment number:" };
	QLabel* lblModifyOwner = new QLabel{ "New owner name:" };
	QLineEdit* editModifyNrAp;
	QLineEdit* editModifyOwner;
	QPushButton* btnModify;

	QGroupBox* groupSortBox = new QGroupBox(tr("Sort criteria:"));

	QRadioButton* radioSortOwner = new QRadioButton(QString::fromStdString("by Owner"));
	QRadioButton* radioSortSurface = new QRadioButton(QString::fromStdString("by Surface"));
	QRadioButton* radioSortTypeSurface = new QRadioButton(QString::fromStdString("Type+Surface"));
	QPushButton* btnSort;

	QLabel* lblFilterType = new QLabel{ "Filter by type:   " };
	QLineEdit* editFilterType;
	QPushButton* btnFilterType;

	QLabel* lblFilterSurface = new QLabel{ "Filter by surface:" };
	QLineEdit* editFilterSurface;
	QPushButton* btnFilterSurface;

	QPushButton* btnUndo;
	QPushButton* btnReloadData;
	QPushButton* btn2nd;

	QTableWidget* table;


	void initializeGUIComponents();
	void connectSignalsSlots();
	void reloadList(vector<Tenant> tenants);
public:
	ServiceGUI(Service& srv) : srv{ srv } {
		initializeGUIComponents();
		connectSignalsSlots();
		reloadList(srv.getAll_srv());
	}
	void guiAdd();
	void guiRemove();
	void guiModify();
};
