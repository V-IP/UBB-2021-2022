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


	editRandom = new QLineEdit;

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

	QWidget* right = new QWidget;
	QVBoxLayout* lyRight = new QVBoxLayout;
	right->setLayout(lyRight);

	lst = new QListWidget;
	lst->setFixedWidth(320);
	lst->setSelectionMode(QAbstractItemView::SingleSelection);

	lyRight->addWidget(lst);

	lyMain->addWidget(left);
	lyMain->addWidget(right);
}

void ServiceGUI2::reloadList(vector<Tenant> all) {
	this->lst->clear();
	for (auto& t : all) {
		QString currentItem=QString::QString::fromStdString(to_string(t.getNrAp()) + "\t" + t.getOwner() + "\t" + t.getType() + "\t" + to_string(t.getSurface()));
		this->lst->addItem(currentItem);
	}
}

void ServiceGUI2::connectSignalsSlots() {
	QObject::connect(btnAdd, &QPushButton::clicked, this, &ServiceGUI2::guiAdd);
	QObject::connect(btnRandom, &QPushButton::clicked, this, &ServiceGUI2::guiRandom);
	QObject::connect(btnRemove, &QPushButton::clicked, [&]() {
		srv.deleteAll();
		this->reloadList(srv.getAllWishlist());
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