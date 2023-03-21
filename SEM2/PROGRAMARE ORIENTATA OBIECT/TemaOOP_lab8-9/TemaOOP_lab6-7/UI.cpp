#include"UI.h"
#include<iostream>
#include<fstream>
#include<string>
using std::cout;
using std::cin;
using std::endl;

using namespace std;

void ConsoleUI::printMenu() {
	cout << "	Options for App:\n";
	cout << "	0.  Exit\n";
	cout << "	1.  Add\n";
	cout << "	2.  Delete\n";
	cout << "	3.  Modify\n";
	cout << "	4.  find\n";
	cout << "	5.  Filter\n";
	cout << "	6.  Sort\n";
	cout << "	7.  Undo\n";
	cout << "	8.  Print all\n";
	cout << "	Options for WishList:\n";
	cout << "	9.  Add WishList\n";
	cout << "	10. Delete WishList\n";
	cout << "	11. Add Random\n";
	cout << "	12. Save to HTML\n";
	cout << "	13. Print WishList\n";
}

void ConsoleUI::uiAdd() {
	int nrAp; string owner, type; double surface;
	cout << "Enter the apartment number: ";
	cin >> nrAp;
	cout << "Enter the apartment owner name: ";
	getline(cin >> ws, owner);
	cout << "Enter the apartment type: ";
	getline(cin >> ws, type);
	cout << "Enter the apartment surface: ";
	cin >> surface;

	try {
		srv.add_srv(nrAp, owner, type, surface);
	}
	catch (RepoException& re) {
		cout << re.getErrorMsg();
	}
	catch (ValidationException& ve) {
		cout << ve.getErrorMsg();
	}
	cout << endl << "Succesfully added!" << endl;
}

void ConsoleUI::uiModify() {
	int nrAp; string newOwner;
	cout << "Enter the apartment number: ";
	cin >> nrAp;
	cout << "Enter the new apartment owner name: ";
	getline(cin >> ws, newOwner);
	try {
		srv.modify_srv(nrAp, newOwner);
	}
	catch (RepoException& re) {
		cout << re.getErrorMsg();
	}
	catch (ValidationException& ve) {
		cout << ve.getErrorMsg();
	}
	cout << endl << "Succesfully modified!" << endl;
}

void ConsoleUI::uiRemove() {
	int nrAp;
	cout << "Enter the apartment number: ";
	cin >> nrAp;
	try {
		srv.remove_srv(nrAp);
	}
	catch (RepoException& re) {
		cout << re.getErrorMsg();
	}
	catch (ValidationException& ve) {
		cout << ve.getErrorMsg();
	}
	cout << endl << "Succesufully removed!" << endl;
}

void ConsoleUI::uiFind() {
	int nrAp;
	cout << "Enter the apartment number: ";
	cin >> nrAp;
	try {
		Tenant tenant = srv.find_srv(nrAp);
		cout << "Nr.: " << tenant.getNrAp() << " | Owner: " << tenant.getOwner() << " | Type: " << tenant.getType() << " | surface: " << tenant.getSurface() << endl;
	}
	catch (RepoException& re) {
		cout<<re.getErrorMsg();
	}
}

void ConsoleUI::uiFilter() {
	try {
		int opt;
		cout << "By what criteria do you want to filter, sir?\n";
		cout << "1. Type | 2. Surface\n";
		cin >> opt;
		string type_criteria="-1"; double surface_criteria=-1;
		if (opt == 1) {
			cout << "Enter the type criteria: ";
			getline(cin >> ws, type_criteria);
		}
		else {
			cout << "Enter the urface criteria: ";
			cin >> surface_criteria;
		}
		vector<Tenant> filtered = srv.filter_srv(type_criteria, surface_criteria);
		if (filtered.size() == 0)
			cout << "There are no apartments with this criteria." << endl << endl;
		else
			for (const auto& tenant : filtered) {
				cout << "Nr.: " << tenant.getNrAp() << " | Owner: " << tenant.getOwner() << " | Type: " << tenant.getType() << " | surface: " << tenant.getSurface() << endl;
			}
	}
	catch (ValidationException& ve) {
		cout << ve.getErrorMsg();
	}
}

