#include <assert.h>
#include <random>
#include <fstream>
#include <sstream>
#include <iostream>

#include "Repository.h"
#include "Undo.h"

const vector<Tenant>& Repository::getAll() noexcept {
	return this->all;
}

const Tenant& Repository::find(int nrAp) {
	auto rez = std::find_if(all.begin(), all.end(), [nrAp](const Tenant& t) {
		return t.getNrAp() == nrAp;
		});
	if (rez != all.end()) {
		const Tenant& t = *rez;
		return t;
	}
	throw RepoException("The object doesn't exists!\n");
}

bool Repository::exists(const Tenant& tenant) {
	try {
		find(tenant.getNrAp());
		return true;
	}
	catch (RepoException) {
		return false;
	}
}

void Repository::add(const Tenant& tenant) {
	if (exists(tenant)) {
		throw RepoException("The object already exists!\n");
	}
	all.push_back(tenant);
}


void Repository::remove(const Tenant& tenant) {
	exists(tenant);
	for (int i = 0; i < this->all.size(); i++)
		if (tenant.getNrAp() == this->all[i].getNrAp()) {
			this->all.erase(this->all.begin() + i);
			break;
		}
}


void Repository::modify(const Tenant& tenant, const Tenant& newTenant) {
	exists(tenant);
	for (int i = 0; i < this->all.size(); i++)
		if (this->all[i].getNrAp() == tenant.getNrAp()) {
			this->all[i].setOwner(newTenant.getOwner());
			break;
		}
}

void FileRepository::loadFromFile() {
	ifstream file(this->filename);
	if (!file.is_open()) {
		throw RepoException("Cannot read from file" + filename);
	}
	string line;
	while (getline(file, line)) {
		int nrAp; string owner; string type; double surface;
		stringstream linestream(line);
		string current_item;
		int item_no = 0;
		while (getline(linestream, current_item, ','))
		{
			if (item_no == 0) nrAp = stoi(current_item);
			if (item_no == 1) owner = current_item;
			if (item_no == 2) type = current_item;
			if (item_no == 3) surface = stod(current_item);
			item_no++;
		}
		Tenant t{ nrAp,owner,type,surface };
		Repository::add(t);
	}
	file.close();
}

void FileRepository::saveToFile() {
	ofstream fout(this->filename);
	if (!fout.is_open())
		throw RepoException("Cannot write to file" + filename);
	for (auto& tenant : getAll()) {
		fout << tenant.getNrAp() << ",";
		fout << tenant.getOwner() << ",";
		fout << tenant.getType() << ",";
		fout << tenant.getSurface() << endl;
	}
	fout.close();
}

void FileRepository::add(const Tenant& t) {
	Repository::add(t);
	saveToFile();
}

void WishList::addToWishlist(int nr)
{
	int found = 0;
	for (const auto& t : repo.getAll()) {
		if (t.getNrAp() == nr) {
			wishlist.push_back(t);
			found = 1;
			break;
		}
	}
	if (found == 0)
		throw RepoException("Non-existent tenant!\n");
	else return;
}

const vector<Tenant> WishList::getAllWishList() {
	return wishlist;
}
void WishList::deleteAll() noexcept {
	wishlist.clear();
}
void WishList::addRandom(int cate) {
	if (size_t(cate) > repo.getAll().size()) {
		throw RepoException("There are no enough tenants!\n");
	}
	else {
		std::mt19937 mt{ std::random_device{}() };
		std::uniform_int_distribution<> const dist(0, repo.getAll().size() - 1);
		vector<Tenant> dest{ repo.getAll() };
		for (int i = 0; i < cate; i++) {
			const int rndNr = dist(mt);
			wishlist.push_back(dest[rndNr]);
		}
	}
}