#pragma once
#include <vector>
#include <algorithm>
#include <unordered_map>

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
	void add(const Tenant& tenant);
	void remove(const Tenant& tenant);
	void modify(const Tenant& tenant, const Tenant& newTenant);
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
	void addRandom(int cate);
};

class UnorderedMap {
private:
	Repository& repo;
	unordered_map<string, int> umap;
public:
	UnorderedMap(Repository& repo) :repo{ repo } {};
	UnorderedMap(const UnorderedMap& ot) = delete;

	void updateMap();
	const unordered_map<string, int> getAllMap();
};