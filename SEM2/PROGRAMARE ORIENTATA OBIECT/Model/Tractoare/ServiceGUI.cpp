#include "ServiceGUI.h"

void ServiceGUI::initializeGUIComponents() {


	QHBoxLayout* lyMain = new QHBoxLayout;
	this->setLayout(lyMain);


	QWidget* left = new QWidget;
	QVBoxLayout* lyLeft = new QVBoxLayout;
	left->setLayout(lyLeft);


	QWidget* formAdd = new QWidget;
	QFormLayout* lyFormAdd = new QFormLayout;
	formAdd->setLayout(lyFormAdd);
	editId = new QLineEdit;
	editDenumire = new QLineEdit;
	editTip = new QLineEdit;
	editNrRoti = new QLineEdit;

	lyFormAdd->addRow(lblId, editId);
	lyFormAdd->addRow(lblDenumire, editDenumire);
	lyFormAdd->addRow(lblTip, editTip);
	lyFormAdd->addRow(lblNrRoti, editNrRoti);
	btnAdd = new QPushButton("Add.");
	lyFormAdd->addWidget(btnAdd);

	comboBox = new QComboBox;
	vector<string> tipuri;
	for (int i = 0; i < srv.getAll_srv().size(); i++) {
		bool sem = false;
		for (const auto el : tipuri)
			if (el == srv.getAll_srv()[i].getTip())
				sem = true;
		if (sem == false) {
			comboBox->addItem(QString::fromStdString(srv.getAll_srv()[i].getTip()));
			tipuri.push_back(srv.getAll_srv()[i].getTip());
		}
	}
	lyFormAdd->addWidget(comboBox);
	lyLeft->addWidget(formAdd);


	QWidget* right = new QWidget;
	QVBoxLayout* lyRight = new QVBoxLayout;
	right->setLayout(lyRight);


	this->table = new QTableView;
	this->model = new MyTableModel(srv.getAll_srv(), "");
	this->table->setModel(model);

	lyRight->addWidget(table);

	lyMain->addWidget(left);
	lyMain->addWidget(right);

}


void ServiceGUI::connectSignalsSlots() {
	QObject::connect(btnAdd, &QPushButton::clicked, this, &ServiceGUI::guiAdd);

	QObject::connect(comboBox, &QComboBox::currentTextChanged, [this]() {
		this->model = new MyTableModel(srv.getAll_srv(), comboBox->currentText().toStdString());
		this->table->setModel(model);
		});
	QObject::connect(this->table->selectionModel(), &QItemSelectionModel::selectionChanged, [this]() {
		Obj o = srv.getAll_srv()[this->table->selectionModel()->selectedIndexes().at(0).row()];
		ServiceGUIDraw draw(srv);
		draw.update();
		});
}


void ServiceGUI::guiAdd() {
	try {

		int id = editId->text().toInt();
		string denumire = editDenumire->text().toStdString();
		string tip = editTip->text().toStdString();
		int nrRoti = editNrRoti->text().toDouble();


		editId->clear();
		editDenumire->clear();
		editTip->clear();
		editNrRoti->clear();

		bool sem = false;
		for (int i = 0; i < comboBox->count(); i++) {
			if (comboBox->currentText().toStdString() == tip)
				sem = true;
		}
		if (sem == false) {
			comboBox->addItem(QString::fromStdString(tip));
		}

		this->srv.add_srv(id, denumire, tip, nrRoti);
		model->setObj(srv.getAll_srv());

		QMessageBox::information(this, "Info", QString::fromStdString("Successufully added."));

	}
	catch (RepoException& re) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(re.getErrorMsg()));
	}
	catch (ValidationException& ve) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ve.getErrorMsg()));
	}
}