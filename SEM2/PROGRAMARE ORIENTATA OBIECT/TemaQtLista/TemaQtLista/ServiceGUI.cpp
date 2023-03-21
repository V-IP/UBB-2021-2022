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
	editNrAp = new QLineEdit;
	editOwner = new QLineEdit;
	editType = new QLineEdit;
	editSurface = new QLineEdit;

	lyFormAdd->addRow(lblNrAp, editNrAp);
	lyFormAdd->addRow(lblOwner, editOwner);
	lyFormAdd->addRow(lblType, editType);
	lyFormAdd->addRow(lblSurface, editSurface);
	btnAdd = new QPushButton("Add tenant.");
	lyFormAdd->addWidget(btnAdd);


	lyLeft->addWidget(formAdd);

	QWidget* formRemove = new QWidget;
	QFormLayout* lyFormRemove = new QFormLayout;
	formRemove->setLayout(lyFormRemove);
	editRemoveFindNrAp = new QLineEdit();
	lyFormRemove->addRow(lblRemoveFindNrAp, editRemoveFindNrAp);
	btnRemove = new QPushButton("Remove tenant.");
	btnFind = new QPushButton("Find tenant.");
	lyFormRemove->addWidget(btnRemove);
	lyFormRemove->addWidget(btnFind);

	lyLeft->addWidget(formRemove);


	QWidget* formModify = new QWidget;
	QFormLayout* lyFormModify = new QFormLayout;
	formModify->setLayout(lyFormModify);
	editModifyNrAp = new QLineEdit();
	lyFormModify->addRow(lblModifyNrAp, editModifyNrAp);
	editModifyOwner = new QLineEdit();
	lyFormModify->addRow(lblModifyOwner, editModifyOwner);
	btnModify = new QPushButton("Modify tenant.");
	lyFormModify->addWidget(btnModify);

	lyLeft->addWidget(formModify);


	QVBoxLayout* lyRadioBox = new QVBoxLayout;
	this->groupSortBox->setLayout(lyRadioBox);
	lyRadioBox->addWidget(radioSortOwner);
	lyRadioBox->addWidget(radioSortSurface);
	lyRadioBox->addWidget(radioSortTypeSurface);

	btnSort = new QPushButton("Sort tenants.");
	lyRadioBox->addWidget(btnSort);


	lyLeft->addWidget(groupSortBox);


	QWidget* formFilterType = new QWidget;
	QFormLayout* lyFormFilterType = new QFormLayout;
	formFilterType->setLayout(lyFormFilterType);
	editFilterType = new QLineEdit();
	lyFormFilterType->addRow(lblFilterType, editFilterType);
	btnFilterType = new QPushButton("Filter by type");
	lyFormFilterType->addWidget(btnFilterType);

	lyLeft->addWidget(formFilterType);

	QWidget* formFilterSurface = new QWidget;
	QFormLayout* lyFormFilterSurface = new QFormLayout;
	formFilterSurface->setLayout(lyFormFilterSurface);
	editFilterSurface = new QLineEdit();
	lyFormFilterSurface->addRow(lblFilterSurface, editFilterSurface);
	btnFilterSurface = new QPushButton("Filter by surface");
	lyFormFilterSurface->addWidget(btnFilterSurface);

	lyLeft->addWidget(formFilterSurface);


	btnUndo = new QPushButton("Undo");
	lyLeft->addWidget(btnUndo);

	btnReloadData = new QPushButton("Reload data");
	lyLeft->addWidget(btnReloadData);

	btn2nd = new QPushButton("2nd View");
	lyLeft->addWidget(btn2nd);

	QWidget* right = new QWidget;
	QVBoxLayout* lyRight = new QVBoxLayout;
	right->setLayout(lyRight);

	gui2 = new ServiceGUI2(srv);

	int noLines = 10;
	int noColumns = 4;
	this->table = new QTableWidget{ noLines, noColumns };


	this->table->setSelectionBehavior(QAbstractItemView::SelectRows);
	QStringList tblHeaderList;
	tblHeaderList << "Number" << "Owner" << "Type" << "Surface";
	this->table->setHorizontalHeaderLabels(tblHeaderList);


	this->table->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);


	lyRight->addWidget(table);

	lyMain->addWidget(left);
	lyMain->addWidget(right);

}
void ServiceGUI::reloadList(vector<Tenant> tenants) {
	this->table->clearContents();
	this->table->setRowCount(tenants.size());

	int lineNumber = 0;
	for (auto& t : tenants) {
		QTableWidgetItem* item1 = new QTableWidgetItem(QString::number(t.getNrAp()));
		//item1->setBackground(Qt::red);
		this->table->setItem(lineNumber, 0, item1);
		this->table->setItem(lineNumber, 1, new QTableWidgetItem(QString::fromStdString(t.getOwner())));
		this->table->setItem(lineNumber, 2, new QTableWidgetItem(QString::fromStdString(t.getType())));
		this->table->setItem(lineNumber, 3, new QTableWidgetItem(QString::number(t.getSurface())));
		lineNumber++;
	}
}

