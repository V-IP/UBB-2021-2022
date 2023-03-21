#pragma once
#include <vector>
#include <algorithm>

#include "Obj.h"

using namespace std;


class RepoException {
private:
	string errorMsg;
public:
	RepoException(string errorMsg) :errorMsg{ errorMsg } {};

	string getErrorMsg() {
		return this->errorMsg;
	}
};

class Repository {
private:
	vector<Tenant> all;
public:
	Repository() = default;
	Repository(const Repository& ot) = delete;

	const vector<Tenant>& getAll() noexcept;
	const Tenant& find(int nrAp);
	bool exists(const Tenant& Tenant);
	virtual void add(const Tenant& tenant);
	void remove(const Tenant& tenant);
	void modify(const Tenant& tenant, const Tenant& newTenant);
};

class FileRepository :public Repository {
private:
	string filename;
	void loadFromFile();
	void saveToFile();
public:
	FileRepository(string filename) :Repository(), filename{ filename }{
		loadFromFile();
	};
	void add(const Tenant& t) override;
};

class WishList {
private:
	Repository& repo;
	vector<Tenant> wishlist;
public:
	WishList(Repository& repo) :repo{ repo } {};
	WishList(const WishList& ot) = delete;

	void addToWishlist(int nr);
	void deleteAll()noexcept;
	const vector<Tenant> getAllWishList();
	void addRandom(int nr);
};