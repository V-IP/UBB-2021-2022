#include <assert.h>

#include "Repository.h"


const MyList<Tenant>& Repository::getAll() noexcept {
	return this->all;
}

const Tenant& Repository::find(int nrAp) {
	for (const Tenant& tenant : this->all) {
		if (tenant.getNrAp() == nrAp) {
			return tenant;
		}
	}
	throw RepoException("The object doesn't exists!\n");
}

bool Repository::exists(const Tenant& tenant) {
	try {
		find(tenant.getNrAp());
		return true;
	}
	catch (RepoException) {
		return false;}
}

void Repository::add(const Tenant& tenant) {
	if (exists(tenant)) {
		throw RepoException("The object already exists!\n");
	}
	this->all.push_back(tenant);
}


void Repository::remove(const Tenant& tenant) {
	exists(tenant);
	for (auto const& t : all)
		if (tenant.getNrAp() == t.getNrAp()) {
			all.removeVal(t);
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