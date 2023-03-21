#include <assert.h>
#include <fstream>
#include <iostream>

#include "Service.h"


bool cmp_name(const Tenant& t1, const Tenant& t2)
{
	return t1.getOwner() < t2.getOwner();
}
bool cmp_surface(const Tenant& t1, const Tenant& t2) noexcept
{
	return t1.getSurface() < t2.getSurface();
}
bool cmp_type_surface(const Tenant& t1, const Tenant& t2)
{
	if (t1.getType() < t2.getType())
		return true;
	if (t1.getType() == t2.getType())
		if (t1.getSurface() < t2.getSurface())
			return true;
	return false;
}
bool cmpR_name(const Tenant& t1, const Tenant& t2)
{
	return t1.getOwner() >= t2.getOwner();
}
bool cmpR_surface(const Tenant& t1, const Tenant& t2) noexcept
{
	return t1.getSurface() >= t2.getSurface();
}
bool cmpR_type_surface(const Tenant& t1, const Tenant& t2)
{
	if (t1.getType() > t2.getType())
		return true;
	if (t1.getType() == t2.getType())
		if (t1.getSurface() > t2.getSurface())
			return true;
	return false;
}


const vector<Tenant>& Service::getAll_srv() const noexcept {
	return this->repo.getAll();
}

void Service::add_srv(int nrAp, string owner, string type, double surface) {
	Tenant t{ nrAp,owner,type,surface };
	valid.validate(t);
	repo.add(t);
	undoActions.push_back(std::make_unique<UndoAdd>(repo, t));
}

void Service::remove_srv(int nrAp) {
	Tenant tenant = repo.find(nrAp);
	repo.remove(tenant);
	undoActions.push_back(std::make_unique<UndoRemove>(repo, tenant));
}

void Service::modify_srv(int nrAp, string newOwner) {
	Tenant tenant = repo.find(nrAp);
	Tenant newTenant{ nrAp,newOwner,tenant.getType(),tenant.getSurface() };
	valid.validate(newTenant);
	repo.modify(tenant, newTenant);
	undoActions.push_back(std::make_unique<UndoModify>(repo, tenant, newTenant));
}

const Tenant& Service::find_srv(int nrAp) {
	return repo.find(nrAp);
}

const vector<Tenant> Service::filter_srv(string type_criteria, double surface_criteria) {
	vector<Tenant> filtered;
	if (type_criteria != "-1") {
		std::copy_if(repo.getAll().begin(), repo.getAll().end(), std::back_inserter(filtered), [type_criteria](const Tenant& t) {
			return t.getType() == type_criteria;
			});
	}
	if (surface_criteria != -1) {
		std::copy_if(repo.getAll().begin(), repo.getAll().end(), std::back_inserter(filtered), [surface_criteria](const Tenant& t) {
			return t.getSurface() == surface_criteria;
			});
	}
	return filtered;
}

const vector<Tenant> Service::sort_srv(bool (*cmp)(const Tenant&, const Tenant&))
{
	vector<Tenant> all{ repo.getAll() };
	for (int i = 0; i < all.size(); i++)
	{
		for (int j = i + 1; j < all.size(); j++)
			if (!cmp(all[i], all[j]))
			{
				Tenant aux = all[i];
				all[i] = all[j];
				all[j] = aux;
			}
	}
	return all;
}

void Service::undo() {
	if (undoActions.empty()) {
		throw RepoException{ "There are no Undos left!\n" };
	}
	undoActions.back()->doUndo();
	undoActions.pop_back();
}


void Service::addToWishlist(int nr) {
	repo2.addToWishlist(nr);
}
void Service::deleteAll() noexcept {
	repo2.deleteAll();
}
const vector<Tenant> Service::getAllWishlist() {
	return repo2.getAllWishList();
}
void Service::addRandom(int nr) {
	repo2.addRandom(nr);
}