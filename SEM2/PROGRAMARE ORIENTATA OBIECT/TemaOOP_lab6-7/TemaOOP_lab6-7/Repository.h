#pragma once
#include <vector>
#include <algorithm>

#include "Obj.h"
#include "VectorDinamic.h"

using std::vector;


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
	MyList<Tenant> all;
public:
	Repository() = default;
	Repository(const Repository& ot) = delete;

	const MyList<Tenant>& getAll() noexcept;

	const Tenant& find(int nrAp);
	bool exists(const Tenant& Tenant);
	void add(const Tenant& tenant);

	void remove(const Tenant& tenant);

	void modify(const Tenant& tenant, const Tenant& newTenant);
};