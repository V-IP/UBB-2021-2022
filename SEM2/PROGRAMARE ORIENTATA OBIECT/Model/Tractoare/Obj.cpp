#include <assert.h>

#include "Obj.h"

int Obj::getId() const {
	return this->id;
}

string Obj::getDenumire() const {
	return this->denumire;
}

string Obj::getTip() const {
	return this->tip;
}

int Obj::getNrRoti() const {
	return this->nrRoti;
}


void testGetSet() {
	Obj obj{ 1,"Denumire1","Tip1",2 };
	assert(obj.getId() == 1);
	assert(obj.getDenumire() == "Denumire1");
	assert(obj.getTip() == "Tip1");
	assert(obj.getNrRoti() == 2);
}