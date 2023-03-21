#include "ServiceGUI2.h"

void ServiceGUI2::initializeGUIComponents() {

	QHBoxLayout* lyMain = new QHBoxLayout;
	this->setLayout(lyMain);


	QWidget* left = new QWidget;
	QVBoxLayout* lyLeft = new QVBoxLayout;
	left->setLayout(lyLeft);


	QWidget* formAdd = new QWidget;
	QFormLayout* lyFormAdd = new QFormLayout;
	formAdd->setLayout(lyFormAdd);
	editNrAp = new QLineEdit;

	lyFormAdd->addRow(lblNrAp, editNrAp);
	btnAdd = new QPushButton("Add tenant.");
	lyFormAdd->addWidget(btnAdd);


	lyLeft->addWidget(formAdd);


	QWidget* formRandom = new QWidget;
	QFormLayout* lyFormRandom = new QFormLayout;
	formRandom->setLayout(lyFormRandom);
	editRandom = new QLineEdit;

	lyFormRandom->addRow(lblRandom, editRandom);
	btnRandom = new QPushButton("Add random.");
	lyFormRandom->addWidget(btnRandom);


	lyLeft->addWidget(formRandom);


	btnRemove = new QPushButton("Delete all.");
	lyLeft->addWidget(btnRemove);


	btnDrawWindow = new QPushButton{ "Draw window." };
	btnDrawWindow->setStyleSheet("background-color: pink");
	lyLeft->addWidget(btnDrawWindow);


	QWidget* right = new QWidget;
	QVBoxLayout* lyRight = new QVBoxLayout;
	right->setLayout(lyRight);

	int noLines = 10;
	int noColumns = 4;
	this->table = new QTableView();
	this->model = new MyTableModel{ srv.getAllWishlist() };
	table->setModel(this->model);


	lyRight->addWidget(table);

	lyMain->addWidget(left);
	lyMain->addWidget(right);

}
void ServiceGUI2::reloadList(vector<Tenant> tenants) {
	this->model->setTenant(tenants);
}

void ServiceGUI2::connectSignalsSlots() {
	srv.getList().addObserver(this);

	QObject::connect(btnAdd, &QPushButton::clicked, this, &ServiceGUI2::guiAdd);

	QObject::connect(btnRandom, &QPushButton::clicked, this, &ServiceGUI2::guiRandom);

	QObject::connect(btnRemove, &QPushButton::clicked, [&]() {
		srv.deleteAll();
		this->reloadList(srv.getAllWishlist());
		QMessageBox::information(this, "Info", QString::fromStdString("Successufully removed."));
		});

	QObject::connect(btnDrawWindow, &QPushButton::clicked, this, [&]() {
		auto drawWindow = new ServiceGUI2Draw{ srv.getList() };
		drawWindow->show();
		});
}


void ServiceGUI2::guiAdd() {
	try {

		int NrAp = editNrAp->text().toInt();


		editNrAp->clear();

		this->srv.addToWishlist(NrAp);
		this->reloadList(this->srv.getAllWishlist());


		QMessageBox::information(this, "Info", QString::fromStdString("Successufully added."));

	}
	catch (RepoException& re) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(re.getErrorMsg()));
	}
	catch (ValidationException& ve) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ve.getErrorMsg()));
	}
}

void ServiceGUI2::guiRandom() {
	try {

		int nr = editRandom->text().toInt();

		editRandom->clear();
		srv.addRandom(nr);
		this->reloadList(this->srv.getAllWishlist());


		QMessageBox::information(this, "Info", QString::fromStdString("Successfully randomly added."));

	}
	catch (RepoException& re) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(re.getErrorMsg()));
	}
	catch (ValidationException& ve) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ve.getErrorMsg()));
	}
}