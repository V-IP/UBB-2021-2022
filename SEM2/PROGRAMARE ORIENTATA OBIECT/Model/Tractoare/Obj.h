#pragma once

#include <iostream> 
#include <vector>
using namespace std;

class Obj {
private:
	int id;
	string denumire;
	string tip;
	int nrRoti;
public:
	Obj(int id, string denumire, string tip, int nrRoti) : id{ id }, denumire{ denumire }, tip{ tip }, nrRoti{ nrRoti }{};

	int getId() const;
	string getDenumire() const;
	string getTip() const;
	int getNrRoti() const;
};

void testGetSet();