void ConsoleUI::uiSort() {
	vector<Tenant> sorted;
	int reversed;
	cout << "Do you want to Sort descending, sir?\n";
	cout << "0. No	| 1. Yes\n";
	cin >> reversed;
	int opt;
	cout << "By what criteria do you want to Sort, sir?\n";
	cout << "1. Owner name	|	2. Surface	|	3. Type + Surface\n";
	cin >> opt;
	if (reversed == 0) {
		if (opt == 1) {
			sorted = srv.sort_srv(cmp_name);
		}
		if (opt == 2) {
			sorted = srv.sort_srv(cmp_surface);
		}
		if (opt == 3) {
			sorted = srv.sort_srv(cmp_type_surface);
		}
	}
	if (reversed == 1) {
		if (opt == 1) {
			sorted = srv.sort_srv(cmpR_name);
		}
		if (opt == 2) {
			sorted = srv.sort_srv(cmpR_surface);
		}
		if (opt == 3) {
			sorted = srv.sort_srv(cmpR_type_surface);
		}
	}
	if (sorted.size() == 0)
		cout << "There are no apartments with this criteria." << endl << endl;
	else
		for (const auto& tenant : sorted) {
			cout << "Nr.: " << tenant.getNrAp() << " | Owner: " << tenant.getOwner() << " | Type: " << tenant.getType() << " | surface: " << tenant.getSurface() << endl;
		}
}

void ConsoleUI::uiUndo() {
	try {
		srv.undo();
		cout << "Undo operation went successfully!\n";
	}
	catch (RepoException& re) {
		cout << re.getErrorMsg();
	}
}

void ConsoleUI::printAll() {
	const vector<Tenant>& tenants = srv.getAll_srv();
	if (tenants.size() == 0)
		cout << "There are no apartments." << endl << endl;
	else
		for (const auto& tenant : tenants) {
			cout << "Nr.: " << tenant.getNrAp() << " | Owner: " << tenant.getOwner() << " | Type: " << tenant.getType() << " | surface: " << tenant.getSurface() << endl;
		}
}

void ConsoleUI::addWishlist() {
	cout << "Enter the apartment number: ";
	int numar;
	cin >> numar;
	try {
		srv.addToWishlist(numar);
		cout << "ADDED TO THE LIST...\n";
	}
	catch (RepoException& re) {
		cout << re.getErrorMsg();
	}
}
void ConsoleUI::deleteWishlist() {
	srv.deleteAll();
	cout << "Toti locatarii au fost stersi din lista...\n\n";
}
void ConsoleUI::addRandom() {
	cout << "Introduceti numarul de locatari pentru a fi adaugati aleator: ";
	int numar;
	cin >> numar;
	try {
		srv.addRandom(numar);
		cout << "Au fost adaugati " << numar << " locatari aleator\n\n";
	}
	catch (RepoException& re) {
		cout << re.getErrorMsg();
	}
}
void ConsoleUI::printWishList() {
	const vector<Tenant>& all = srv.getAllWishlist();
	if (all.size() == 0)
		cout << "Nu exista locatari." << endl;
	else
		for (const auto& tenant : all) {
			cout << "Nr.: " << tenant.getNrAp() << " | Owner: " << tenant.getOwner() << " | Type: " << tenant.getType() << " | surface: " << tenant.getSurface() << endl;
		}
}
void ConsoleUI::saveToHtml() {
	string fisier;
	cout << "Enter the filename: ";
	cin >> fisier;
	fisier.append(".html");
	std::ofstream fout(fisier);
	fout << "====LISTA====" << " <p> ";
	fout << "<html><body>" << endl;
	fout << "<table border=\"1\" style=\"width:100 % \">" << endl;
	for (auto& elem : srv.getAllWishlist()) {
		fout << "<tr>";
		fout << "<td>" << elem.getNrAp() << "</td>" << endl;
		fout << "<td>" << elem.getOwner() << "</td>" << endl;
		fout << "<td>" << elem.getSurface() << "</td>" << endl;
		fout << "<td>" << elem.getType() << "</td>" << endl;
		fout << "</tr>" << endl;
	}
	fout << "</table>" << endl;
	fout << "</body></html>" << endl;
	cout << "Successfully saved...\n\n";
	fout.close();
}

void ConsoleUI::updateMap() {
	srv.updateMap_srv();
}

void ConsoleUI::printMap() {
	unordered_map<string, int> umap = srv.getAllMap_srv();
	cout << "UMAP:" << endl;
	for (auto x : umap)
		cout << "Type: " << x.first << " <-> Number: " << x.second << endl;
}

void ConsoleUI::run() {
	int running = 1;
	int opt;
	while (running) {
		printMenu();
		cout << "Select an option: ";
		cin >> opt;
		switch (opt)
		{
		case 0:
			running = 0;
			break;
		case 1:
			uiAdd();
			updateMap();
			break;
		case 2:
			uiRemove();
			updateMap();
			break;
		case 3:
			uiModify();
			break;
		case 4:
			uiFind();
			break;
		case 5:
			uiFilter();
			break;
		case 6:
			uiSort();
			break;
		case 7:
			uiUndo();
		case 8:
			printAll();
			printMap();
			break;
		case 9:
			addWishlist();
			break;
		case 10:
			deleteWishlist();
			break;
		case 11:
			addRandom();
			break;
		case 12:
			saveToHtml();
			break;
		case 13:
			printWishList();
			break;
		default:
			cout << "Invalid option!" << endl;
		}
	}
}