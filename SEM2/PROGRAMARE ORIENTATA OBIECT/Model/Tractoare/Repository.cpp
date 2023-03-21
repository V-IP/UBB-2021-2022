#include "Repository.h"
#include <fstream>
#include <sstream>


const vector<Obj>& Repository::getAll() {
	for (int i = 0; i < all.size(); i++)
	{
		for (int j = i + 1; j < all.size(); j++)
			if (all[i].getDenumire() > all[j].getDenumire())
			{
				Obj aux = all[i];
				all[i] = all[j];
				all[j] = aux;
			}
	}
	return this->all;
}

const Obj& Repository::find(int id) {
	auto rez = std::find_if(all.begin(), all.end(), [id](const Obj& obj) {
		return obj.getId() == id;
		});
	if (rez != all.end()) {
		const Obj& obj = *rez;
		return obj;
	}
	throw RepoException("The object doesn't exists!\n");
}

bool Repository::exists(const Obj& obj) {
	try {
		find(obj.getId());
		return true;
	}
	catch (RepoException) {
		return false;
	}
}

void Repository::add(const Obj& obj) {
	if (exists(obj)) {
		throw RepoException("The object already exists!\n");
	}
	all.push_back(obj);
}

void FileRepository::loadFromFile() {
	ifstream file(this->filename);
	if (!file.is_open()) {
		throw RepoException("Cannot read from file" + filename);
	}
	string line;
	while (getline(file, line)) {
		int id; string denumire; string tip; int nrRoti;
		stringstream linestream(line);
		string current_item;
		int item_no = 0;
		while (getline(linestream, current_item, ','))
		{
			if (item_no == 0) id = stoi(current_item);
			if (item_no == 1) denumire = current_item;
			if (item_no == 2) tip = current_item;
			if (item_no == 3) nrRoti = stoi(current_item);
			item_no++;
		}
		Obj obj{ id,denumire,tip,nrRoti };
		Repository::add(obj);
	}
	file.close();
}

void FileRepository::saveToFile() {
	ofstream fout(this->filename);
	if (!fout.is_open())
		throw RepoException("Cannot write to file" + filename);
	for (auto& tenant : getAll()) {
		fout << tenant.getId() << ",";
		fout << tenant.getDenumire() << ",";
		fout << tenant.getTip() << ",";
		fout << tenant.getNrRoti() << endl;
	}
	fout.close();
}

void FileRepository::add(const Obj& obj) {
	Repository::add(obj);
	saveToFile();
}