void ServiceGUI::connectSignalsSlots() {
	QObject::connect(btnAdd, &QPushButton::clicked, this, &ServiceGUI::guiAdd);

	QObject::connect(btnSort, &QPushButton::clicked, [&]() {
		if (this->radioSortOwner->isChecked())
			this->reloadList(srv.sort_srv(cmp_name));
		else if (this->radioSortSurface->isChecked())
			this->reloadList(srv.sort_srv(cmp_surface));
		else if (this->radioSortTypeSurface->isChecked())
			this->reloadList(srv.sort_srv(cmp_type_surface));
		});

	QObject::connect(btnRemove, &QPushButton::clicked, this, &ServiceGUI::guiRemove);

	QObject::connect(btnModify, &QPushButton::clicked, this, &ServiceGUI::guiModify);

	QObject::connect(btnFind, &QPushButton::clicked, [&]() {
		try {
			int NrAp = this->editRemoveFindNrAp->text().toInt();
			Tenant tenant = srv.find_srv(NrAp);
			vector<Tenant> vector;
			vector.push_back(tenant);
			this->reloadList(vector);
			editRemoveFindNrAp->clear();
		}
		catch (RepoException& re) {
			QMessageBox::warning(this, "Warning", QString::fromStdString(re.getErrorMsg()));
		}
		catch (ValidationException& ve) {
			QMessageBox::warning(this, "Warning", QString::fromStdString(ve.getErrorMsg()));
		}
		});

	QObject::connect(btnFilterType, &QPushButton::clicked, [&]() {
		string filterC = this->editFilterType->text().toStdString();
		this->reloadList(srv.filter_srv(filterC, -1));
		editFilterType->clear();
		});

	QObject::connect(btnFilterSurface, &QPushButton::clicked, [&]() {
		double filterC = this->editFilterSurface->text().toDouble();
		this->reloadList(srv.filter_srv("-1", filterC));
		editFilterSurface->clear();
		});

	QObject::connect(btnUndo, &QPushButton::clicked, [&]() {
		try {
			srv.undo();
			this->reloadList(srv.getAll_srv());
		}
		catch (RepoException& re) {
			QMessageBox::warning(this, "Warning", QString::fromStdString(re.getErrorMsg()));
		}
		catch (ValidationException& ve) {
			QMessageBox::warning(this, "Warning", QString::fromStdString(ve.getErrorMsg()));
		}
		});

	QObject::connect(btnReloadData, &QPushButton::clicked, [&]() {
		this->reloadList(srv.getAll_srv());
		});

	QObject::connect(btn2nd, &QPushButton::clicked, [&]() {
		gui2->show();
		});

	QObject::connect(table, &QTableWidget::currentCellChanged, [&](int currentRow, int currentCol, int PreviousRow, int previousCol) {
		if (currentRow < 0) return;
		Tenant t = srv.getAll_srv()[currentRow];
		editRemoveFindNrAp->setText(std::to_string(t.getNrAp()).c_str());
		});

	QObject::connect(table, &QTableWidget::itemSelectionChanged, [&]() {
		auto elem = table->selectedItems();
		for (auto x : elem) {
			x->setBackground(Qt::green);
		}
		});

}


void ServiceGUI::guiAdd() {
	try {

		int NrAp = editNrAp->text().toInt();
		string Owner = editOwner->text().toStdString();
		string Type = editType->text().toStdString();
		double Surface = editSurface->text().toDouble();


		editNrAp->clear();
		editOwner->clear();
		editType->clear();
		editSurface->clear();

		this->srv.add_srv(NrAp, Owner, Type, Surface);
		this->reloadList(this->srv.getAll_srv());


		QMessageBox::information(this, "Info", QString::fromStdString("Successufully added."));

	}
	catch (RepoException& re) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(re.getErrorMsg()));
	}
	catch (ValidationException& ve) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ve.getErrorMsg()));
	}
}

void ServiceGUI::guiRemove() {
	try {

		int NrAp = editRemoveFindNrAp->text().toInt();

		editRemoveFindNrAp->clear();

		this->srv.remove_srv(NrAp);
		this->reloadList(this->srv.getAll_srv());


		QMessageBox::information(this, "Info", QString::fromStdString("Successufully removed."));

	}
	catch (RepoException& re) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(re.getErrorMsg()));
	}
	catch (ValidationException& ve) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ve.getErrorMsg()));
	}
}

void ServiceGUI::guiModify() {
	try {

		int NrAp = editModifyNrAp->text().toInt();
		string Owner = editModifyOwner->text().toStdString();

		editModifyNrAp->clear();
		editModifyOwner->clear();

		this->srv.modify_srv(NrAp, Owner);
		this->reloadList(this->srv.getAll_srv());


		QMessageBox::information(this, "Info", QString::fromStdString("Successufully modified."));

	}
	catch (RepoException& re) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(re.getErrorMsg()));
	}
	catch (ValidationException& ve) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ve.getErrorMsg()));
	}
}