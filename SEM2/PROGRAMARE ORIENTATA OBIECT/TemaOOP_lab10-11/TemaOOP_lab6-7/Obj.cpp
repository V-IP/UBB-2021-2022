#include <assert.h>

#include "Obj.h"

int Tenant::getNrAp() const noexcept {
	return this->nrAp;
}

string Tenant::getOwner() const {
	return this->owner;
}

double Tenant::getSurface() const noexcept {
	return this->surface;
}

string Tenant::getType() const {
	return this->type;
}

void Tenant::setOwner(string newOwner) {
	this->owner = newOwner;
}

void testGetSet() {
	Tenant t1{ 1,"Name1","Type1",37.75 };
	assert(t1.getNrAp() == 1);
	assert(t1.getOwner() == "Name1");
	assert(t1.getType() == "Type1");
	assert(t1.getSurface() == 37.75);

	Tenant t2{ 2,"Name2","Type2",80.55 };
	assert(t2.getNrAp() == 2);
	assert(t2.getOwner() == "Name2");
	assert(t2.getType() == "Type2");
	assert(t2.getSurface() == 80.55);

	t2.setOwner("newName");
	assert(t2.getOwner() == "newName");
}